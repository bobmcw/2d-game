#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
#include "EnemyController.h"
#include "Map_parser.h"
#include "Player.h"
#include "Terrain.h"


class Collision_detector {
public:
    Collision_detector(Player &player, std::vector<Terrain*> &loaded_terrain, ProjectileManager &projectile_manager, EnemyController &enemy_controller, Map_parser &map_parser);
    void checkColisionWithPlayer();
    void checkProjectilesCollision();
private:
    Player &player;
    std::vector<Terrain *> &loaded_terrain;
    ProjectileManager &projectile_manager;
    EnemyController &enemy_controller;
    Map_parser &map_parser;
};



#endif //COLLISION_DETECTOR_H
