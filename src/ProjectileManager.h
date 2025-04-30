#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H
#include "Projectile.h"
#include "SFML/Graphics/RenderWindow.hpp"


class ProjectileManager {
public:
    ProjectileManager(sf::RenderWindow& window);
    void addProjectile(std::unique_ptr<Projectile> p);
    void updateProjectiles();
    std::vector<std::unique_ptr<Projectile>>& getProjectiles();

    std::__wrap_iter<std::unique_ptr<Projectile> *> removeProjectile(
        std::vector<std::unique_ptr<Projectile> >::iterator i);
private:
    std::vector<std::unique_ptr<Projectile>> projectiles;
    sf::RenderWindow& window;
};



#endif //PROJECTILEMANAGER_H
