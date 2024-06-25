#ifndef BODYOBJECT_H
#define BODYOBJECT_H

#include <QGraphicsScene>
#include "Position.h"

class BodyObject {
protected:
    int width, height;
    Position position;

public:
    BodyObject(int width, int height, Position position)
        : width(width), height(height), position(position) {}

    virtual ~BodyObject() {}

    virtual void draw(QGraphicsScene& scene) = 0;
};

#endif // BODYOBJECT_H
