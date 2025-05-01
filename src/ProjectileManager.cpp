
#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(sf::RenderWindow &window): window(window) {
        this->projectiles = std::vector<std::unique_ptr<Projectile>>();
}

void ProjectileManager::updateProjectiles() {
    for (auto &p : this->projectiles) {
        p->sprite.move(p->velocity);
        this->window.draw(p->sprite);
    }
}

std::vector<std::unique_ptr<Projectile>>& ProjectileManager::getProjectiles() {
    return this->projectiles;
}

std::vector<std::unique_ptr<Projectile>>::iterator ProjectileManager::removeProjectile(
    std::vector<std::unique_ptr<Projectile> >::iterator i) {
    return projectiles.erase(i);
}

void ProjectileManager::addProjectile(std::unique_ptr<Projectile> p) {
    this->projectiles.push_back(std::move(p));
}


