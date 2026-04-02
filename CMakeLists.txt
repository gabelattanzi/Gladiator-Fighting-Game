cmake_minimum_required(VERSION 4.0)
project(M2OEP_Project)

set(CMAKE_CXX_STANDARD 17)

# --- Main ---.
add_executable(gladiator
        main.cpp
        Weapon.cpp
        Fighter.cpp
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h

)

# --- Testing ---
add_executable(gladiator_test
        testing.cpp
        Weapon.cpp
        Fighter.cpp
        Enemy.cpp
        Player.cpp
)