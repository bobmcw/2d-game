#include "Player.h"

#include <iostream>

#include "SFML/Window/Keyboard.hpp"
#include <cmath>


using namespace sf;

Player::Player(RenderWindow &window, ProjectileManager &projectile_manager)
    : sprite(texture), window(window), projectile_manager(projectile_manager), hp(10), font("Assets/ByteBounce.ttf"), reloadText(font),
      weapon(Weapon(weaponType::ak47, projectile_manager)) {
    pressedKeys = PressedKeys();
    texture = Texture();
    if (!texture.loadFromFile("Assets/textures/player.png")) {
        std::cerr << "failed to load /Assets/textures/player.png";
    }
    sprite = Sprite(texture);
    sprite.setPosition({750, 750});
    sprite.setTextureRect(sf::IntRect({0, 0}, {50, 50}));
    window.draw(sprite);
    velocity = Vector2f(0, 0);
    lmbPressedAndReleased = true;
    reloadText.setString("reloading...");
    reloadText.setCharacterSize(20);
}

Sprite &Player::getSprite() {
    return sprite;
}

int Player::getHp() {
    return hp;
}

void Player::setHp(int hp) {
    this->hp = hp;
}

void Player::takeDamage() {
    if (eyeFrameClock.isRunning() && eyeFrameClock.getElapsedTime().asSeconds() > 0.75) {
        hp -= 1;
        eyeFrameClock.restart();
    }
}

void Player::setWeapon(Weapon&& w) {
    weapon = std::move(w);
    weapon.rebindTexture();
}
void Player::setWeapon(int id) {
    weapon = Weapon(id,projectile_manager);
    weapon.rebindTexture();
}

Weapon& Player::getWeapon() {
    return weapon;
}

void Player::drawCrosshair() {
    auto croshairVisualization = CircleShape(10);
    croshairVisualization.setFillColor(Color::Green);
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    auto delta = mousePos - sprite.getPosition();
    auto angle = std::atan2(delta.y, delta.x);
    //https://en.sfml-dev.org/forums/index.php?topic=5992.0
    croshairVisualization.setPosition(
        sprite.getGlobalBounds().getCenter() + Vector2f(50 * cos(angle), 50 * sin(angle)));
    window.draw(croshairVisualization);
}

void Player::shoot() {
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    auto delta = mousePos - sprite.getPosition();
    auto angle = std::atan2(delta.y, delta.x);
    //https://en.sfml-dev.org/forums/index.php?topic=5992.0
    auto position = sprite.getGlobalBounds().getCenter() + Vector2f(50 * cos(angle), 50 * sin(angle));
    auto direction = sf::Vector2f(std::cos(angle) * 1.5, std::sin(angle) * 1.5);
    if (!weapon.isReloading()) {
        weapon.shoot(direction, position);
    }
}

void Player::displayReloadText() {
    reloadText.setPosition({sprite.getPosition().x, sprite.getPosition().y - 25 }) ;
    window.draw(reloadText);
}

void Player::handleReload() {
    if (weapon.isReloading()) {
        displayReloadText();
        weapon.reload();
    }
}

void Player::update() {
    handleMove();
    handleReload();
    drawCrosshair();
    handleShooting();
    draw();
}

void Player::listenForKeyPresses(std::optional<Event> event) {
    if (auto const e = event->getIf<Event::KeyPressed>()) {
        if (e->code == Keyboard::Key::W) {
            pressedKeys.W = true;
        } else if (e->code == Keyboard::Key::S) {
            pressedKeys.S = true;
        } else if (e->code == Keyboard::Key::A) {
            pressedKeys.A = true;
        } else if (e->code == Keyboard::Key::D) {
            pressedKeys.D = true;
        } else if (e->code == Keyboard::Key::R) {
            weapon.reload();
        }
    } else if (auto const e = event->getIf<Event::KeyReleased>()) {
        if (e->code == Keyboard::Key::W) {
            pressedKeys.W = false;
        } else if (e->code == Keyboard::Key::S) {
            pressedKeys.S = false;
        } else if (e->code == Keyboard::Key::A) {
            pressedKeys.A = false;
        } else if (e->code == Keyboard::Key::D) {
            pressedKeys.D = false;
        }
    } else if (auto const e = event->getIf<Event::MouseButtonPressed>()) {
        if (e->button == Mouse::Button::Left) {
            pressedKeys.LMB = true;
        }
    } else if (auto const e = event->getIf<Event::MouseButtonReleased>()) {
        if (e->button == Mouse::Button::Left) {
            lmbPressedAndReleased = true;
            pressedKeys.LMB = false;
        }
    }
}

void Player::handleShooting() {
    if (pressedKeys.LMB) {
        if (weapon.isAutomatic) {
            shoot();
        } else if (lmbPressedAndReleased) {
            shoot();
            lmbPressedAndReleased = false;
        }
    }
}

void Player::handleMove() {
    auto MAX_VELOCITY = 2.5f;
    //account for floating point inaccuracy
    if (velocity.y > -0.1f && velocity.y < 0.1f) {
        velocity.y = 0.0f;
    }
    if (velocity.x > -0.1f && velocity.x < 0.1f) {
        velocity.x = 0.0f;
    }
    if (pressedKeys.W) {
        if (velocity.y > 0.0f) {
            velocity.y = 0.0f;
        }
        if (velocity.y > -MAX_VELOCITY) {
            velocity.y += -0.1f;
        }
    } else if (velocity.y < 0.0f) {
        velocity.y += 0.1f;
    }
    if (pressedKeys.S) {
        if (velocity.y < 0.0f) {
            velocity.y = 0.0f;
        }
        if (velocity.y < MAX_VELOCITY) {
            velocity.y += 0.1f;
        }
    } else if (velocity.y > 0.0f) {
        velocity.y += -0.1f;
    }
    if (pressedKeys.A) {
        if (velocity.x > 0.0f) {
            velocity.x = 0.0f;
        }
        if (velocity.x > -MAX_VELOCITY) {
            velocity.x += -0.1f;
        }
    } else if (velocity.x < 0.0f) {
        velocity.x += 0.1;
    }
    if (pressedKeys.D) {
        if (velocity.x < 0.0f) {
            velocity.x = 0.0f;
        }
        if (velocity.x < MAX_VELOCITY) {
            velocity.x += 0.1f;
        }
    } else if (velocity.x > 0.0f) {
        velocity.x += -0.1f;
    }
    sprite.move(velocity);
}

void Player::draw() {
    window.draw(sprite);
}
