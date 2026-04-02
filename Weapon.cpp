#include "Weapon.h"
#include <cstdlib>

// --- Constructors ---

// Takes name, min/max value for damage
Weapon::Weapon(std::string name, int minValue, int maxValue)
    : name(name), minDamage(minValue), maxDamage(maxValue) {}

// Default
Weapon::Weapon() : name("Fists"), minDamage(1), maxDamage(3) {}

// --- Getters ---
std::string Weapon::getName() const {return name;}
int Weapon::getMinDamage() const {return minDamage;}
int Weapon::getMaxDamage() const {return maxDamage;}

// --- Methods ---
// Randomizer for damage output
int Weapon::rollDamage() const {
    // Returns min + (random % range)
    return minDamage + (rand() % (maxDamage - minDamage + 1));
}


