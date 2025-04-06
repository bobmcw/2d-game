#include "player.h"

#include "SFML/Window/Keyboard.hpp"

using namespace sf;

Player::Player(RenderWindow &window)
    : window(window) {
    this->sprite = CircleShape(10);
    this->sprite.setPosition({500, 500});
    this->sprite.setFillColor(Color::White);
    this->window.draw(this->sprite);
    this->velocity = Vector2f(0, 0);
}

void Player::HandleMove() {
    //account for floating point inaccuracy
    if (this->velocity.y > -0.1f && this->velocity.y < 0.1f) {
        this->velocity.y = 0.0f;
    }
    if (this->velocity.x > -0.1f && this->velocity.x < 0.1f) {
        this->velocity.x = 0.0f;
    }
    if (isKeyPressed(Keyboard::Key::W)) {
        if (this->velocity.y > 0.0f) {
            this->velocity.y = 0.0f;
        }
        this->velocity.y += -0.1f;
    } else if (this->velocity.y < 0.0f) {
        this->velocity.y += 0.1f;
    }
    if (isKeyPressed(Keyboard::Key::S)) {
        if (this->velocity.y < 0.0f) {
            this->velocity.y = 0.0f;
        }
        this->velocity.y += 0.1f;
    } else if (this->velocity.y > 0.0f) {
        this->velocity.y += -0.1f;
    }
    if (isKeyPressed(Keyboard::Key::A)) {
        if (this->velocity.x > 0.0f) {
            this->velocity.x = 0.0f;
        }
        this->velocity.x += -0.1f;
    } else if (this->velocity.x < 0.0f) {
        this->velocity.x += 0.1;
    }
    if (isKeyPressed(Keyboard::Key::D)) {
        if (this->velocity.x < 0.0f) {
            this->velocity.x = 0.0f;
        }
        this->velocity.x += 0.1f;
    } else if (this->velocity.x > 0.0f) {
        this->velocity.x += -0.1f;
    }
    this->sprite.move(this->velocity);
}

void Player::draw() {
    this->window.draw(this->sprite);
}
