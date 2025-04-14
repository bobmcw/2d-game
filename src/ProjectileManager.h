#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H
#include "Projectile.h"
#include "SFML/Graphics/RenderWindow.hpp"


class ProjectileManager {
public:
    ProjectileManager(sf::RenderWindow& window);
    void addProjectile(Projectile* p);
    void updateProjectiles();
private:
    std::vector<Projectile*> projectiles;
    sf::RenderWindow& window;
};



#endif //PROJECTILEMANAGER_H
