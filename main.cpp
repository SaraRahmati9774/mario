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

    // Add continuous ground platforms
    int platformWidth = 100;
    int platformHeight = 20;
    int platformCount = 10; // Number of platforms
    int startY = 500;

    for (int i = 0; i < platformCount; ++i) {
        QGraphicsRectItem* platform = new QGraphicsRectItem(0, 0, platformWidth, platformHeight);
        platform->setPos(i * platformWidth, startY);
        platform->setBrush(Qt::gray);
        scene.addItem(platform);
    }

    view.show();

    qDebug() << "Application started with player and continuous ground platforms";

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        static int velocityY = 0;
        static int posX = 50;
        static int posY = 50;

        // Check collision with platforms
        bool onGround = false;
        QList<QGraphicsItem*> collidingItems = player->collidingItems();
        for (auto& item : collidingItems) {
            if (item->type() == QGraphicsRectItem::Type) {
                onGround = true;
                posY = item->y() - player->rect().height();
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
