/*
 * Weapon is a class that builds Weapon objects, which are owned by Fighters.
 * They have a damage range, as well as a name. Weapons can be customized via
 * the config files for players and enemies, respectively.
 */

#ifndef M2OEP_GLATTANZ_WEAPON_H
#define M2OEP_GLATTANZ_WEAPON_H


#include <string>

class Weapon {
private:
    // --- Variables ---
    std::string name;
    int minDamage;
    int maxDamage;

public:
    // --- Constructors ---
    // Takes name, min/max value for damage
    Weapon(std:: string name, int minValue, int maxValue);

    // Default
    Weapon();

    // --- Getters ---
    std::string getName() const;
    int getMinDamage() const;
    int getMaxDamage() const;

    // --- Methods ---
    // Randomizer for damage output
    int rollDamage() const;
};


#endif //M2OEP_GLATTANZ_WEAPON_H