#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

class Player {
public:
    Player(RenderWindow& window);
    void HandleMove();
    void draw();
private:
    CircleShape sprite;
    RenderWindow& window;
    Vector2f velocity;
};



#endif //PLAYER_H
