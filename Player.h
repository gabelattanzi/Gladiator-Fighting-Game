/*
 * Player is a child class of Fighter, it is what the user will be associated with.
 * It handles user input, the player's attack, and healing.
 */

#ifndef M2OEP_PROJECT_PLAYER_H
#define M2OEP_PROJECT_PLAYER_H

#include "Fighter.h"

class Player : public Fighter {
private:
    // --- Constants ---
    static constexpr int STARTING_FLASKS = 3;   // Number of healing flasks at start of game
    static constexpr int HEALING_PERCENT = 20;  // Percentage of max HP restored per flask

    // --- Variables ---
    int numFlasks;

public:
    // --- Constructor ---
    Player(std::string name, int hp, Weapon weapon)
        : Fighter(name, hp, weapon), numFlasks(STARTING_FLASKS) {}

    // --- Methods ---
    // Override for takeTurn()
    void takeTurn(Fighter& target) override;

    // Returns number of healing flasks remaining
    int getNumFlasks() const;
};

#endif //M2OEP_PROJECT_PLAYER_H