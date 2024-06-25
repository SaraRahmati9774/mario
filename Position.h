#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    int x, y;

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
    Position(const Position& other) : x(other.x), y(other.y) {}
    Position& operator=(const Position& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

#endif // POSITION_H
