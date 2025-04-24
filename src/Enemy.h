#ifndef ENEMY_H
#define ENEMY_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"


class Enemy {
public:
    Enemy(int initialX, int initialY);
    sf::Sprite getSprite();
    void update();
    void MoveTowards(sf::Vector2f position);
    void takeDamage();
    void die();
    bool isDead();
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int x;
    int y;
    int health;
    sf::Clock dmgFlashClock;
};



#endif //ENEMY_H
