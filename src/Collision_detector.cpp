#include "Collision_detector.h"

#include <iostream>
#include <random>

Collision_detector::Collision_detector(Player &player, std::vector<std::unique_ptr<Terrain> > &loaded_terrain,
                                       ProjectileManager &projectile_manager,
                                       EnemyController &enemy_controller, Map_parser &map_parser, SaverAndLoader &saveManager): player(player), saveManager(saveManager),
    hatch(nullptr), reward(Weapon( std::ref(projectile_manager))),
    enemy_controller(enemy_controller),
    loaded_terrain(loaded_terrain),
    projectile_manager(projectile_manager), map_parser(map_parser), rewardPickedUp(false) {}

void Collision_detector::handleEndOfLvl() {
    if (enemy_controller.getEnemies().empty()) {
        for (auto &t: loaded_terrain) {
            if (auto o = dynamic_cast<Openable *>(t.get())) {
                o->open();
                hatch = o;
            }
        }
        spawnReward();
        checkRewardCollision();
    }
}

void Collision_detector::spawnReward() {
    if (!rewardPickedUp) {
        map_parser.draw(reward.getSprite());
    }
}

void Collision_detector::checkRewardCollision() {
   if (reward.getSprite().getGlobalBounds().findIntersection(player.getSprite().getGlobalBounds()) && !rewardPickedUp) {
       player.setWeapon(reward);
       rewardPickedUp = true;
   }
}


void Collision_detector::update() {
    checkProjectilesCollision();
    checkColisionWithPlayer();
    handleEndOfLvl();
}

void Collision_detector::checkColisionWithPlayer() {
    for (auto &t: this->loaded_terrain) {
        if (t == nullptr) {
            continue;
        }
        if (player.getSprite().getGlobalBounds().findIntersection(t->getSprite().getGlobalBounds()) && (*t).hasCollision) {
            auto playerBounds = player.getSprite().getGlobalBounds();
            auto tileBounds = t->getSprite().getGlobalBounds();
            float overlapLeft   = (playerBounds.position.x + playerBounds.size.x) - tileBounds.position.x;
            float overlapRight  = (tileBounds.position.x + tileBounds.size.x) - playerBounds.position.x;
            float overlapTop    = (playerBounds.position.y + playerBounds.size.y) - tileBounds.position.y;
            float overlapBottom = (tileBounds.position.y + tileBounds.size.y) - playerBounds.position.y;

            bool resolveOnX = std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom);

            if (resolveOnX) {
                if (overlapLeft < overlapRight) {
                    player.getSprite().move({ -overlapLeft, 0.f }); // From left
                } else {
                    player.getSprite().move({ overlapRight, 0.f }); // From right
                }
            } else {
                if (overlapTop < overlapBottom) {
                    player.getSprite().move({ 0.f, -overlapTop }); // From top
                } else {
                    player.getSprite().move({ 0.f, overlapBottom }); // From bottom
                }
            }
        }
        //check for collision with the hatch
        else if (this->player.getSprite().getGlobalBounds().findIntersection((*t).getSprite().getGlobalBounds())) {
            if (auto o = dynamic_cast<Openable *>(t.get())) {
                if (o->isOpened()) {
                    std::cout << "next lvl";
                    reward = Weapon(std::ref(projectile_manager));
                    reward.rebindTexture();
                    rewardPickedUp = false;
                    this->map_parser.load_next_map();
                    hatch = nullptr;
                    this->player.getSprite().setPosition({750, 750});
                    projectile_manager.getProjectiles().clear();
                    saveManager.save();
                }
            }
        }
    }
    for (auto &e: enemy_controller.getEnemies()) {
        if (player.getSprite().getGlobalBounds().findIntersection(e->getSprite().getGlobalBounds())) {
            player.takeDamage();
        }
    }
}

void Collision_detector::checkProjectilesCollision() {
    auto iterator = projectile_manager.getProjectiles().begin();
    while (iterator != projectile_manager.getProjectiles().end()) {
        //check for collision with terrain
        for (auto &t: this->loaded_terrain) {
            if (t->hasCollision) {
                if ((*iterator)->sprite.getGlobalBounds().findIntersection(t->getSprite().getGlobalBounds())) {
                    iterator = projectile_manager.removeProjectile(iterator);
                    if (!*iterator) {
                        return;
                    }
                    break;
                }
            }
        }
        //check for collision with enemies
        for (auto &e: this->enemy_controller.getEnemies()) {
            if ((*iterator)->sprite.getGlobalBounds().findIntersection(e->getSprite().getGlobalBounds())) {
                e->takeDamage();
                iterator = this->projectile_manager.removeProjectile(iterator);
                if (!*iterator) {
                    return;
                }
            }
        }
        if ((*iterator)->sprite.getGlobalBounds().findIntersection(player.getSprite().getGlobalBounds())) {
            player.takeDamage();
            iterator = this->projectile_manager.removeProjectile(iterator);
            if (!*iterator) {
                return;
            }
        }
        ++iterator;
    }
}
