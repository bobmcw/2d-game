#include "Menu.h"

Menu::Menu(sf::RenderWindow &window) : menu_(sf::RectangleShape({
                                           static_cast<float>(window.getSize().x),
                                           static_cast<float>(window.getSize().y)
                                       })), window(window), isActive_(true) {
}

void Menu::displayMenu() {
    window.draw(menu_);
}

bool Menu::isActive() {
    return isActive_;
}
