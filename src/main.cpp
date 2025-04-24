#include <SFML/Graphics.hpp>

#include "Collision_detector.h"
#include "EnemyController.h"
#include "Map_parser.h"
#include "Player.h"
#include "Terrain.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project",State::Fullscreen);
    window.setFramerateLimit(144);

    auto projectileManager = ProjectileManager(window);
    auto player = Player(window,projectileManager);
    auto enemyController = EnemyController(window, player);

    auto maploader = Map_parser(window);
    maploader.load_maps();
    maploader.load_next_map(100,100);

    auto collision_detector = Collision_detector(player, maploader.get_loaded_sprites(),projectileManager);

    enemyController.addEnemy(new Enemy(100,100));
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
        //drawing objects
        maploader.draw_current_map();
        projectileManager.updateProjectiles();
        collision_detector.checkProjectilesCollision();
        enemyController.updateEnemies();
        collision_detector.checkColisionWithPlayer();
        player.update();
        window.display();
    }
}
