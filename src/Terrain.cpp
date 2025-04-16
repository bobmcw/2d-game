
#include "Terrain.h"

#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"

Terrain::Terrain(sf::RenderWindow &window, int x,int y,const std::string& textureName) : window(window), sprite(this->texture) {
    this->hasCollision = false;
    this->x = x;
    this->y = y;
    this->size = 50;
    this->texture = sf::Texture();
    assert(this->texture.loadFromFile(textureName));
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setTextureRect(sf::IntRect({this->x,this->y},{this->size,this->size}));
    this->sprite.setPosition({static_cast<float>(this->x),static_cast<float>(this->y)});
    this->texture.setRepeated(true);
}

void Terrain::draw() const {
    this->window.draw(this->sprite);
}

Wall::Wall(sf::RenderWindow &window, int x, int y)
    : Terrain(window,x,y,"Assets/textures/wall.png") {
        this->hasCollision = true;
}

Floor::Floor(sf::RenderWindow &window, int x, int y) : Terrain(window,x,y,"Assets/textures/floor.png") {
   this-> hasCollision = false;
}

