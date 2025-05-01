#include "UI.h"

UI::UI(sf::RenderWindow &window, Player &player) : window(window),player(player),hpBar({200,20}),hpBarOutline({210,30}) {
    hpBar.setFillColor(sf::Color::Red);
    hpBarOutline.setFillColor(sf::Color::Black);
    hpBarOutline.setOutlineColor(sf::Color::White);
    hpBarOutline.setOutlineThickness(5);
    hpBarOutline.setPosition({50,50});
    hpBar.setPosition({55,55});
    maxHp = player.getHp();
}

void UI::update() {
    float length = 200 * player.getHp() / maxHp;
    if (length < 0) {
        length = 0;
    }
    hpBar.setSize({length,20});
    draw();
}

void UI::draw() {
    window.draw(hpBarOutline);
    window.draw(hpBar);
}

