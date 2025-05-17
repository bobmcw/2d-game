#include "EnemyController.h"

EnemyController::EnemyController(sf::RenderWindow &window, Player &player) : window(window), player(player) {
    enemies = std::vector<std::unique_ptr<Enemy> >();
}

void EnemyController::addEnemy(std::unique_ptr<Enemy> e) {
    enemies.push_back(std::move(e));
}

void EnemyController::removeEnemy(std::unique_ptr<Enemy> e) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), e), enemies.end());
}

void EnemyController::updateEnemies() {
    auto i = enemies.begin();
    while (i != enemies.end()) {
        if ((*i)->isDead()) {
            i = enemies.erase(i);
        } else {
            (*i)->update();
            (*i)->enemyAction(player.getSprite().getPosition());
            window.draw((*i)->getSprite());
            ++i;
        }
    }
}

std::vector<std::unique_ptr<Enemy> > &EnemyController::getEnemies() {
    return enemies;
}
