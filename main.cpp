/* *
 * Main build. Creates Player and Enemy objects by pulling stats from two config files. Runs the game loop,
 * using client input to simulate a fight between the client (Player) and a Enemy. The victor is logged to
 * an output file.
 *
 * Note - For your "player_config.txt" and "enemy_config.txt" files, the naming convention for variables should be as follows:
 *
 * =-------------------------------=
 * fighter_name=
 * hp=
 *
 * weapon_name=
 * min_damage
 * max_damage
 * =-------------------------------=
 *
 * Names for fighters/weapons do not need to be encased in quotes and can include spaces, such as:
 *
 * =-------------------------------=
 * fighter_name=Kevin the Ogre
 * hp=10
 *
 * weapon_name=A Big Rock
 * min_damage=4
 * max_damage=6
 * =-------------------------------=
 */

#include <iostream>
#include <fstream>
#include <ctime> // for random seed gen
#include "Player.h"
#include "Enemy.h"

// --- Constants ---
namespace GameConstants {
    const int HEALTH_BAR_LENGTH = 20;
    const std::string BATTLE_LOG_FILE = "battle_log.txt";
    const std::string ENEMY_CONFIG_FILE = "enemy_config.txt";
    const std::string PLAYER_CONFIG_FILE = "player_config.txt";

    // Default stats if config files are missing/corrupt
    const FighterStats DEFAULT_ENEMY = {"Kevin the Ogre", 40, "A Really Big Rock", 3, 7};
    const FighterStats DEFAULT_PLAYER = {"Hero", 40, "Bronze Sword", 3, 7};
}


// Helper function to save results
void logBattleResult(std::string winner) {
    std::ofstream outFile(GameConstants::BATTLE_LOG_FILE, std::ios::app);
    if (outFile.is_open()) {
        outFile << "Battle ended. Winner: " << winner << "\n";
        outFile.close();
    } else {
        std::cout << "[Warning] Could not write to battle log file." << std::endl;
    }
}

// Helper function to read stats from a file
bool loadConfig(std::string fileName, FighterStats& stats) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        return false;
    }

    std::string line;

    // Keep reading lines until the end of the file is reached
    while (std::getline(inFile, line)) {
        // Find the delimiter (equal sign)
        size_t pos = line.find('=');

        if (pos == std::string::npos) {
            continue; // Skip any lines without an equal sign
        }

        // Split the string into Key (before split point) and Value (after split point)
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // Store directly into the struct
        if (key == "fighter_name") {
            stats.name = value;
        }
        else if (key == "hp") {
            stats.hp = std::stoi(value);
        } else if (key == "weapon_name") {
            stats.weaponName = value;
        } else if (key == "min_damage") {
            stats.minDmg = std::stoi(value);
        } else if (key == "max_damage") {
            stats.maxDmg = std::stoi(value);
        }
    }

    std::cout << "[System] Loaded config for: " << stats.name << std::endl;
    inFile.close();
    return true;
}

// Helper to draw a visual health bar
// Example: [##########          ] (50/100)
void drawHealthBar(std::string name, int current, int max) {
    std::cout << name << ": ";

    // Calculate ratio
    if (current < 0) {
        current = 0;
    }

    double ratio = (double)current / (double)max;
    int filledBars = (int)(ratio * GameConstants::HEALTH_BAR_LENGTH);

    // Draws health bar
    std::cout << "[";
    for (int i = 0; i < GameConstants::HEALTH_BAR_LENGTH; i++) {
        if (i < filledBars) {
            std::cout << "#";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << current << "/" << max << std::endl;
}

int main() {
    std::srand(std::time(0));
    std::cout << "Welcome to the Arena!" << std::endl;

    // --- Enemy Setup ---
    FighterStats enemyStats = GameConstants::DEFAULT_ENEMY;

    if (!loadConfig(GameConstants::ENEMY_CONFIG_FILE, enemyStats)) {
        std::cout << "[System] Using default enemy." << std::endl;
    }

    // Create Enemy
    Enemy enemy(enemyStats.name, enemyStats.hp,
        Weapon(enemyStats.weaponName, enemyStats.minDmg, enemyStats.maxDmg));  // Enemy weapon


    // --- Player Setup ---
    FighterStats playerStats = GameConstants::DEFAULT_PLAYER;

    if (!loadConfig(GameConstants::PLAYER_CONFIG_FILE, playerStats)) {
        std::cout << "[System] Using default player." << std::endl;
    }

    // Create Player
    Player hero(playerStats.name, playerStats.hp,
        Weapon(playerStats.weaponName, playerStats.minDmg, playerStats.maxDmg));  // Player weapon

    // --- Game Loop ---
    int turnCounter = 1;

    // Loops until a fighter is defeated
    while (hero.isAlive() && enemy.isAlive()) {

        // Header
        std::cout << "\n========================================" << std::endl;
        std::cout << "               TURN " << turnCounter << std::endl;
        std::cout << "========================================" << std::endl;

        // Draws current health bars, adds (You) prefix to player
        std::cout << "(You) ";
        drawHealthBar(hero.getName(), hero.getHealth(), hero.getMaxHealth());
        drawHealthBar(enemy.getName(), enemy.getHealth(), enemy.getMaxHealth());

        // Player Turn
        hero.takeTurn(enemy);

        // End game immediately if player/enemy dies on player's turn
        if (!enemy.isAlive() || !hero.isAlive()) {
            break;
        }

        // Enemy Turn
        enemy.takeTurn(hero);

        turnCounter++;
    }

    // --- End of Game & Logging ---
    std::cout << "\n--- BATTLE OVER ---" << std::endl;

    if (hero.isAlive()) {
        std::cout << "VICTORY! You defeated " << enemy.getName() << " in "
        << turnCounter << " turns!" << std::endl;
        logBattleResult("Player");
    } else {
        std::cout << "DEFEAT! You were slain by " << enemy.getName() << " in "
        << turnCounter << " turns..." << std::endl;
        logBattleResult("Enemy");
    }

    // --- Makes it so console doesn't immediately close ---
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.ignore(1000, '\n');
    std::cin.get();

    return 0;
}