#ifndef SAVERANDLOADER_H
#define SAVERANDLOADER_H
#include "EnemyController.h"
#include "Map_parser.h"


class SaverAndLoader {
public:
    SaverAndLoader(Player &player, EnemyController &enemy_controller, Map_parser &map_parser,ProjectileManager &projectile_manager);

    void savePlayer();

    void saveMaps();

    void save();

    void loadPlayer();

    void load();
private:
    Player &player;
    ProjectileManager &projectile_manager;
    EnemyController &enemy_controller;
    Map_parser &map_parser;
};



#endif //SAVERANDLOADER_H
