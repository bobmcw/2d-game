
#include "Collision_detector.h"

#include "fmt/args.h"

Collision_detector::Collision_detector(Player &player, std::vector<Terrain*> &loaded_terrain): player(player),
                                                                                               loaded_terrain(loaded_terrain) {
}


void Collision_detector::checkColisionWithPlayer() {
    // fmt::println("wall x:{} y:{}",this->loaded_terrain[0]->getSprite().getGlobalBounds().position.x, this->loaded_terrain[0]->getSprite().getGlobalBounds().position.y);
    // fmt::println("player x:{} y:{}",player.getSprite().getGlobalBounds().position.x, player.getSprite().getGlobalBounds().position.y);
    // fmt::println("intersection : {}", this->loaded_terrain[0]->getSprite().getGlobalBounds().findIntersection(this->player.getSprite().getGlobalBounds()) != std::nullopt);
    for (auto t: this->loaded_terrain) {
        if (this->player.getSprite().getGlobalBounds().findIntersection(t->getSprite().getGlobalBounds()) && t->hasCollision) {
            fmt::println("intersection");
            //from bottom
            if (this->player.getSprite().getPosition().y > t->getSprite().getPosition().y) {
                player.getSprite().setPosition({this->player.getSprite().getPosition().x, t->getSprite().getPosition().y + t->getSprite().getGlobalBounds().size.y});
            }
            //from top
            else if(this->player.getSprite().getPosition().y < t->getSprite().getPosition().y) {
                player.getSprite().setPosition({this->player.getSprite().getPosition().x, t->getSprite().getPosition().y - t->getSprite().getGlobalBounds().size.y});
            }
            //from right
            else if (this->player.getSprite().getPosition().x > t->getSprite().getPosition().x) {
                player.getSprite().setPosition({t->getSprite().getPosition().x + t->getSprite().getGlobalBounds().size.x, this->player.getSprite().getPosition().y});
            }
            //from left
            else if(this->player.getSprite().getPosition().x < t->getSprite().getPosition().x) {
                player.getSprite().setPosition({t->getSprite().getPosition().x - t->getSprite().getGlobalBounds().size.x, this->player.getSprite().getPosition().y});
            }
        }
    }
}