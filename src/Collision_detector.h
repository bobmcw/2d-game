#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
#include "Player.h"
#include "Terrain.h"


class Collision_detector {
public:
    Collision_detector(Player &player, std::vector<Terrain*> &loaded_terrain, ProjectileManager &projectile_manager);
    void checkColisionWithPlayer();
    void checkProjectilesCollision();
private:
    Player &player;
    std::vector<Terrain *> loaded_terrain;
    ProjectileManager &projectile_manager;
};



#endif //COLLISION_DETECTOR_H
