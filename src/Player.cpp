#include "Player.h"

#include <iostream>

#include "fmt/args.h"
#include "SFML/Window/Keyboard.hpp"

using namespace sf;

Player::Player(RenderWindow &window)
    : sprite(this->texture), window(window) {
    this->pressedKeys = PressedKeys();
    this->texture = Texture();
    if (!this->texture.loadFromFile("Assets/textures/player.png")) {
        std::cerr << "failed to load /Assets/textures/player.png";
    }
    this->sprite = Sprite(this->texture);
    this->sprite.setPosition({500, 500});
    this->sprite.setTextureRect(sf::IntRect({0, 0}, {50, 50}));
    this->window.draw(this->sprite);
    this->velocity = Vector2f(0, 0);
}
Sprite& Player::getSprite() {
    return this->sprite;
}

void Player::update() {
    this->handleMove();
    this->draw();
}
void Player::listenForKeyPresses(std::optional<Event> event) {
   if (auto const e = event->getIf<Event::KeyPressed>()) {
        if (e->code == Keyboard::Key::W) {
            this->pressedKeys.W = true;
        }
        else if (e->code == Keyboard::Key::S) {
            this->pressedKeys.S = true;
        }
        else if (e->code == Keyboard::Key::A) {
            this->pressedKeys.A = true;
        }
        else if (e->code == Keyboard::Key::D) {
            this->pressedKeys.D = true;
        }
   }
    else if (auto const e = event->getIf<Event::KeyReleased>()) {
        if (e->code == Keyboard::Key::W) {
            this->pressedKeys.W = false;
        }
        else if (e->code == Keyboard::Key::S) {
            this->pressedKeys.S = false;
        }
        else if (e->code == Keyboard::Key::A) {
            this->pressedKeys.A = false;
        }
        else if (e->code == Keyboard::Key::D) {
            this->pressedKeys.D = false;
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
