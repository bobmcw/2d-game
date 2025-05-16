#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include <functional>

#include "SaverAndLoader.h"

enum class options {
    Start,
    Continue,
    Exit,
};

struct Option {
    inline static sf::Font font = sf::Font("Assets/ByteBounce.ttf");
    options val;
    sf::Text text;
    std::function<void()> callback;
    Option(options o, std::string text, std::function<void()> f) : val(o), text(font), callback(std::move(f)) {
        this->text.setString(text);
        this->text.setCharacterSize(24);
        this->text.setFillColor(sf::Color::White);
    }
};

class Menu {
public:
    Menu(sf::RenderWindow &window, SaverAndLoader &saveManager, Map_parser &mapLoader, Player &player);
    void displayMenu();

    void startNewGame();

    void loadAndStart();

    void hideMenu();

    void checkIfPlayerIsDead();

    bool isActive() const;

    void highlightSelected();

    void listenToKeyPresses(std::optional<sf::Event> event);
private:
    void moveUp();
    void moveDown();
    sf::RenderWindow &window;
    SaverAndLoader &saveManager;
    Map_parser &mapLoader;
    Player &player;
    bool isActive_;
    sf::RectangleShape menu_;
    std::vector<Option> options;
    int selectedIndex;
};



#endif //MENU_H
