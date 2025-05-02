#include "Weapon.h"

#include "fmt/compile.h"
#include "SFML/Graphics/Texture.hpp"

Weapon::Weapon(weaponType type, ProjectileManager &projectile_manager): sprite(texture), projectile_manager(projectile_manager),shotCooldown(sf::Clock()) {
   texture = sf::Texture();
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
   assert(texture.loadFromFile("./Assets/textures/bullet.png"));
}
void Weapon::shoot(sf::Vector2f direction, sf::Vector2f position) {
   if (shotCooldown.getElapsedTime().asSeconds() > firerate) {
      projectile_manager.addProjectile(std::make_unique<Projectile>(direction,position));
      shotCooldown.restart();
   }
}


