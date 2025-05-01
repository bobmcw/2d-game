#ifndef UI_H
#define UI_H
#include "Player.h"
#include "SFML/Graphics/RenderWindow.hpp"


class UI {
public:
    UI(sf::RenderWindow &window, Player &player);
    void draw();
private:
    RenderWindow &window;
    Player &player;
    RectangleShape hpBar;
    RectangleShape hpBarOutline;
};



#endif //UI_H
