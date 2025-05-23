#include "Enemy.h"
#include <cmath>
#include <iostream>
#include "SFML/System/Time.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
Enemy::Enemy(float initialX, float initialY) : sprite(this->texture), x(initialX), y(initialY), texture(sf::Texture()),
                                               health(10), dmgFlashClock(sf::Clock()), movementSpeed(1) {
    assert(texture.loadFromFile("Assets/textures/enemy.png"));
    sprite = sf::Sprite(this->texture);
    sprite.setPosition({initialX, initialY});
}

Enemy::~Enemy() {
}

sf::Sprite Enemy::getSprite() {
    return sprite;
}

void Enemy::update() {
    if (dmgFlashClock.isRunning() && dmgFlashClock.getElapsedTime().asSeconds() >= 0.2) {
        dmgFlashClock.restart();
        dmgFlashClock.stop();
        sprite.setColor(sf::Color::White);
    }
}

void Enemy::moveTowards(sf::Vector2f position) {
    auto delta = position - sprite.getPosition();
    auto angle = std::atan2(delta.y, delta.x);
    sprite.move(sf::Vector2f(movementSpeed * cos(angle), movementSpeed * sin(angle)));
}


void Enemy::takeDamage() {
    health -= 1;
    sprite.setColor(sf::Color::Red);
    dmgFlashClock.start();
    sprite.setColor(sf::Color::Red);
}


bool Enemy::isDead() {
    return health <= 0;
}

void Enemy::enemyAction(sf::Vector2f playerPosition) {
    moveTowards(playerPosition);
}

//shooting enemy

Shooting_enemy::Shooting_enemy(float initialX, float initialY,
                               ProjectileManager &projectile_manager) : Enemy(initialX, initialY),
                                                                        projectile_manager(projectile_manager) {
    shootingCooldown.start();
}

void Shooting_enemy::shootTowards(sf::Vector2f position) {
    if (shootingCooldown.getElapsedTime().asSeconds() > 0.3) {
        auto delta = position - sprite.getPosition();
        auto angle = std::atan2(delta.y, delta.x);
        auto currentposition = sprite.getGlobalBounds().getCenter() + sf::Vector2f(
                                   50 * cos(angle), 50 * sin(angle));
        auto direction = sf::Vector2f(std::cos(angle), std::sin(angle));
        projectile_manager.addProjectile(std::make_unique<Projectile>(direction, currentposition));
        shootingCooldown.restart();
    }
}

void Shooting_enemy::enemyAction(sf::Vector2f playerPosition) {
    shootTowards(playerPosition);
}

//Boss

Boss::Boss(float initialX, float initialY, ProjectileManager &projectile_manager) : Shooting_enemy(
    initialX, initialY, projectile_manager) {
    specialAttackTimer.restart();
    movementSpeed = 0.5;
    health = 100;
}

void Boss::circleAttack(sf::Vector2f playerPosition) {
    if (specialAttackTimer.getElapsedTime().asSeconds() >= 5) {
        auto numPoints = 40;
        auto radius = 50;
        auto currentPosition = sprite.getGlobalBounds().getCenter();
        for (int i = 0; i < numPoints; i++) {
            auto tmp = (2 * M_PI * i) / numPoints;

            auto spawnPoint = sf::Vector2f(currentPosition.x + radius * std::cos(tmp),
                                           currentPosition.y + radius * std::sin(tmp));

            auto direction = spawnPoint - currentPosition;
            auto length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
            direction /= length;

            projectile_manager.addProjectile(std::make_unique<Projectile>(direction, spawnPoint));
            specialAttackTimer.restart();
        }
    }
}

void Boss::enemyAction(sf::Vector2f playerPosition) {
    circleAttack(playerPosition);
    shootTowards(playerPosition);
    moveTowards(playerPosition);
}
