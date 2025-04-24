#include "Enemy.h"
#include <cmath>
#include "fmt/base.h"

Enemy::Enemy(int initialX, int initialY) : sprite(this->texture) {
   this->x = initialX;
   this->y = initialY;
   this->texture = sf::Texture();
   assert(texture.loadFromFile("Assets/textures/enemy.png"));
   this->sprite = sf::Sprite(this->texture);
}
sf::Sprite Enemy::getSprite() {
   return this->sprite;
}

void Enemy::MoveTowards(sf::Vector2f position) {
   auto delta = position - this->sprite.getPosition();
   auto angle = std::atan2(delta.y,delta.x);
   this->sprite.move(sf::Vector2f(1 * cos(angle),1 * sin(angle)));
}

void Enemy::takeDamage() {
   fmt::print("took dmg");
}


