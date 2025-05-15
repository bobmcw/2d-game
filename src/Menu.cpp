#include "Menu.h"

Menu::Menu(sf::RenderWindow &window, SaverAndLoader &saveManager, Map_parser &mapLoader) : menu_(sf::RectangleShape({
                                           static_cast<float>(window.getSize().x),
                                           static_cast<float>(window.getSize().y)
                                       })), mapLoader(mapLoader),window(window),saveManager(saveManager), isActive_(true),
                                       options({
                                           Option(options::Start, "Start", [this]() {startNewGame();}),
                                           Option(options::Continue, "Continue", [this]() {this->loadAndStart();}),
                                           Option(options::Exit, "Exit", [&window]() {window.close();})
                                       }), selectedIndex(0) {
    menu_.setFillColor(sf::Color::Black);
}

void Menu::displayMenu() {
    window.draw(menu_);
    float x = window.getSize().x/2;
    float y = window.getSize().y/2;
    for (Option &o : options) {
        o.text.setPosition({x,y});
        o.text.setFillColor(sf::Color::White);
        highlightSelected();
        y += 50;
        window.draw(o.text);
    }
}

void Menu::startNewGame() {
   mapLoader.load_maps();
    mapLoader.load_current_map();
    hideMenu();
}

void Menu::loadAndStart() {
   saveManager.load();
    mapLoader.load_current_map();
   hideMenu();
}

void Menu::hideMenu() {
    isActive_ = false;
}

bool Menu::isActive() const {
    return isActive_;
}
void Menu::highlightSelected() {
    options.at(selectedIndex).text.setFillColor(sf::Color::Yellow);
}

void Menu::moveDown() {
    if (selectedIndex >= options.size() -1) {
        return;
    }
    selectedIndex++;
}

void Menu::moveUp() {
    if (selectedIndex <= 0) {
        return;
    }
    selectedIndex--;
}

void Menu::listenToKeyPresses(std::optional<sf::Event> event) {
    if (auto const e = event->getIf<sf::Event::KeyPressed>()) {
        if (e->code == sf::Keyboard::Key::Up) {
            moveUp();
        }else if (e->code == sf::Keyboard::Key::Down){
            moveDown();
        } else if (e->code == sf::Keyboard::Key::Enter) {
            options.at(selectedIndex).callback();
        }
    }
}
