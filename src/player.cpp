#include "player.h"

#include <iostream>

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Window.hpp"

using namespace sf;

Player::Player(RenderWindow& window)
    : window(window)
{
    this->sprite = CircleShape(10);
    this->sprite.setPosition({50,50});
    this->sprite.setFillColor(Color::White);
    this->window.draw(this->sprite);
}
void Player::HandleMove(std::optional<Event> event) {
        if (auto const e = event->getIf<Event::KeyPressed>())
        {
            switch (e->code) {
                case Keyboard::Key::W: {
                    this->sprite.move({0,-5});
                    break;
                }
                case Keyboard::Key::S: {
                    this->sprite.move({0,5});
                    break;
                }
                case Keyboard::Key::A: {
                    this->sprite.move({-5,0});
                    break;
                }
                case Keyboard::Key::D: {
                    this->sprite.move({5,0});
                    break;
                }
                default: break;
            }
    }
}
void Player::draw() {
    this->window.draw(this->sprite);
}

