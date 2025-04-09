#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

struct PressedKeys {
    bool W;
    bool S;
    bool A;
    bool D;
};

class Player {
public:
    Player(RenderWindow& window);
    void handleMove();
    void listenForKeyPresses(std::optional<Event> event);
    void draw();
    void update();
private:
    PressedKeys pressedKeys;
    CircleShape sprite;
    RenderWindow& window;
    Vector2f velocity;
};



#endif //PLAYER_H
