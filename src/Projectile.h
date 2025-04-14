#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(sf::Vector2f velocity, sf::Vector2f initialPosition);
    sf::Vector2f velocity;
    sf::Texture texture;
    sf::Sprite sprite;

    ~Projectile() {
    }

private:
};



#endif //BULLET_H
