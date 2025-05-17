#include "Terrain.h"

#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"

Terrain::Terrain(sf::RenderWindow &window, int x, int y, const std::string &textureName) : window(window),
    sprite(texture), x(x), y(y), hasCollision(false), size(50) {
    texture = sf::Texture();
    assert(texture.loadFromFile(textureName));
    sprite = sf::Sprite(texture);
    sprite.setTextureRect(sf::IntRect({this->x, this->y}, {size, size}));
    sprite.setPosition({static_cast<float>(this->x), static_cast<float>(this->y)});
    texture.setRepeated(true);
}

void Terrain::draw() const {
    window.draw(sprite);
}

Wall::Wall(sf::RenderWindow &window, int x, int y)
    : Terrain(window, x, y, "Assets/textures/wall.png") {
    hasCollision = true;
}

Floor::Floor(sf::RenderWindow &window, int x, int y) : Terrain(window, x, y, "Assets/textures/floor.png") {
    hasCollision = false;
}

Hatch::Hatch(sf::RenderWindow &window, int x, int y): Terrain(window, x, y, "Assets/textures/hatch-closed.png") {
    hasCollision = false;
    isOpen = false;
    assert(openTexture.loadFromFile("Assets/textures/stairs.png"));
    openTexture.setRepeated(true);
}

void Hatch::open() {
    if (!isOpen) {
        isOpen = true;
        sprite.setTexture(openTexture);
    }
}

bool Hatch::isOpened() {
    return isOpen;
}
