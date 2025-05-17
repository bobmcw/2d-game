#include "Projectile.h"

#include <iostream>

Projectile::Projectile(sf::Vector2f velocity, sf::Vector2f initialPosition): sprite(this->texture) {
    this->velocity = velocity;
    this->texture = sf::Texture();
    if (!this->texture.loadFromFile("Assets/textures/bullet.png")) {
        std::cerr << "failed to load texture texture/bullet.png";
    }
    this->texture.setRepeated(true);
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setPosition(initialPosition);
}

Projectile::~Projectile() {
}
