#ifndef WEAPON
#define WEAPON


#include <iostream>
#include <string>
#include <vector>

#include "dice.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

class Weapon {
    string name;    // name of weapon
    string damage;  // damage per roll or "use"
    Dice*  die;

public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    Weapon() {
        name = "Fists&Feet";
        damage = "1.d.4";
        die = new Dice(damage);
    }
    /**
     * 
     */
    Weapon(string damageStr, string nameOfWeapon) {
        name = nameOfWeapon;
        damage = damageStr;
        die = new Dice(damage);
    }

    double use() {
        return die->roll();
    }

    friend ostream& operator<<(ostream& os, const Weapon& w) {
        return os << "[" << w.name << " , " << w.damage << "]";
    }
};

#endif
