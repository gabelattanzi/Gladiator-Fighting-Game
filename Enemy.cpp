//
// Created by gabe lattanzi on 2/4/26.
//

#include "Enemy.h"
#include <iostream>

void Enemy::takeTurn(Fighter& target) {
    std::cout << "\n" << name << "'s Turn!\n" << std::endl;

    // --- Fatigue Check ---
    if (checkFatigueFailure(target)) {
        std::cout << name << " attacks, and..." << std::endl;
        std::cout << ">>> Riposte! <<<" << std::endl;
        std::cout << "You deflect the attack and strike " << name << " down!" << std::endl;

        // Kill Enemy
        currentHealth = 0;
        return;
    }

    // --- Normal Attack ---
    int damage = weapon.rollDamage();

    std::cout << "  >> " << name << " attacks you with " << weapon.getName()
              << " for " << damage << " damage!" << std::endl;

    target.takeDamage(damage);
}