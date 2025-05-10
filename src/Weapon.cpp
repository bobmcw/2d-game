#include "Weapon.h"

#include <random>
#include <cmath>
#include "fmt/base.h"
#include "SFML/Graphics/Texture.hpp"

Weapon::Weapon(weaponType type, ProjectileManager &projectile_manager): projectile_manager(
                                                                            std::ref(projectile_manager)),
                                                                        sprite(texture),
                                                                        shotCooldown(sf::Clock()), reloading(false), reloadTimer(sf::Clock()) {
    shotCooldown.start();
    reloadTimer.reset();
    texture = sf::Texture();
    switch (type) {
        case weaponType::pistol: {
            maxAmmo = 12;
            ammo = 12;
            isAutomatic = false;
            dmg = 1;
            firerate = 0.3;
            spread = 0;
            assert(texture.loadFromFile("Assets/textures/pistol.png"));
            break;
        }
        case weaponType::ak47: {
            maxAmmo = 30;
            ammo = 30;
            isAutomatic = true;
            dmg = 3;
            firerate = 0.1;
            spread = 30;
            assert(texture.loadFromFile("Assets/textures/ak-47.png"));
        }
        case weaponType::uzi: {
            maxAmmo = 15;
            ammo = 15;
            isAutomatic = true;
            dmg = 1;
            firerate = 0.05;
            spread = 60;
            assert(texture.loadFromFile("Assets/textures/uzi.png"));
        }
        case weaponType::ppbizon: {
            maxAmmo = 64;
            ammo = 64;
            isAutomatic = true;
            dmg = 1;
            firerate = 0.1;
            spread = 120;
            assert(texture.loadFromFile("Assets/textures/ppbizon.png"));
        }
    }
    sprite = sf::Sprite(texture);
    sprite.setPosition({500, 500});
}

Weapon::Weapon(ProjectileManager &projectile_manager): Weapon(randomWeaponType(), projectile_manager) {}

void Weapon::shoot(sf::Vector2f direction, sf::Vector2f position) {
    if (shotCooldown.getElapsedTime().asSeconds() > firerate && ammo > 0) {
        applyRandomSpread(direction, spread);
        projectile_manager.get().addProjectile(std::make_unique<Projectile>(direction, position));
        shotCooldown.restart();
        ammo--;
    }
}

void Weapon::applyRandomSpread(sf::Vector2<float> &v, float spread) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    float maxSpread = spread * (M_PI / 180.0f);

    std::uniform_real_distribution<> dist(-maxSpread / 2.0f, maxSpread / 2.0f);
    float angleOffset = dist(gen);

    float cosA = std::cos(angleOffset);
    float sinA = std::sin(angleOffset);

    float originalX = v.x;
    float originalY = v.y;

    //2D vector rotation formula
    //https://en.wikipedia.org/wiki/Rotation_matrix
    v.x = originalX * cosA - originalY * sinA;
    v.y = originalX * sinA + originalY * cosA;
}

void Weapon::reload() {
    if (!reloadTimer.isRunning()) {
        reloadTimer.start();
        reloading = true;
    } else if (reloadTimer.getElapsedTime().asSeconds() > 2) {
        reloadTimer.reset();
        ammo = maxAmmo;
        reloading = false;
        fmt::println("reloaded");
    }
}

sf::Sprite &Weapon::getSprite() {
    return sprite;
}
int Weapon::getAmmo() const {
    return ammo;
}
int Weapon::getMaxAmmo() const {
    return maxAmmo;
}
bool Weapon::isReloading() const {
    return reloading;
}
weaponType Weapon::randomWeaponType() {
    auto types = std::vector<weaponType>{weaponType::ak47, weaponType::pistol, weaponType::ppbizon, weaponType::uzi};
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(types.size() - 1));
    auto tmp = types[dist(gen)];
    return tmp;
}
