#ifndef PLAYER_H
#define PLAYER_H
#include "ProjectileManager.h"
#include "Weapon.h"
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
    bool LMB;
};

class Player {
public:
    Player(RenderWindow &window, ProjectileManager &projectile_manager);

    void handleMove();

    void listenForKeyPresses(std::optional<Event> event);

    void handleShooting();

    void draw();

    void update();

    Sprite &getSprite();

    void drawCrosshair();

    void shoot();

    void handleReload();

    int getHp();

    void takeDamage();

    void setWeapon(Weapon w);

    Weapon &getWeapon();

private:
    bool lmbPressedAndReleased;
    Weapon weapon;
    PressedKeys pressedKeys;
    Sprite sprite;
    Texture texture;
    RenderWindow &window;
    ProjectileManager &projectile_manager;
    Vector2f velocity;
    int hp;
    sf::Clock eyeFrameClock;
};


#endif //PLAYER_H
