
#include "Terrain.h"

#include "SFML/Graphics/RenderWindow.hpp"

Terrain::Terrain(sf::RenderWindow &window, int x,int y,int size) : window(window), sprite(this->texture) {
    this->x = x;
    this->y = y;
    this->size = size;
}

Wall::Wall(sf::RenderWindow &window, int x, int y)
    : Terrain(window,x,y,50) {
        this->hasColision = true;
        this->size = 50;
        //this->texture = sf::Texture("textures/wall.png", false, sf::IntRect({this->x,this->y}, {this->size,this->size}));
        //this->sprite = sf::Sprite(this->texture);
    this->texture = sf::Texture();
    this->texture.loadFromFile("textures/wall.png");
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setTextureRect(sf::IntRect({this->x,this->y},{this->size,this->size}));
    this->sprite.setPosition({(float)this->x,(float)this->y});
}

void Wall::draw() {
    this->window.draw(this->sprite);
}
