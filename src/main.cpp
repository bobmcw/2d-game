#include <SFML/Graphics.hpp>

#include "Collision_detector.h"
#include "map_parser.h"
#include "Player.h"
#include "Terrain.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    auto player = Player(window);
    auto maploader = Map_parser(window);
    maploader.load_maps();
    maploader.load_next_map(400,400);
    auto collision_detector = Collision_detector(player, maploader.get_loaded_sprites());
    while (window.isOpen())
    {
        window.clear();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            player.listenForKeyPresses(event);
        }
        collision_detector.checkColisionWithPlayer();
        maploader.draw_current_map();
        player.update();
        window.display();
    }
}
