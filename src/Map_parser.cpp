#include "Map_parser.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <random>

#include "EnemyController.h"
#include "Terrain.h"
#include "fmt/ranges.h"

namespace fs = std::filesystem;

Map_parser::Map_parser(RenderWindow &window, EnemyController &enemy_controller,
                       ProjectileManager &projectile_manager) : window(window), enemy_controller(enemy_controller),
                                                                projectile_manager(projectile_manager) {
    maps = std::deque<std::vector<std::string> >{};
    loadedSprites = std::vector<std::unique_ptr<Terrain> >{};
    enemyLayouts = std::deque<std::vector<std::string> >();
}

std::vector<std::unique_ptr<Terrain> > &Map_parser::get_loaded_sprites() {
    return loadedSprites;
}

std::deque<std::string> &Map_parser::getMapOrder() {
    return mapOrder;
}

void Map_parser::draw(const Drawable &drawable) const {
    window.draw(drawable);
}


void Map_parser::load_maps() {
    maps.clear();
    enemyLayouts.clear();
    mapOrder.clear();
    loadedSprites.clear();
    enemy_controller.getEnemies().clear();
    projectile_manager.getProjectiles().clear();
    loadMap(std::filesystem::directory_entry(fs::path("./Assets/special_maps/start.map")));
    auto vec = std::vector<std::filesystem::directory_entry>();
    for (auto const &mapFile: fs::directory_iterator(fs::path("./Assets/maps"))) {
        //loadMap(mapFile);
        vec.push_back(mapFile);
    }
    auto rd = std::random_device{};
    auto rng = std::default_random_engine{rd()};
    std::ranges::shuffle(vec, rng);
    for (auto const &m: vec) {
        loadMap(m);
    }
    loadMap(std::filesystem::directory_entry(fs::path("./Assets/special_maps/boss.map")));
}

void Map_parser::loadMap(std::filesystem::directory_entry const &mapFile) {
    auto line = std::string();
    auto map = std::fstream(mapFile.path());
    auto stringMap = std::vector<std::string>();
    while (std::getline(map, line)) {
        stringMap.push_back(line);
    }
    mapOrder.push_back(mapFile.path().string());
    maps.push_back(stringMap);
    auto enemyPath = std::string(mapFile.path().filename().replace_extension("").generic_string());
    load_enemy_layout(enemyPath);
}

void Map_parser::loadMapsFromSave(std::vector<std::string> const &maps) {
    this->maps.clear();
    enemyLayouts.clear();
    mapOrder.clear();
    loadedSprites.clear();
    enemy_controller.getEnemies().clear();
    projectile_manager.getProjectiles().clear();
    this->maps.clear();
    enemyLayouts.clear();
    enemy_controller.getEnemies().clear();
    for (auto const &m: maps) {
        loadMap(std::filesystem::directory_entry(fs::path(m)));
    }
}

void Map_parser::load_enemy_layout(std::string &filename) {
    auto vec = std::vector<std::string>();
    if (std::fstream f(std::fstream("./Assets/enemy_layouts/" + filename + ".enemies")); f.is_open()) {
        auto line = std::string();
        while (std::getline(f, line)) {
            vec.push_back(line);
        }
        enemyLayouts.push_back(vec);
    } else {
        enemyLayouts.push_back(std::vector<std::string>());
    }
}

void Map_parser::load_next_map() {
    maps.pop_front();
    mapOrder.pop_front();
    enemyLayouts.pop_front();
    load_current_map();
}

void Map_parser::load_current_map() {
    loadedSprites.clear();
    auto startX = 100;
    auto x = 100;
    auto y = 100;
    auto map = maps.front();
    for (auto &line: map) {
        for (auto c: line) {
            switch (c) {
                case 'W': {
                    loadedSprites.push_back(std::make_unique<Wall>(window, x, y));
                    break;
                }
                case 'F': {
                    loadedSprites.push_back(std::make_unique<Floor>(window, x, y));
                    break;
                }
                case 'H': {
                    loadedSprites.push_back(std::make_unique<Hatch>(window, x, y));
                    break;
                }
                default: {
                    fmt::println("invalid symbol {}", c);
                }
            }
            x += 50;
        }
        x = startX;
        y += 50;
    }
    for (auto &s: enemyLayouts.front()) {
        //split by space
        auto vals = std::vector<std::string>();
        std::istringstream stream(s);
        auto word = std::string();
        while (stream >> word) {
            vals.push_back(word);
        }

        if (vals.size() == 3) {
            if (vals.front() == 'E') {
                enemy_controller.addEnemy(std::make_unique<Enemy>(std::stof(vals[1]), std::stof(vals[2])));
            } else if (vals.front() == 'S') {
                enemy_controller.addEnemy(
                    std::make_unique<Shooting_enemy>(std::stof(vals[1]), std::stof(vals[2]), projectile_manager));
            } else if (vals.front() == 'B') {
                enemy_controller.addEnemy(
                    std::make_unique<Boss>(std::stof(vals[1]), std::stof(vals[2]), projectile_manager));
            } else {
                fmt::println("invalid enemy type: {}", vals.front());;
            }
        }
    }
}

void Map_parser::draw_current_map() {
    for (auto &t: loadedSprites) {
        t->draw();
    }
}
