/*
 * Enemy is a child class of Fighter, and is what the user will "fight" against.
 */

#ifndef M2OEP_PROJECT_ENEMY_H
#define M2OEP_PROJECT_ENEMY_H

#include "Fighter.h"

class Enemy : public Fighter {
public:
    // --- Constructor ---
    Enemy(std::string name, int hp, Weapon weapon)
        : Fighter(name, hp, weapon) {}

    // --- Methods ---
    // Override for takeTurn()
    void takeTurn(Fighter& target) override;
};


#endif //M2OEP_PROJECT_ENEMY_H