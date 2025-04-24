#include "EnemyController.h"

EnemyController::EnemyController(sf::RenderWindow &window, Player &player) : window(window), player(player) {
    this->enemies = std::vector<Enemy *>();
}

void EnemyController::addEnemy(Enemy *e) {
    this->enemies.push_back(e);
}

void EnemyController::removeEnemy(Enemy *e) {
    this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), e), this->enemies.end());
}

void EnemyController::updateEnemies() {
    for (Enemy *e: this->enemies) {
        if (e->isDead()) {
            this->removeEnemy(e);
        } else {
            e->update();
            e->MoveTowards(this->player.getSprite().getPosition());
            this->window.draw(e->getSprite());
        }
    }
}

std::vector<Enemy *> EnemyController::getEnemies() const {
    return this->enemies;
}
