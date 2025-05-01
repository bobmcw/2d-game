#include "EnemyController.h"

EnemyController::EnemyController(sf::RenderWindow &window, Player &player) : window(window), player(player) {
    this->enemies = std::vector<std::unique_ptr<Enemy> >();
}

void EnemyController::addEnemy(std::unique_ptr<Enemy> e) {
    this->enemies.push_back(std::move(e));
}

void EnemyController::removeEnemy(std::unique_ptr<Enemy> e) {
    this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), e), this->enemies.end());
}

void EnemyController::updateEnemies() {
    auto i = enemies.begin();
    while (i != enemies.end()) {
        if ((*i)->isDead()) {
            i = enemies.erase(i);
        } else {
            (*i)->update();
            (*i)->enemyAction(player.getSprite().getPosition());
            //(*i)->MoveTowards(this->player.getSprite().getPosition());
            this->window.draw((*i)->getSprite());
            ++i;
        }
    }
}

std::vector<std::unique_ptr<Enemy> > &EnemyController::getEnemies() {
    return this->enemies;
}
