#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsView view;
    QGraphicsScene scene;

    view.setScene(&scene);
    view.setFixedSize(800, 600);

    // Add player
    QGraphicsRectItem* player = new QGraphicsRectItem(0, 0, 32, 32);
    player->setBrush(Qt::blue);
    player->setPos(50, 50);
    scene.addItem(player);

    // Add platforms
    std::vector<QGraphicsRectItem*> platforms = {
        new QGraphicsRectItem(0, 0, 100, 20),
        new QGraphicsRectItem(0, 0, 100, 20),
        new QGraphicsRectItem(0, 0, 100, 20)
    };
    platforms[0]->setPos(0, 100);
    platforms[1]->setPos(150, 150);
    platforms[2]->setPos(300, 200);
    for (auto& platform : platforms) {
        platform->setBrush(Qt::gray);
        scene.addItem(platform);
    }

    view.show();

    qDebug() << "Application started with player and platforms";

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        static int velocityY = 0;
        static int posX = 50;
        static int posY = 50;

        // Check collision with platforms
        bool onGround = false;
        for (auto& platform : platforms) {
            if (player->collidesWithItem(platform)) {
                // Player is on the platform
                onGround = true;
                posY = platform->y() - player->rect().height();
                velocityY = 0; // Stop falling
                break;
            }
        }

        // Apply gravity if not on the ground
        if (!onGround) {
            velocityY += 1;
            posY += velocityY;
        }

        // Movement
        posX += 1;

        // Update player position
        player->setPos(posX, posY);

        qDebug() << "Player position: (" << posX << "," << posY << ")";
    });
    timer.start(16); // 60 FPS

    return a.exec();
}
