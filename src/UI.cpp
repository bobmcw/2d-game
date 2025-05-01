//
// Created by Jan Zakrzewski on 01/05/2025.
//

#include "UI.h"

UI::UI(sf::RenderWindow &window, Player &player) : window(window),player(player),hpBar({200,20}),hpBarOutline({210,30}) {
    hpBar.setFillColor(sf::Color::Red);
    hpBarOutline.setFillColor(sf::Color::White);
    hpBarOutline.setPosition({50,50});
    hpBar.setPosition({55,55});
}

void UI::draw() {
    window.draw(hpBarOutline);
    window.draw(hpBar);
}

