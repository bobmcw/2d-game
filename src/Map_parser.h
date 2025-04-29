#ifndef MAP_PARSER_H
#define MAP_PARSER_H
#include <vector>

#include "Terrain.h"


class Map_parser {
public:
    Map_parser(sf::RenderWindow &window);
    void load_maps();
    void load_next_map();
    void draw_current_map();

    std::vector<Terrain *> &get_loaded_sprites();
private:
    sf::RenderWindow& window;
    std::vector<Terrain*> loadedSprites = std::vector<Terrain*>{};
    std::deque<std::vector<std::string>> maps = std::deque<std::vector<std::string>>{};
};



#endif //MAP_PARSER_H
