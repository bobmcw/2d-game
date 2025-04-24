#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"


class EnemyController {
public:
    EnemyController(sf::RenderWindow &window, Player &player);
    void addEnemy(Enemy *e);
    void removeEnemy(Enemy *e);
    void updateEnemies();
    std::vector<Enemy*> getEnemies() const;
private:
    std::vector<Enemy*> enemies;
    sf::RenderWindow &window;
    Player &player;
};



#endif //ENEMYCONTROLLER_H
