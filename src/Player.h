#ifndef PLAYER_H
#define PLAYER_H
#include "ProjectileManager.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

using namespace sf;

struct PressedKeys {
    bool W;
    bool S;
    bool A;
    bool D;
};

class Player {
public:
    Player(RenderWindow& window, ProjectileManager& projectile_manager);
    void handleMove();
    void listenForKeyPresses(std::optional<Event> event);
    void draw();
    void update();
    Sprite& getSprite();
    void drawCrosshair();
    void shoot();
    int getHp();

    void takeDamage();

private:
    PressedKeys pressedKeys;
    Sprite sprite;
    Texture texture;
    RenderWindow& window;
    ProjectileManager& projectile_manager;
    Vector2f velocity;
    int hp;
    sf::Clock eyeFrameClock;
};



#endif //PLAYER_H
