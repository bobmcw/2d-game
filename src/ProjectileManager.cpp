
#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(sf::RenderWindow &window): window(window) {
        this->projectiles = std::vector<Projectile*>();
}

void ProjectileManager::updateProjectiles() {
    for (auto p : this->projectiles) {
        p->sprite.move(p->velocity);
        this->window.draw(p->sprite);
    }
}

std::vector<Projectile *> ProjectileManager::getProjectiles() {
    return this->projectiles;
}

void ProjectileManager::removeProjectile(Projectile* p) {
    this->projectiles.erase(std::remove(this->projectiles.begin(),this->projectiles.end(),p), this->projectiles.end());
}

void ProjectileManager::addProjectile(Projectile* p) {
    this->projectiles.push_back(p);
}


