#include "Player.h"
#include <iostream>
#include <string>

int Player::getNumFlasks() const {
    return numFlasks;
}

void Player::takeTurn(Fighter& target) {
    // Variables for input
    std::string rawInput;
    int choice = 0;
    bool validChoice = false;

    // Prompt for user input with validation
    while (!validChoice) {
        std::cout << "\nIt's your turn! Choose an action: " << std::endl;
        std::cout << "1. Attack with " << weapon.getName() << std::endl;
        std::cout << "2. Healing Potion (" << numFlasks << ")" << std::endl;
        std::cout << "> ";

        std::cin >> rawInput;

        // Input validation
        if (rawInput != "1" && rawInput != "2") {
            std::cout << "Invalid choice. Please type \"1\" or \"2\"." << std::endl;
        } else if (rawInput == "1") {
            choice = 1;             // Attack
            validChoice = true;
        } else {
            if (numFlasks > 0) {
                choice = 2;         // Heal
                validChoice = true;
            } else {
                    std::cout << "You are out of healing flasks! You must attack again!" << std::endl;
            }
        }
    }

    // Clear input buffer
    std::cin.ignore(1000, '\n');

    // --- Actions ---

    if (choice == 1) {
        // --- Attack ---

        // Fatigue Check
        if (checkFatigueFailure(target)) {
            std::cout << "You stumble while attacking..." << std::endl;
            std::cout << ">>> Riposte! <<<" << std::endl;
            std::cout << target.getName() << " deflects your attack and annihilates you!" << std::endl;

            currentHealth = 0;
            return;
        }

        // Normal Attack
        int damage = weapon.rollDamage();

        std::cout << "\n  >> " << "You hit " << target.getName() << " with " <<  weapon.getName()
                  << " for " << damage << " damage!" << std::endl;

        target.takeDamage(damage);

    } else {
        // --- Heal ---

        // Calculate Heal Amount
        int healAmount = (maxHealth * HEALING_PERCENT) / 100;

        // Store old hp to calculate actual healing done
        int oldHP = currentHealth;
        currentHealth += healAmount;

        // Decrement flask counter
        --numFlasks;

        // Cap at Max Health
        if (currentHealth > maxHealth) {
            currentHealth = maxHealth;
        }

        // Calculate actual amount healed (for the text log)
        int actualHealed = currentHealth - oldHP;

        std::cout << "\t* You drank a healing flask." << std::endl;
        std::cout << "\t* Recovered " << actualHealed << " HP. Health is now: "
                  << currentHealth << "/" << maxHealth << std::endl;
    }
}