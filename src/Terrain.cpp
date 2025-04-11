
#include "Terrain.h"

#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"

Terrain::Terrain(sf::RenderWindow &window, int x,int y,int size) : window(window), sprite(this->texture) {
    this->hasColision = false;
    this->x = x;
    this->y = y;
    this->size = size;
}

Wall::Wall(sf::RenderWindow &window, int x, int y)
    : Terrain(window,x,y,50) {
        this->hasColision = true;
        this->size = 50;
    this->texture = sf::Texture();
    if (!this->texture.loadFromFile("Assets/textures/wall.png")) {
        std::cerr << "failed to load texture Assets/textures/wall.png";
    }
    this->texture.setRepeated(true);
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setTextureRect(sf::IntRect({this->x,this->y},{this->size,this->size}));
    this->sprite.setPosition({static_cast<float>(this->x),static_cast<float>(this->y)});
}

void Wall::draw() {
    this->window.draw(this->sprite);
}
