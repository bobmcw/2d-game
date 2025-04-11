

#ifndef TERAIN_H
#define TERAIN_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#define WALL_SIZE 50;

class Terrain {
public:
    bool hasColision;
    virtual void draw() = 0;
    virtual ~Terrain() = default;

    sf::Sprite getSprite() {
        return this->sprite;
    }
protected:
    int x;
    int y;
    int size;
    sf::RenderWindow& window;
    Terrain(sf::RenderWindow &window, int x, int y, int size);
    sf::Texture texture;
    sf::Sprite sprite;
};
class Wall : public Terrain {
public:
    Wall(sf::RenderWindow &window, int x, int y);

    void draw() override;
};


#endif //TERAIN_H
