#ifndef KEYPRESSHANDLER_H
#define KEYPRESSHANDLER_H

#include <QObject>
#include <QKeyEvent>

class KeyPressHandler : public QObject {
    Q_OBJECT

public:
    KeyPressHandler(QObject *parent = nullptr) : QObject(parent), leftPressed(false), rightPressed(false), upPressed(false) {}

    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            bool isPressed = (event->type() == QEvent::KeyPress);

            switch (keyEvent->key()) {
            case Qt::Key_Left:
                leftPressed = isPressed;
                return true;
            case Qt::Key_Right:
                rightPressed = isPressed;
                return true;
            case Qt::Key_Up:
                upPressed = isPressed;
                return true;
            default:
                break;
            }
        }
        return QObject::eventFilter(obj, event);
    }

    bool leftPressed;
    bool rightPressed;
    bool upPressed;
};

#endif // KEYPRESSHANDLER_H
