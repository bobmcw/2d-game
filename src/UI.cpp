#include "UI.h"

#include "fmt/color.h"

UI::UI(sf::RenderWindow &window, Player &player) : window(window), player(player), hpBar({200, 20}),
                                                   hpBarOutline({210, 30}), weaponContainer({75, 50}),
                                                   font("Assets/ByteBounce.ttf"),
                                                   ammoCount(player.getWeapon().getAmmo()),
                                                   maxAmmo(player.getWeapon().getAmmo()),
                                                   ammoText(font) {
    hpBar.setFillColor(sf::Color::Red);
    hpBarOutline.setFillColor(sf::Color::Black);
    hpBarOutline.setOutlineColor(sf::Color::White);
    hpBarOutline.setOutlineThickness(5);
    hpBarOutline.setPosition({50, 50});
    weaponContainer.setPosition({
        static_cast<float>(window.getSize().x * 0.01),
        static_cast<float>(window.getSize().y - window.getSize().y * 0.05)
    });
    hpBar.setPosition({55, 55});
    maxHp = player.getHp();
    ammoText.setPosition({weaponContainer.getPosition().x, static_cast<float>(weaponContainer.getPosition().y - weaponContainer.getSize().y * 0.75)});
    ammoText.setCharacterSize(32);
    ammoText.setFillColor(sf::Color::White);

}

void UI::update() {
    updateHPBar();
    updateWeapon();
    draw();
}

void UI::updateHPBar() {
    float length = 200 * player.getHp() / maxHp;
    if (length < 0) {
        length = 0;
    }
    hpBar.setSize({length, 20});
}

void UI::updateWeapon() {
    player.getWeapon().getSprite().setScale({2, 2});
    player.getWeapon().getSprite().setPosition({
        weaponContainer.getPosition().x + weaponContainer.getSize().x / 4, weaponContainer.getPosition().y
    });
    ammoText.setString(fmt::format("{} / {}", player.getWeapon().getAmmo(), maxAmmo));
    window.draw(weaponContainer);
    window.draw(ammoText);
    window.draw(player.getWeapon().getSprite());
}

void UI::draw() {
    window.draw(hpBarOutline);
    window.draw(hpBar);
}
