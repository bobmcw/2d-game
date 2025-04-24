#include "EnemyController.h"

EnemyController::EnemyController(sf::RenderWindow &window, Player &player) : window(window), player(player){
   this->enemies = std::vector<Enemy *>();
}
void EnemyController::addEnemy(Enemy* e) {
  this->enemies.push_back(e);
}
void EnemyController::updateEnemies() const {
    for (Enemy* e : this->enemies) {
        e->MoveTowards(this->player.getSprite().getPosition());
       this->window.draw(e->getSprite());
    }
}

std::vector<Enemy *> EnemyController::getEnemies() const {
    return this->enemies;
}


