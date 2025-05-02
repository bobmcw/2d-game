#include "Weapon.h"

#include "fmt/compile.h"
#include "SFML/Graphics/Texture.hpp"

Weapon::Weapon(weaponType type, ProjectileManager &projectile_manager): sprite(texture), projectile_manager(projectile_manager) {
   texture = sf::Texture();
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
   projectile_manager.addProjectile(std::make_unique<Projectile>(direction,position));
}

