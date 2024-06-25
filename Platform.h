#ifndef PLATFORM_H
#define PLATFORM_H

#include "BodyObject.h"
#include <QGraphicsRectItem>
#include <QDebug>

class Platform : public BodyObject {
private:
    QGraphicsRectItem* rect;

public:
    Platform(int width, int height, Position position)
        : BodyObject(width, height, position), rect(new QGraphicsRectItem(0, 0, width, height)) {
        rect->setBrush(Qt::gray); // Set color to gray for visibility
        qDebug() << "Platform created at (" << position.x << "," << position.y << ")";
    }

    ~Platform() {
        delete rect;
    }

    void draw(QGraphicsScene& scene) override {
        if (!rect->scene()) {
            scene.addItem(rect);
        }
        rect->setPos(position.x, position.y);
    }
};

#endif // PLATFORM_H
