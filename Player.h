#ifndef PLAYER_H
#define PLAYER_H

#include "BodyObject.h"
#include <QGraphicsRectItem>
#include <QDebug>

class Player : public BodyObject {
private:
    int speed;
    Position velocity;
    QGraphicsRectItem* rect;

public:
    Player(int width, int height, Position position, int speed, Position velocity)
        : BodyObject(width, height, position), speed(speed), velocity(velocity), rect(new QGraphicsRectItem(0, 0, width, height)) {
        rect->setBrush(Qt::blue); // Set color to blue for visibility
        qDebug() << "Player created at (" << position.x << "," << position.y << ")";
    }

    ~Player() {
        delete rect;
    }

    void handleGravity() {
        velocity.y += 1; // Simple gravity effect
        position.y += velocity.y;
        if (rect) rect->setY(position.y);
        qDebug() << "Player position after gravity: (" << position.x << "," << position.y << ")";
    }

    void handleMovement() {
        position.x += velocity.x * speed;
        if (rect) rect->setX(position.x);
        qDebug() << "Player position after movement: (" << position.x << "," << position.y << ")";
    }

    void draw(QGraphicsScene& scene) override {
        if (!rect->scene()) {
            scene.addItem(rect);
        }
        rect->setPos(position.x, position.y);
        qDebug() << "Player drawn at (" << position.x << "," << position.y << ")";
    }
};

#endif // PLAYER_H
