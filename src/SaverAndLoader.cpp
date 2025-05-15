#include "SaverAndLoader.h"

#include <fstream>

SaverAndLoader::SaverAndLoader(Player &player, EnemyController &enemy_controller,
                               Map_parser &map_parser): player(player),
                                                        enemy_controller(enemy_controller),
                                                        map_parser(map_parser) {
}

void SaverAndLoader::savePlayer() {
    std::ofstream playerFile("player.dat");
    playerFile << player.getHp() << '\n';
    playerFile << player.getWeapon().getId() << '\n';
}
void SaverAndLoader::saveMaps() {
    std::ofstream mapsFile("maps.dat");
    for (auto const &m : map_parser.getMapOrder()) {
        mapsFile << m << '\n';
    }
}

void SaverAndLoader::save() {
    savePlayer();
    saveMaps();
}

void SaverAndLoader::loadPlayer() {
    std::ifstream in("player.dat");
    std::string hp;
    std::string weaponId;
    in >> hp >> weaponId;
    player.setHp(std::stoi(hp));
    player.setWeapon(std::stoi(weaponId));
}

void SaverAndLoader::load() {
    loadPlayer();
}
