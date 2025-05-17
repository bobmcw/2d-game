#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
#include "EnemyController.h"
#include "Map_parser.h"
#include "Player.h"
#include "SaverAndLoader.h"
#include "Terrain.h"


class Collision_detector {
public:
    Collision_detector(Player &player, std::vector<std::unique_ptr<Terrain> > &loaded_terrain,
                       ProjectileManager &projectile_manager, EnemyController &enemy_controller, Map_parser &map_parser,
                       SaverAndLoader &saveManager);

    void handleEndOfLvl();

    void spawnReward();

    void checkRewardCollision();

    void update();

    void checkColisionWithPlayer();

    void checkProjectilesCollision();

private:
    Player &player;
    SaverAndLoader &saveManager;
    std::vector<std::unique_ptr<Terrain> > &loaded_terrain;
    ProjectileManager &projectile_manager;
    EnemyController &enemy_controller;
    Map_parser &map_parser;
    Openable *hatch;
    Weapon reward;
    bool rewardPickedUp;
};


#endif //COLLISION_DETECTOR_H
