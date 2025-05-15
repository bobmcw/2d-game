#include <SFML/Graphics.hpp>

#include "Collision_detector.h"
#include "EnemyController.h"
#include "Map_parser.h"
#include "Menu.h"
#include "Player.h"
#include "UI.h"
#include "SaverAndLoader.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project",State::Fullscreen);
    window.setFramerateLimit(144);

    auto projectileManager = ProjectileManager(window);
    auto player = Player(window,projectileManager);
    auto enemyController = EnemyController(window, player);
    auto ui = UI(window,player);
    auto maploader = Map_parser(window,enemyController,projectileManager);
    auto saveManager = SaverAndLoader(player,enemyController,maploader);
    auto menu = Menu(window,saveManager,maploader);

    //maploader.load_maps();
    //saveManager.save();
    //maploader.load_next_map();

    auto collision_detector = Collision_detector(player, maploader.get_loaded_sprites(),projectileManager,enemyController,maploader,saveManager);

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
            menu.listenToKeyPresses(event);
        }
        if (!menu.isActive()) {
            //drawing objects
            maploader.draw_current_map();
            projectileManager.updateProjectiles();
            ui.update();
            //collision
            collision_detector.update();
            //updating objects
            player.update();
            enemyController.updateEnemies();
        }
        else {
            menu.displayMenu();
        }
        window.display();
    }
}
