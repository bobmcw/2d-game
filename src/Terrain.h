

#ifndef TERAIN_H
#define TERAIN_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#define WALL_SIZE 50;

class Openable {
public:
    virtual void open() = 0;
    virtual ~Openable() = default;
};

class Terrain {
public:
    bool hasCollision;
    void draw() const;
    virtual ~Terrain() = default;
    sf::Sprite getSprite() {
        return this->sprite;
    }
protected:
    int x;
    int y;
    int size;
    sf::RenderWindow& window;
    Terrain(sf::RenderWindow &window, int x, int y, const std::string& textureName);
    sf::Texture texture;
    sf::Sprite sprite;
};

class Wall : public Terrain {
public:
    Wall(sf::RenderWindow &window, int x, int y);
};

class Floor : public Terrain {
public:
    Floor(sf::RenderWindow &window, int x, int y);
};

class Hatch : public Terrain, public Openable {
public:
    Hatch(sf::RenderWindow &window, int x, int y);
    void open() override;
private:
    bool isOpen;
    sf::Texture openTexture;
};

#endif //TERAIN_H
