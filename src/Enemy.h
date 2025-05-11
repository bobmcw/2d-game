#ifndef ENEMY_H
#define ENEMY_H
#include "ProjectileManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"


class Enemy {
public:
    Enemy(float initialX, float initialY);

    virtual ~Enemy();

    sf::Sprite getSprite();

    void update();

    void moveTowards(sf::Vector2f position);

    void takeDamage();

    bool isDead();

    virtual void enemyAction(sf::Vector2f playerPosition);

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    int x;
    int y;
    int health;
    sf::Clock dmgFlashClock;
    float movementSpeed;
};

class Shooting_enemy : public Enemy {
public:
    Shooting_enemy(float initialX, float initialY,ProjectileManager &projectile_manager);

    void shootTowards(sf::Vector2f position);

    void enemyAction(sf::Vector2f playerPosition) override;

protected:
    ProjectileManager& projectile_manager;
    sf::Clock shootingCooldown;
};

class Boss : public Shooting_enemy {
public:
    Boss(float initialX, float initialY,ProjectileManager &projectile_manager);

    void circleAttack(sf::Vector2f playerPosition);

    void enemyAction(sf::Vector2f playerPosition) override;
private:
    sf::Clock specialAttackTimer;
};

#endif //ENEMY_H
