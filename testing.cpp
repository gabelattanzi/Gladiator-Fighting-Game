/*
 * Test build. A full testrun passes if there are no [FAIL] flags, and output reaches "--- End Test Report---"
 */

#include <iostream>
#include <string>
#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"

// Testing helper function to save eyes from a billion if/else statements
void runTest(bool condition, std::string testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << std::endl;
    } else {
        std::cout << "[FAIL] " << testName << " <--- CHECK THIS!" << std::endl;
    }
}

int main() {
    std::cout << "--- Test Report ---\n" << std::endl;

    // 1. Tests weapon
    std::cout << "- Testing weapon initialization and damage logic -" << std::endl;
    Weapon w("TestWeapon", 10, 10);
    // Check if damage is exactly 10
    runTest(w.rollDamage() == 10, "Weapon fixed damage logic");
    std::cout << std::endl;

    // 2. Tests Enemy setup
    std::cout << "- Testing Enemy setup -" << std::endl;
    Weapon weak("Weak", 1, 1);
    Enemy m("TestEnemy", 50, weak);

    runTest(m.getHealth() == 50, "Enemy HP initialization");
    runTest(m.getName() == "TestEnemy", "Enemy Name initialization");
    runTest(m.isAlive() == true, "Enemy starts alive");
    std::cout << std::endl;

    // 3. Tests damage
    std::cout << "- Testing damage infliction -" << std::endl;
    m.takeDamage(20);
    runTest(m.getHealth() == 30, "Damage calculation (50 - 20 = 30)");
    std::cout << std::endl;

    // 4. Tests death
    std::cout << "- Testing character death upon fatal damage infliction -" << std::endl;
    m.takeDamage(100);
    runTest(m.getHealth() == 0, "HP stops to 0 (no negatives)");
    runTest(m.isAlive() == false, "Dead status check");
    std::cout << std::endl;

    // 5. Tests attack logic
    std::cout << "- Testing attack logic -" << std::endl;
    Enemy attacker("Attacker", 100, w);
    Enemy target("Target", 100, w);

    attacker.takeTurn(target);
    runTest(target.getHealth() == 90, "Enemy vs Enemy damage logic");
    std::cout << std::endl;

    // 6. Fatigue Testing
    // Healthy fighters should not trigger fatigue checks.
    std::cout << "- Testing fatigue check -" << std::endl;
    bool isFatigued = attacker.checkFatigueFailure(target);
    runTest(isFatigued == false, "High HP correctly avoids fatigue check");
    std::cout << std::endl;

    std::cout << "--- End Test Report ---" << std::endl;

    return 0;
}


