#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"


class EnemyController {
public:
    EnemyController(sf::RenderWindow &window, Player &player);
    void addEnemy(std::unique_ptr<Enemy> e);
    void removeEnemy(std::unique_ptr<Enemy> e);
    void updateEnemies();
    std::vector<std::unique_ptr<Enemy>>& getEnemies();
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::RenderWindow &window;
    Player &player;
};



#endif //ENEMYCONTROLLER_H
