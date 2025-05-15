#ifndef MAP_PARSER_H
#define MAP_PARSER_H
#include <vector>
#include <deque>

#include "Terrain.h"
#include "EnemyController.h"


class Map_parser {
public:
    Map_parser(sf::RenderWindow &window, EnemyController &enemy_controller, ProjectileManager &projectile_manager);
    void load_maps();

    void loadMap(std::filesystem::directory_entry const &path);

    void loadMapsFromSave(std::vector<std::string> const &maps);

    void load_enemy_layout(std::string &filename);

    void load_next_map();

    void load_current_map();

    void draw_current_map();

    std::vector<std::unique_ptr<Terrain>> &get_loaded_sprites();
    std::deque<std::string> &getMapOrder();

    void draw(const Drawable &drawable) const;
private:
    RenderWindow& window;
    std::vector<std::unique_ptr<Terrain>> loadedSprites = std::vector<std::unique_ptr<Terrain>>{};
    std::deque<std::vector<std::string>> maps = std::deque<std::vector<std::string>>{};
    std::deque<std::vector<std::string>> enemyLayouts;
    EnemyController &enemy_controller;
    ProjectileManager &projectile_manager;
    std::deque<std::string> mapOrder;
};



#endif //MAP_PARSER_H
