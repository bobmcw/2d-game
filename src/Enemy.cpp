#include "Enemy.h"
#include <cmath>
#include <iostream>

#include "fmt/base.h"
#include "SFML/System/Time.hpp"

Enemy::Enemy(int initialX, int initialY) : sprite(this->texture) {
   this->x = initialX;
   this->y = initialY;
   this->texture = sf::Texture();
   assert(texture.loadFromFile("Assets/textures/enemy.png"));
   this->sprite = sf::Sprite(this->texture);
   this-> health = 10;
   this->dmgFlashClock = sf::Clock();
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


