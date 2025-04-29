#include "Map_parser.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "Terrain.h"
#include "fmt/ranges.h"

namespace fs = std::filesystem;

Map_parser::Map_parser(sf::RenderWindow &window) : window(window) {
    this->maps = std::deque<std::vector<std::string>>{};
    this->loadedSprites = std::vector<Terrain*>{};
}

std::vector<Terrain *> &Map_parser::get_loaded_sprites() {
    return this->loadedSprites;
}


void Map_parser::load_maps() {
    for(auto const& mapFile : fs::directory_iterator(fs::path("./Assets/maps"))) {
        auto line = std::string();
        auto map = std::fstream(mapFile.path());
        auto stringMap = std::vector<std::string>();
        while (std::getline(map,line)) {
            stringMap.push_back( line );
        }
        this->maps.push_back(stringMap);
    }
        fmt::println("{}",this->maps);
}
void Map_parser::load_next_map() {
    this->loadedSprites.clear();
    maps.pop_front();
    auto startX = 100;
    auto x = 100;
    auto y = 100;
    auto map = this->maps.front();
    for (auto &line : map) {
        for (auto c : line) {
            switch (c) {
                case 'W': {
                    this->loadedSprites.push_back(new Wall(this->window,x,y));
                    break;
                }
                case 'F': {
                    this->loadedSprites.push_back(new Floor(this->window,x,y));
                    break;
                }
                case 'H': {
                    this->loadedSprites.push_back(new Hatch(this->window,x,y));
                    break;
                }
                default: {
                    fmt::println("invalid symbol {}",c);
                }
            }
            x += 50;
        }
        x = startX;
        y+= 50;
    }
}
void Map_parser::draw_current_map() {
    for (auto t : this->loadedSprites) {
        t->draw();
    }
}

