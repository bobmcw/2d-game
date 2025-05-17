#ifndef UI_H
#define UI_H
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"


class UI {
public:
    UI(sf::RenderWindow &window, Player &player);

    void update();

    void updateHPBar();

    void updateWeapon();

    void draw();

private:
    RenderWindow &window;
    Player &player;
    RectangleShape hpBar;
    RectangleShape hpBarOutline;
    RectangleShape weaponContainer;
    int ammoCount;
    Text ammoText;
    Font font;
    int maxHp;
};


#endif //UI_H
