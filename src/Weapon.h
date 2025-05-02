
#ifndef WEAPON_H
#define WEAPON_H
#include "ProjectileManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

enum class weaponType {
    pistol,
    ak47,
    ppbizon,
    uzi,
};

class Weapon {
public:
    Weapon(weaponType type, ProjectileManager &projectile_manager);
    void shoot(sf::Vector2f direction, sf::Vector2f position);

private:
    ProjectileManager &projectile_manager;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock shotCooldown;
    int maxAmmo;
    int ammo;
    bool isAutomatic;
    int dmg;
    float firerate;
    float spread;
};



#endif //WEAPON_H
