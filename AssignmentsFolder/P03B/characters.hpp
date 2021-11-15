#ifndef CHARACTERS
#define CHARACTERS

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <map> 
#include "weapon.hpp"
#include "helpers.hpp"


using namespace std;

#pragma once

map<string, vector<string>> mapOfWeapons = {
  {"sword", {"1.d.12", "2.d.6", "3.d.4"}},
  {"magic", {"1.d.20", "2.d.10", "3.d.6", "5.d.4"}},
  {"bow", {"1.d.8", "2.d.4", "1.d.10"}},
  {"magicSword", {"4.d.6","2.d.12"}},
  {"magicFire", {"4.d.8","3.d.8", "5.d.6"}}
};

string pickWeapon(string weapon){
  static int progresser = 0;
  
  int r = rand() % mapOfWeapons[weapon].size();

  return mapOfWeapons[weapon][r];
  progresser++; 
}



/**
 * BaseFighter
 * 
 * Description:
 *      this is the parent class of a number of different types of Fighters
 *      it allows us to use a base pointer that can point at any of the Fighters
 *      and use the methods of basefighter to manipulate their values
 * 
 * Public Methods:
 *      - virtual double attack() -returns a value for the damage done
 *      - virtual int getHealth() -returns the current health of the object
 *      - virtual void setHealth(int dmg) - you can set the health 
 *      - virtual string getName() - returns the name
 *      - virtual string getRace() - returns the race
 *      - virtual string getWeapon() - returns the weapon
 *
 * Overloaded Operators:
 *      - friend ostream& operator<<(ostream& cout, const BaseFighter &rhs)
 *      - BaseFighter operator=(BaseFighter &rhs)
 *
 * Constructors:
 *      -BaseFighter()
 * 
 * Usage: 
 * 
 *      - You can use it to point at multiple other classes inheriting from it
 *        and use the virtual functions to manipulate that object accordingly 
 */
class BaseFighter {
    
protected:
    Weapon *weapon;     //the weapon pointer that switches between different objects
    string name;        //nickname of the object
    double health;         //the current Health
    string race;        //the race of the object
    string weaponN;     //the nickname of the weapon
    string weaponName;  //the map key for the weapon used
    double healthReg;   //total life regen each character has
    double maxHealth;

public:
    /**
    * Constructor : BaseFighter(){
    * 
    * Description:
    *      - initializes key values of the class 
    */
    BaseFighter() {
        name = "None";
        weapon = new Weapon;
    }

    // virtual ~BaseFighter() {
    //   delete *weapon;
    // }

     /**
     * Method : virtual double attack()
     * 
     * Description:
     *      -  returns a value based on the weapons damage
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - using it to decide the damage done to the other player
     */
    virtual int attack(){
        return weapon->use();
    }
    
     /**
     * friend ostream& operator<<(ostream& cout, const BaseFighter &rhs)
     * 
     * Description:
     *      -  over loading the = brackets allows us to copy over entire 
     *         vectors and even the compilation of different vectors into one
     * 
     * Params:
     *      - [BaseFighter] rhs - the fighter we are printing out
     *                
     * 
     * Usage: 
     *      - use it to print out the data of a BaseFighter type object
     */
    friend ostream& operator<<(ostream& cout, const BaseFighter &rhs){
      cout << "Name: " << rhs.name << endl
           << "Race: " << rhs.race << endl
           << "Weapon: " << rhs.weaponN << endl
           << "Health: " << rhs.health << endl
           << "Damage: " << rhs.weapon->use() << endl 
           << "Health Regeneration: " << rhs.healthReg << endl << endl;
      
      return cout;
    }

    /**
     * BaseFighter operator=(const BaseFighter &rhs)
     * 
     * Description:
     *      -  overloaded the = sign to allow copying between different instances
     * 
     * Params:
     *      - const [BaseFighter] rhs - the fighter we are copying
     *                
     * 
     * Usage: 
     *      - use it for copying over the contents from one basefighter to another
     */
    BaseFighter operator=(const BaseFighter &rhs){
    
      this->health = rhs.health;
      this->race = rhs.race;
      this->weaponN = rhs.weaponN;
      this->name = rhs.name;
      this->weapon = new Weapon(pickWeapon(rhs.weaponName), rhs.weaponN);
      this->weaponName = rhs.weaponName;
      this->healthReg = rhs.healthReg;
      this->maxHealth = rhs.maxHealth;
      return *this;
    }


    //GETTERS/SETTERS FOR ALL CHILDREN CLASSES -- VIRTUAL
    virtual double getHealth(){
      return health;
    }

    virtual void setHealth(int dmg){
      health = health - dmg;
    }

    virtual void addHealth(int heal){
      health = health + heal;
    }

    virtual double getRegen(){
      return healthReg;
    }

    virtual string getName(){
      return name;
    }

    virtual string getRace(){
      return race;
    }

    virtual string getWeapon(){
      return weaponName;
    }

    virtual double getMaxHealth(){
      return maxHealth; 
    }

    friend class BattleScene;
};



/**
 * Warrior
 * 
 * Description:
 *      - Creates either a warrior attacker or defender based on which constructor 
 *          you implement
 *
 * Constructors:
 *      - Warrior() - creates the attacker warrior
 *      - Warrior(int defender) - creates the defender warrior
 * 
 * Usage: 
 * 
 *      - create a fighter with the stats of a warrior 
 */
class Warrior: public BaseFighter{

public:
  //creates the attacker warrior class.
  Warrior(){
    weapon = new Weapon(pickWeapon("sword"), weaponN);
    name = "Warrior";
    race = "Nordic Viking";
    weaponN = "Battle Axe";
    health = randomRange(25,32);
    weaponName = "sword";
    healthReg = 1;
    maxHealth = 32;
  }
  //creates the defender warrior class
  Warrior(int defender){
    weapon = new Weapon(pickWeapon("sword"), weaponN);
    name = "Warrior King"; 
    race = "Nordic Viking Berserker";
    weaponN = "Axe of Destruction";
    health = 850;
    weaponName = "sword";
    healthReg = 0.5;
    maxHealth = 850;
  }


};


/**
 * Wizard
 * 
 * Description:
 *      - Creates either a wizard attacker or defender based on which constructor 
 *          you implement
 *
 * Constructors:
 *      - Wizard() - creates the attacker wizard
 *      - Wizard(int defender) - creates the defender wizard
 * 
 * Usage: 
 * 
 *      - create a fighter with the stats of a wizard 
 */
class Wizard: public BaseFighter{

public:
  //creates the attacker wizard class.
  Wizard(){
    weapon = new Weapon(pickWeapon("magic"), weaponN);
    name = "Wizard";
    race = "Elvin";
    weaponN = "Staff";
    health = randomRange(19,25);
    weaponName = "magic";
    healthReg = 1;
    maxHealth = 25;
  }

  //creates the defender wizard class
  Wizard(int defender){
    weapon = new Weapon(pickWeapon("magic"), weaponN);
    name = "Wizard of High";
    race = "High Elvin";
    weaponN = "Ancient Staff of Magic";
    health = 600;
    weaponName = "magic";
    healthReg = 0.85;
    maxHealth = 600;
  }

  

};


/**
 * Archer
 * 
 * Description:
 *      - Creates either a Archer attacker or defender based on which constructor 
 *          you implement
 *
 * Constructors:
 *      - Archer() - creates the attacker archer
 *      - Archer(int defender) - creates the defender archer
 * 
 * Usage: 
 * 
 *      - create a fighter with the stats of a archer
 */
class Archer: public BaseFighter{

public:
  //creates the attacker archer class.
  Archer(){
    weapon = new Weapon(pickWeapon("bow"), weaponN);
    name = "Archer";
    race = "Wood Elf";
    weaponN = "Bow of Truth";
    health = randomRange(14,18);
    weaponName = "bow";
    healthReg = 1;
    maxHealth = 18; 
  }

  //creates the defender archer class
  Archer(int defender){
    weapon = new Weapon(pickWeapon("bow"), weaponN);
    name = "Hawkeye";
    race = "Murican";
    weaponN = "Lazer Bow";
    health = 750;
    weaponName = "bow";
    healthReg = 1.5;
    maxHealth = 750; 
  }


};


/**
 * Elf
 * 
 * Description:
 *      - Creates either a Elf attacker or defender based on which constructor 
 *          you implement
 *
 * Constructors:
 *      - Elf() - creates the attacker elf
 *      - Elf(int defender) - creates the defender elf
 * 
 * Usage: 
 * 
 *      - create a fighter with the stats of a Elf
 */
class Elf: public BaseFighter{
protected:
 

public:
  //creates the attacker Elf class.
  Elf(){
    weapon = new Weapon(pickWeapon("magicSword"), weaponN);
    name = "Elf";
    race = "Dark Elvin";
    weaponN = "Fire Sword";
    health = randomRange(35,49);
    weaponName = "magicSword";
    healthReg = 1;
    maxHealth = 49; 
  }

  //creates the defender elf class
  Elf(int defender){
    weapon = new Weapon(pickWeapon("magicSword"), weaponN);
    name = "Elf Commander";
    race = "Royal Dark Elvin";
    weaponN = "Divine Sword of Fire"; 
    health = 1000;
    weaponName = "magicSword";
    healthReg = 0.75;
    maxHealth = 1000;
  }

};


/**
 * DragonBorn
 * 
 * Description:
 *      - Creates either a dragonborn attacker or defender based on which constructor 
 *          you implement
 *
 * Constructors:
 *      - DragonBorn() - creates the attacker dragonborn
 *      - DragonBorn(int defender) - creates the defender dragonborn
 * 
 * Usage: 
 * 
 *      - create a fighter with the stats of a dragonborn
 */
class DragonBorn: public BaseFighter{

public:
  //creates the attacker DragonBorn class.
  DragonBorn(){
    weapon = new Weapon(pickWeapon("magicFire"), weaponN);
    name = "Dragon Born Disciple";
    race = "Demon/Human";
    weaponN = "Fire Magic";
    health = randomRange(45,55);
    weaponName = "magicFire";
    healthReg = 1;
    maxHealth = 55; 
  }

  //creates the defender DragonBorn class
  DragonBorn(int defender){
    weapon = new Weapon(pickWeapon("magicFire"), weaponN);
    name = "Dragon Born God";
    race = "Dragon Born";
    weaponN = "Hand Of Destruction"; 
    health = 1000;
    weaponName = "magicFire";
    healthReg = 0.5;
    maxHealth = 1000; 
  }
  

};

#endif
