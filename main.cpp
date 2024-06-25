#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>
#include "KeyPressHandler.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QGraphicsView view;
    QGraphicsScene scene;

    view.setScene(&scene);
    view.setFixedSize(800, 600);

    // Add player
    QGraphicsRectItem* player = new QGraphicsRectItem(0, 0, 32, 32);
    player->setBrush(Qt::blue);
    player->setPos(50, 468); // Adjust starting position to be above the platforms
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

    KeyPressHandler *keyPressHandler = new KeyPressHandler(&view);
    view.installEventFilter(keyPressHandler);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        static int velocityY = 0;
        static int posX = 50;
        static int posY = 468; // Adjust starting position to be above the platforms
        static bool onGround = false;

        // Handle left and right movement
        if (keyPressHandler->leftPressed) {
            posX -= 5;
        }
        if (keyPressHandler->rightPressed) {
            posX += 5;
        }

        // Apply gravity
        velocityY += 1;
        posY += velocityY;

        // Check collision with platforms
        QList<QGraphicsItem*> collidingItems = player->collidingItems();
        onGround = false;
        for (auto& item : collidingItems) {
            if (item->type() == QGraphicsRectItem::Type) {
                onGround = true;
                posY = item->y() - player->rect().height();
                velocityY = 0; // Stop falling
                break;
            }
        }

        // Handle jump
        if (keyPressHandler->upPressed && onGround) {
            velocityY = -20; // Initial jump velocity
            posY += velocityY;
        }

        // Update player position
        player->setPos(posX, posY);

        qDebug() << "Player position: (" << posX << "," << posY << ")";
    });
    timer.start(16); // 60 FPS

    return a.exec();
}
