#include "player.h"

#include "SFML/Window/Keyboard.hpp"

using namespace sf;

Player::Player(RenderWindow &window)
    : window(window) {
    this->pressedKeys = PressedKeys();
    this->sprite = CircleShape(10);
    this->sprite.setPosition({500, 500});
    this->sprite.setFillColor(Color::White);
    this->window.draw(this->sprite);
    this->velocity = Vector2f(0, 0);
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
