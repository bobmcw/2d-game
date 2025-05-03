#include "Weapon.h"

#include <random>

#include "fmt/compile.h"
#include "SFML/Graphics/Texture.hpp"

Weapon::Weapon(weaponType type, ProjectileManager &projectile_manager): projectile_manager(
                                                                           std::ref(projectile_manager)), sprite(texture),
                                                                        shotCooldown(sf::Clock()) {
   shotCooldown.start();
   switch (type) {
      case weaponType::pistol: {
         maxAmmo = 12;
         isAutomatic = false;
         dmg = 1;
         firerate = 0.3;
         spread = 0;
         break;
      }
      default: ;
   }
   texture = sf::Texture();
   assert(texture.loadFromFile("Assets/textures/enemy.png"));
   sprite = sf::Sprite(texture);
   sprite.setPosition({10, 500});
}

Weapon::Weapon(ProjectileManager &projectile_manager): Weapon(randomWeaponType(),projectile_manager){}

void Weapon::shoot(sf::Vector2f direction, sf::Vector2f position) {
   if (shotCooldown.getElapsedTime().asSeconds() > firerate) {
      projectile_manager.get().addProjectile(std::make_unique<Projectile>(direction,position));
      shotCooldown.restart();
   }
}

sf::Sprite &Weapon::getSprite() {
   return sprite;
}

weaponType Weapon::randomWeaponType() {
    auto types = std::vector<weaponType>{weaponType::ak47, weaponType::pistol, weaponType::ppbizon, weaponType::uzi};
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(types.size() - 1));
   return types[dist(gen)];
}


