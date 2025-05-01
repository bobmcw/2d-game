#ifndef ENEMY_H
#define ENEMY_H
#include "ProjectileManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"


class Enemy {
public:
    Enemy(int initialX, int initialY);

    ~Enemy();

    sf::Sprite getSprite();

    void update();

    void MoveTowards(sf::Vector2f position);

    void takeDamage();

    void die();

    bool isDead();

    virtual void enemyAction(sf::Vector2f playerPosition);

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    int x;
    int y;
    int health;
    sf::Clock dmgFlashClock;
};

class Shooting_enemy : public Enemy {
public:
    Shooting_enemy(int initialX, int initialY,ProjectileManager &projectile_manager);

    void shootTowards(sf::Vector2f position);

    void enemyAction(sf::Vector2f playerPosition) override;

private:
    ProjectileManager& projectile_manager;
    sf::Clock shootingCooldown;
};


#endif //ENEMY_H
