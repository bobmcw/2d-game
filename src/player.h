#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

class Player {
public:
    Player(RenderWindow& window);
    void HandleMove(std::optional<Event>);
    void draw();
private:
    CircleShape sprite;
    RenderWindow& window;
};



#endif //PLAYER_H
