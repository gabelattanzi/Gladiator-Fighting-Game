#include "Fighter.h"
#include <random>

// --- Constructor ---
Fighter::Fighter(std::string name, int hp, Weapon weapon)
    : name(name), currentHealth(hp), maxHealth(hp), weapon(weapon) {}

// --- Destructor ---
Fighter::~Fighter() {}

// --- Getters ---
int Fighter::getHealth() const {return currentHealth;}
int Fighter::getMaxHealth() const {return maxHealth;}
bool Fighter::isAlive() const {return currentHealth > 0;}
std::string Fighter::getName() const {return name;}
const Weapon& Fighter::getWeapon() const {return weapon;}

// --- Methods ---
void Fighter::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

// Returns true if a fighter is fatigued and gets parried/countered
bool Fighter::checkFatigueFailure(const Fighter& opponent) const {
    // Calculate HP threshold where fatigue kicks in
    // If your HP > (opponent's max damage * FATIGUE_THRESHOLD_MULTIPLIER), you're not fatigued
    int dangerZone = opponent.getWeapon().getMaxDamage() * FATIGUE_THRESHOLD_MULTIPLIER;

    if (currentHealth > dangerZone) {
        return false; // Not low enough to trigger
    }

    // Calculate failure probability based on remaining hp
    double healthRatio = (double)currentHealth / (double)maxHealth;

    // Formula: Lower health = higher risk of failure
    // Divided by FATIGUE_RISK_DIVISOR to keep percentages reasonable
    int riskPercent = (100 - (int)(healthRatio * 100)) / FATIGUE_RISK_DIVISOR;

    // Caps
    if (riskPercent > FATIGUE_MAX_RISK_PERCENT) {
        riskPercent = FATIGUE_MAX_RISK_PERCENT;
    }

    if (riskPercent < FATIGUE_MIN_RISK_PERCENT) {
        riskPercent = FATIGUE_MIN_RISK_PERCENT;
    }

    // Notify that a fighter is fatigued
    std::cout << "\t* " << name << " is Fatigued!\n" << std::endl;

    // Roll for failure
    int roll = rand() % 100;

    // Return true if the roll is less than the risk percentage, a.k.a true if a riposte lands
    return (roll < riskPercent);
}