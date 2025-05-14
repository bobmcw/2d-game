#ifndef MENU_H
#define MENU_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum class options {
    Start,
    Continue,
    Exit,
};

class Menu {
public:
    Menu(sf::RenderWindow &window);
    void displayMenu();
    void hideMenu();
    bool isActive();
private:
    sf::RenderWindow &window;
    bool isActive_;
    sf::RectangleShape menu_;

};



#endif //MENU_H
