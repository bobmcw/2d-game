#include "Player.h"

#include <iostream>

#include "SFML/Window/Keyboard.hpp"
#include <cmath>


using namespace sf;

Player::Player(RenderWindow &window, ProjectileManager &projectile_manager)
    : sprite(this->texture), window(window), projectile_manager(projectile_manager), hp(10), font("Assets/ByteBounce.ttf"), reloadText(font),
      weapon(Weapon(weaponType::ak47, projectile_manager)) {
    this->pressedKeys = PressedKeys();
    this->texture = Texture();
    if (!this->texture.loadFromFile("Assets/textures/player.png")) {
        std::cerr << "failed to load /Assets/textures/player.png";
    }
    this->sprite = Sprite(this->texture);
    this->sprite.setPosition({750, 750});
    this->sprite.setTextureRect(sf::IntRect({0, 0}, {50, 50}));
    this->window.draw(this->sprite);
    this->velocity = Vector2f(0, 0);
    lmbPressedAndReleased = true;
    reloadText.setString("reloading...");
    reloadText.setCharacterSize(20);
}

Sprite &Player::getSprite() {
    return this->sprite;
}

int Player::getHp() {
    return hp;
}

void Player::takeDamage() {
    if (eyeFrameClock.isRunning() && eyeFrameClock.getElapsedTime().asSeconds() > 0.75) {
        hp -= 1;
        eyeFrameClock.restart();
    }
}

void Player::setWeapon(Weapon w) {
    this->weapon = std::move(w);
}

Weapon &Player::getWeapon() {
    return weapon;
}

void Player::drawCrosshair() {
    auto croshairVisualization = CircleShape(10);
    croshairVisualization.setFillColor(Color::Green);
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    auto delta = mousePos - this->sprite.getPosition();
    auto angle = std::atan2(delta.y, delta.x);
    //https://en.sfml-dev.org/forums/index.php?topic=5992.0
    croshairVisualization.setPosition(
        this->sprite.getGlobalBounds().getCenter() + Vector2f(50 * cos(angle), 50 * sin(angle)));
    this->window.draw(croshairVisualization);
}

void Player::shoot() {
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    auto delta = mousePos - this->sprite.getPosition();
    auto angle = std::atan2(delta.y, delta.x);
    //https://en.sfml-dev.org/forums/index.php?topic=5992.0
    auto position = this->sprite.getGlobalBounds().getCenter() + Vector2f(50 * cos(angle), 50 * sin(angle));
    auto direction = sf::Vector2f(std::cos(angle), std::sin(angle));
    if (!weapon.isReloading()) {
        weapon.shoot(direction, position);
    }
    //this->projectile_manager.addProjectile(std::make_unique<Projectile>(direction, position));
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
    this->handleMove();
    handleReload();
    this->drawCrosshair();
    handleShooting();
    this->draw();
}

void Player::listenForKeyPresses(std::optional<Event> event) {
    if (auto const e = event->getIf<Event::KeyPressed>()) {
        if (e->code == Keyboard::Key::W) {
            this->pressedKeys.W = true;
        } else if (e->code == Keyboard::Key::S) {
            this->pressedKeys.S = true;
        } else if (e->code == Keyboard::Key::A) {
            this->pressedKeys.A = true;
        } else if (e->code == Keyboard::Key::D) {
            this->pressedKeys.D = true;
        } else if (e->code == Keyboard::Key::R) {
            weapon.reload();
        }
    } else if (auto const e = event->getIf<Event::KeyReleased>()) {
        if (e->code == Keyboard::Key::W) {
            this->pressedKeys.W = false;
        } else if (e->code == Keyboard::Key::S) {
            this->pressedKeys.S = false;
        } else if (e->code == Keyboard::Key::A) {
            this->pressedKeys.A = false;
        } else if (e->code == Keyboard::Key::D) {
            this->pressedKeys.D = false;
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
    auto MAX_VELOCITY = 3.0f;
    //account for floating point inaccuracy
    if (this->velocity.y > -0.1f && this->velocity.y < 0.1f) {
        this->velocity.y = 0.0f;
    }
    if (this->velocity.x > -0.1f && this->velocity.x < 0.1f) {
        this->velocity.x = 0.0f;
    }
    if (this->pressedKeys.W) {
        if (this->velocity.y > 0.0f) {
            this->velocity.y = 0.0f;
        }
        if (this->velocity.y > -MAX_VELOCITY) {
            this->velocity.y += -0.1f;
        }
    } else if (this->velocity.y < 0.0f) {
        this->velocity.y += 0.1f;
    }
    if (this->pressedKeys.S) {
        if (this->velocity.y < 0.0f) {
            this->velocity.y = 0.0f;
        }
        if (this->velocity.y < MAX_VELOCITY) {
            this->velocity.y += 0.1f;
        }
    } else if (this->velocity.y > 0.0f) {
        this->velocity.y += -0.1f;
    }
    if (this->pressedKeys.A) {
        if (this->velocity.x > 0.0f) {
            this->velocity.x = 0.0f;
        }
        if (this->velocity.x > -MAX_VELOCITY) {
            this->velocity.x += -0.1f;
        }
    } else if (this->velocity.x < 0.0f) {
        this->velocity.x += 0.1;
    }
    if (this->pressedKeys.D) {
        if (this->velocity.x < 0.0f) {
            this->velocity.x = 0.0f;
        }
        if (this->velocity.x < MAX_VELOCITY) {
            this->velocity.x += 0.1f;
        }
    } else if (this->velocity.x > 0.0f) {
        this->velocity.x += -0.1f;
    }
    this->sprite.move(this->velocity);
}

void Player::draw() {
    this->window.draw(this->sprite);
}
