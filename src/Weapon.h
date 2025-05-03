
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
    Weapon(ProjectileManager &projectile_manager);
    void shoot(sf::Vector2f direction, sf::Vector2f position);
    bool isAutomatic;

    sf::Sprite &getSprite();
    weaponType randomWeaponType();

private:
    std::reference_wrapper<ProjectileManager> projectile_manager;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock shotCooldown;
    int maxAmmo;
    int ammo;
    int dmg;
    float firerate;
    float spread;
};



#endif //WEAPON_H
