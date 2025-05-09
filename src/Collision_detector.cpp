#include "Collision_detector.h"

#include <iostream>

#include "fmt/args.h"

Collision_detector::Collision_detector(Player &player, std::vector<std::unique_ptr<Terrain>> &loaded_terrain,
                                       ProjectileManager &projectile_manager,
                                       EnemyController &enemy_controller, Map_parser &map_parser): player(player),
    enemy_controller(enemy_controller),
    loaded_terrain(loaded_terrain),
    projectile_manager(projectile_manager), map_parser(map_parser) {
}

void Collision_detector::checkColisionWithPlayer() {
    for (auto &t: this->loaded_terrain) {
        if (t == nullptr) {
            continue;
        }
        if (this->player.getSprite().getGlobalBounds().findIntersection((*t).getSprite().getGlobalBounds()) && (*t).
            hasCollision) {
            fmt::println("intersection");
            //from bottom
            if (this->player.getSprite().getPosition().y > (*t).getSprite().getPosition().y) {
                player.getSprite().setPosition({
                    this->player.getSprite().getPosition().x,
                    (*t).getSprite().getPosition().y + (*t).getSprite().getGlobalBounds().size.y
                });
            }
            //from top
            else if (this->player.getSprite().getPosition().y < (*t).getSprite().getPosition().y) {
                player.getSprite().setPosition({
                    this->player.getSprite().getPosition().x,
                    (*t).getSprite().getPosition().y - (*t).getSprite().getGlobalBounds().size.y
                });
            }
            //from right
            else if (this->player.getSprite().getPosition().x > (*t).getSprite().getPosition().x) {
                player.getSprite().setPosition({
                    (*t).getSprite().getPosition().x + (*t).getSprite().getGlobalBounds().size.x,
                    this->player.getSprite().getPosition().y
                });
            }
            //from left
            else if (this->player.getSprite().getPosition().x < (*t).getSprite().getPosition().x) {
                player.getSprite().setPosition({
                    (*t).getSprite().getPosition().x - (*t).getSprite().getGlobalBounds().size.x,
                    this->player.getSprite().getPosition().y
                });
            }
        } else if (this->player.getSprite().getGlobalBounds().findIntersection((*t).getSprite().getGlobalBounds())) {
            if (auto o = dynamic_cast<Openable *>(t.get())) {
                if (o->isOpened()) {
                    std::cout << "next lvl";
                    this->map_parser.load_next_map();
                    this->player.getSprite().setPosition({500, 500});
                }
            }
        }
    }
}

void Collision_detector::checkProjectilesCollision() {
    auto iterator = projectile_manager.getProjectiles().begin();
    while (iterator != projectile_manager.getProjectiles().end()) {
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
            //this should propably be somewhere else
            else if (this->enemy_controller.getEnemies().empty()) {
                fmt::println("all enemies killed");
                if (auto o = dynamic_cast<Openable *>(t.get())) {
                    o->open();
                }
            }
        }
            for (auto &e: this->enemy_controller.getEnemies()) {
                if ((*iterator)->sprite.getGlobalBounds().findIntersection(e->getSprite().getGlobalBounds())) {
                    e->takeDamage();
                    iterator = this->projectile_manager.removeProjectile(iterator);
                    if (!*iterator) {
                        return;
                    }
                }
            }
    ++iterator;
    }
}
