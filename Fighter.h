/*
 * The Fighter class is an abstract parent class for the Player and Enemy classes.
 * Both players and enemies can be customized within their respective config files.
 */

#ifndef M2OEP_GLATTANZ_FIGHTER_H
#define M2OEP_GLATTANZ_FIGHTER_H

#include <string>
#include <iostream>
#include "Weapon.h"

// Struct for Fighter Stats
struct FighterStats {
    std::string name = "Unknown";
    int hp = 10;
    std::string weaponName = "Fists";
    int minDmg = 1;
    int maxDmg = 3;
};

class Fighter {
protected:
    // --- Constants ---
    static constexpr int FATIGUE_THRESHOLD_MULTIPLIER = 2; // Multiplied by opponent's max damage
    static constexpr int FATIGUE_RISK_DIVISOR = 3;         // Reduces risk percentage
    static constexpr int FATIGUE_MAX_RISK_PERCENT = 33;    // Maximum failure chance
    static constexpr int FATIGUE_MIN_RISK_PERCENT = 5;     // Minimum failure chance

    // --- Variables ---
    std::string name;
    int currentHealth;
    int maxHealth;
    Weapon weapon; // Fighter's weapon

public:
    // --- Constructor ---
    Fighter(std::string name, int health, Weapon weapon);

    // --- Destructor ---
    virtual ~Fighter();

    // --- Getters ---
    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;
    std::string getName() const;
    const Weapon& getWeapon() const;

    // --- Methods ---
    // Makes a fighter take damage
    void takeDamage(int damage);

    // virtual function that allows Player and Enemy to define their own takeTurn functions
    virtual void takeTurn(Fighter& target) = 0;

    // Checks if a fighter has triggered a fatigue failure against an opponent
    bool checkFatigueFailure(const Fighter& opponent) const;
};


#endif //M2OEP_GLATTANZ_FIGHTER_H