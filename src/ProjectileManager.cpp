
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
void ProjectileManager::addProjectile(Projectile* p) {
    this->projectiles.push_back(p);
}


