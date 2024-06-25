#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <QDebug>
#include "Platform.h"
#include "Player.h"

class Game {
private:
    QGraphicsView& view;
    QGraphicsScene& scene;
    std::vector<Platform> platforms;
    Player player;
    int amountDistance;

public:
    Game(QGraphicsView& view, QGraphicsScene& scene, std::vector<Platform> platforms, Player player, int amountDistance)
        : view(view), scene(scene), platforms(platforms), player(player), amountDistance(amountDistance) {
        qDebug() << "Game initialized";
    }

    void handleGameOver() {
        qDebug() << "Game Over!";
        // Handle game over logic
    }

    void handleVictory() {
        qDebug() << "Victory!";
        // Handle victory logic
    }

    void draw() {
        qDebug() << "Drawing scene...";
        scene.clear();
        for (auto& platform : platforms) {
            platform.draw(scene);
        }
        player.draw(scene);
        view.setScene(&scene);
        qDebug() << "Scene drawn";
    }

    void update() {
        qDebug() << "Updating game state...";
        player.handleGravity();
        player.handleMovement();
        // More game logic here
        qDebug() << "Game state updated";
    }
};

#endif // GAME_H
