#ifndef ENEMY_H
#define ENEMY_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"


class Enemy {
public:
    Enemy(int initialX, int initialY);
    sf::Sprite getSprite();
    void MoveTowards(sf::Vector2f position);
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int x;
    int y;
};



#endif //ENEMY_H
