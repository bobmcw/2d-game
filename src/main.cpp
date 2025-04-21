#include <SFML/Graphics.hpp>

#include "Collision_detector.h"
#include "Map_parser.h"
#include "Player.h"
#include "Terrain.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project",State::Fullscreen);
    window.setFramerateLimit(144);
    auto projectileManager = ProjectileManager(window);
    auto player = Player(window,projectileManager);
    auto maploader = Map_parser(window);
    maploader.load_maps();
    maploader.load_next_map(100,100);
    auto collision_detector = Collision_detector(player, maploader.get_loaded_sprites(),projectileManager);
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
        maploader.draw_current_map();
        collision_detector.checkProjectilesCollision();
        projectileManager.updateProjectiles();
        collision_detector.checkColisionWithPlayer();
        player.update();
        window.display();
    }
}
