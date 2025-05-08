#include "Enemy.h"
#include <cmath>
#include <iostream>

#include "fmt/base.h"
#include "SFML/System/Time.hpp"

Enemy::Enemy(float initialX, float initialY) : sprite(this->texture), x(initialX), y(initialY), texture(sf::Texture()),health(10), dmgFlashClock(sf::Clock()) {
   assert(texture.loadFromFile("Assets/textures/enemy.png"));
   this->sprite = sf::Sprite(this->texture);
   this->sprite.setPosition({initialX,initialY});
}

Enemy::~Enemy() {
   std::cout << "enemy destroyed";
}

sf::Sprite Enemy::getSprite() {
   return this->sprite;
}

void Enemy::update() {
   if (this->dmgFlashClock.isRunning() && this->dmgFlashClock.getElapsedTime().asSeconds() >= 0.2) {
      this->dmgFlashClock.restart();
      this->dmgFlashClock.stop();
      this->sprite.setColor(sf::Color::White);
   }
}

void Enemy::MoveTowards(sf::Vector2f position) {
   auto delta = position - this->sprite.getPosition();
   auto angle = std::atan2(delta.y,delta.x);
   this->sprite.move(sf::Vector2f(1 * cos(angle),1 * sin(angle)));
}


void Enemy::takeDamage() {
   this->health -= 1;
   this->sprite.setColor(sf::Color::Red);
   this->dmgFlashClock.start();
   this->sprite.setColor(sf::Color::Red);
}


bool Enemy::isDead() {
   return this->health<=0;
}

void Enemy::enemyAction(sf::Vector2f playerPosition) {
  MoveTowards(playerPosition);
}

//shooting enemy

Shooting_enemy::Shooting_enemy(float initialX, float initialY,ProjectileManager &projectile_manager) : Enemy(initialX,initialY), projectile_manager(projectile_manager) {
   shootingCooldown.start();
}

void Shooting_enemy::shootTowards(sf::Vector2f position) {
   if (shootingCooldown.getElapsedTime().asSeconds() > 0.3) {
      auto delta = position - this->sprite.getPosition();
      auto angle = std::atan2(delta.y,delta.x);
      auto currentposition = this->sprite.getGlobalBounds().getCenter() + sf::Vector2f(50 * cos(angle), 50 * sin(angle));
      auto direction = sf::Vector2f(std::cos(angle), std::sin(angle));
      projectile_manager.addProjectile(std::make_unique<Projectile>(direction,currentposition));
      shootingCooldown.restart();
   }
}

void Shooting_enemy::enemyAction(sf::Vector2f playerPosition) {
   shootTowards(playerPosition);
}

//Boss

Boss::Boss(float initialX, float initialY, ProjectileManager &projectile_manager) : Enemy(initialX,initialY),projectile_manager(projectile_manager) {

}
void Boss::enemyAction(sf::Vector2f playerPosition) {

}



