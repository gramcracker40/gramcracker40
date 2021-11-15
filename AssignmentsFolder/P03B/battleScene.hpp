#ifndef BATTLESCENE
#define BATTLESCENE


#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <iterator>
#include <map>
//#include <algorithm> 
#include "weapon.hpp"
#include "helpers.hpp"
#include "characters.hpp"
#include "dice.hpp"
#include <cstdlib>
#include <stdlib.h>

using namespace std;

#pragma once

/**
 * BattleScene
 * 
 * Description:
 *      this class runs the game by combining elements from all of the other classes
 *      and different logical statements included within the code of Battle()
 * 
 * Public Methods:
 *      - void Battle() - runs the entirety of the game, uses most of the other public methods within 
 *      - void lifeRegen() - gives the defenders life regen every iteration
 *      - void lifeSteal() - gives the defender a chance at stealing some health
 *      - void healthSwap() - swaps the defender when the health gets low
 *      - void defenseSort() - sorts the defense by their type, good for health swap
 *      - void printScore() - shows the score the whole battle
 *      - void printSpecificOff(int position) - used for testing specific positions
 *      - void printSpecificDef(int position) - used for testing specific positions
 *      - void printAll() - prints all elements of the object
 *      - void printOffense() - prints the offense
 *      - void printDefense() - prints the defense
 *
 * Overloaded Operators:
 *      - N/A
 *
 * Constructors:
 *      -BattleScene(vector<BaseFighter> attackers, vector<BaseFighter> defenders)
 *            ---loads in two vectors of basefighters and sets other variables accordingly
 * 
 * Usage: 
 * 
 *      - initiate the battle by using Battle() within main of your program. 
 */
class BattleScene{
  private:
    int totalFighters;                        //tracks current total fighters
    int numDefenders;                         //tracks current total defenders
    int numAttackers;                         //tracks current total attackers
    vector<BaseFighter> defense;              //vector of defenders
    vector<BaseFighter> offense;              //vector of attackers
    BaseFighter *CaptainBase;                 //the pointer to control which defender is battling.
    int iter = 0;
    //vector<BaseFighter>::iterator it; 
    //Dice *lifeStlChance = new Dice("1.d.10"); //random life steal generator
    

  public:
    /**
    * Constructor : BaseFighter(){
    * 
    * Description:
    *      - initializes all key values of the class determined by the vectors of basefighters 
    *
    * Params: 
    *      - vector<BaseFighter> attackers - a vector full of attackers
    *      - vector<BaseFighter> defenders - a vector full of defenders
    *
    * Usage:
    *      - to create a battlefield of attackers and defenders
    */
    
    BattleScene(vector<BaseFighter> attackers, vector<BaseFighter> defenders){
      cout << endl << "In here" << endl;

      //pulls in all of the offense
      for(int i = 0; i < attackers.size(); i++){
        offense.push_back(attackers[i]);
      }

      //pulls in all of the defense
      for(int e = 0; e < defenders.size(); e++){
        defense.push_back(defenders[e]);
      }
      
      totalFighters = offense.size() + defense.size();
      numDefenders = defense.size();
      numAttackers = offense.size(); 
    }

    
     /**
     * Method : void Battle()
     * 
     * Description:
     *      -  runs the entire battle start to finish
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - use it to run the battle 
     */
    void Battle(){
      double dmgHold;   //holds the damage value of an attack temporarily
      
      CaptainBase = &defense.at(0);
      
      while(defense.size() != 0 || offense.size() != 0){
        iter = 0;
        
        //choosing the defender - while their weapon code is not the same run this 
        while(CaptainBase->getWeapon() != offense.at(0).getWeapon() && iter != defense.size() -1){
          
          CaptainBase = &defense.at(iter);
          if(CaptainBase->getWeapon() == offense.at(0).getWeapon()){
            break;
          }else{
            iter++;
          }
        }
        if(iter == defense.size()){
          CaptainBase = &defense.at(iter - 1);
        }
        if(defense.size() == 0 || offense.size() == 0){
          break;
        }

        //Health check to determine if the object picked still has a health above 0
        if(CaptainBase->getHealth() <= 0){
          defense.erase(defense.begin() + iter);
          numDefenders--;
          totalFighters--;
          if(defense.size() == 0 || offense.size() == 0){
            break;
          }else{
            continue;
          }
        }
        
        lifeRegen(); //applying life regen before any attacks

        healthSwap(); //swapping the object out if their health is too low to keep fighting
        defenseSort();

        //performing an attack from the attacker to the defender
        dmgHold = offense.at(0).attack();
        CaptainBase->setHealth(dmgHold);
        
        //when captain bases health is at or below zero it will erase the element
        //captain base is on from defense and then go to the beginning to pick another
        //defender for captain base to fight with
        if(CaptainBase->getHealth() <= 0){
        
          defense.erase(defense.begin() + iter);
          numDefenders--;
          totalFighters--;
          if(defense.size() == 0 || offense.size() == 0){
            break;
          }else{
            continue;
          }
          
        }

        printScore(); // printing the score out after the fighter is removed

        //performing an attack on the attacker from the defender
        dmgHold = CaptainBase->attack();
        lifeSteal(); 
        offense.at(0).setHealth(dmgHold); 
        // end of attack
        
        //check to see if the attack caused death or not
        if(offense.at(0).getHealth() <= 0){ // if health is below zero
          
          offense.erase(offense.begin());   // erase the character from the vector
          numAttackers--;                   //increment the total variables
          totalFighters--;
          if(defense.size() == 0 || offense.size() == 0){ //checking if the vectors are empty
            break;
          }else{
            continue;
          }        
        }
        printScore();
      }

      //end results to be printed after loop is finished
      if(defense.size() == 0){
        cout << "Attackers WIN\n#Attackers Remaining:: " << offense.size();
      }else{
        cout <<"Defenders WIN\n#Defenders Remaining:: " << defense.size() ;
      }
    }
    

     /**
     * Method : void lifeRegen()
     * 
     * Description:
     *      -  applies life regen each iteration of the battle method
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - used within Battle() to apply life regen periodically
     */
    void lifeRegen(){
      for(int i = 0; i < defense.size(); i++){
        if(defense.at(i).getHealth() + defense.at(i).getRegen() < defense.at(i).getMaxHealth()){
          defense.at(i).addHealth(defense.at(i).getRegen());
        }
      }
      offense.at(0).addHealth(offense.at(0).getRegen());
    }

    /**
     * Method : void lifeSteal()
     * 
     * Description:
     *      -  gives the defender a 40% chance of taking 30% of the attackers current
     *          health and adding it to their own life. 
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - used whenever the defender attacks the attacker
     */
    void lifeSteal(){
      int chance = randomRange(1,10); 
      if(chance == 2 || chance == 7 || chance == 5 || chance == 3){
        CaptainBase->addHealth(CaptainBase->getRegen());
      }

    }
    
     /**
     * Method : void healthSwap()
     * 
     * Description:
     *      -  swaps out CaptainBase with another defender if its health is too low to fight 
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - used whenever CaptainBase gets too low to keep fighting
     */
    void healthSwap(){
      if(CaptainBase->getHealth() <= CaptainBase->getMaxHealth() / 10 && CaptainBase->getHealth() >= 1){
        CaptainBase = &defense.at(0);
      }
    }

     /**
     * Method : void defenseSort()
     * 
     * Description:
     *      -  sorts the defenders by type
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - used to sort the defense before the fight begins so they can stay in relative good order
     *          for the health swap
     */
    void defenseSort(){
      BaseFighter tmp; //holding object for switching objects

      for(int i =1; i< defense.size(); i++){
        for(int j = i; j > 0; j--){
          if(defense.at(j).weaponN.length() < defense.at(j-1).weaponN.length()){
            tmp = defense.at(j);
            defense.at(j) = defense.at(j-1);
            defense.at(j-1) = tmp;
          }
        }
      }
    }


     /**
     * Method : void printScore()
     * 
     * Description:
     *      -  prints the score each iteration
     * 
     * Params:
     *      - N/A
     * 
     * Usage: 
     *      - used to display the score after a defender or attacker is killed
     */
    void printScore(){
      cout << "\nINVADER: HERO COUNT\n";
      cout << "\n#Defenders:: " << defense.size() << endl 
             << "#Attackers:: " << offense.size() << endl;
      system("clear");
    }



     /**
     * Method : void printSpecificOff(int position)
     * 
     * Description:
     *      -  tests the contents of offense at a certain position
     * 
     * Params:
     *      - (int) position -- the desired position of the vector to print out
     * 
     * Usage: 
     *      - used for testing
     */
    void printSpecificOff(int position){
      cout << offense.at(position);
    }


     /**
     * Method : void printSpecificDef(int position)
     * 
     * Description:
     *      -  tests the contents of defense at a certain position
     * 
     * Params:
     *      - (int) position -- the desired position of the vector to print out
     * 
     * Usage: 
     *      - used for testing
     */
    void printSpecificDef(int position){
      cout << defense.at(position);
    }

     /**
     * Method : void printCapBase()
     * 
     * Description:
     *      -  prints out the current CaptainBase
     * 
     * Params:
     *      - n/a
     * 
     * Usage: 
     *      - used for testing
     */
    void printCapBase(){
      cout << *CaptainBase;
    }

     /**
     * Method : void printDefense()
     * 
     * Description:
     *      -  tests the whole defense by printing the whole thing
     * 
     * Params:
     *      - n/a
     * 
     * Usage: 
     *      - used for testing
     */
    void printDefense(){
      cout << "--DEFENSE--" << endl;
      for(int i = 0; i < defense.size(); i++){
        cout << "#" << i+1 << endl << defense.at(i);
      }
    }
    
    
     /**
     * Method : void printOffense()
     * 
     * Description:
     *      -  tests the whole offense by printing the whole thing
     * 
     * Params:
     *      - n/a
     * 
     * Usage: 
     *      - used for testing
     */
    void printOffense(){
      cout << "--OFFENSE--" << endl;
      for(int i = 0; i < 5; i++){
        cout << "#" << i+1 << endl << offense.at(i);
      }
    }

     /**
     * Method : void printAll()
     * 
     * Description:
     *      -  prints the offense and deffense along with total objects
     * 
     * Params:
     *      - n/a
     * 
     * Usage: 
     *      - used for testing
     */
    void printAll(){
      cout << "Total Fighters: " << totalFighters << endl
           << "Number of Defenders: " << numDefenders << endl
           << "Number of Attackers: " << numAttackers << endl;


      for(int i = 0; i < offense.size(); i++){
        cout << "#" << i+1 << endl << offense.at(i);
      }
      for(int i = 0; i < defense.size(); i++){
        cout << "#" << i+1 << endl << defense.at(i);
      }
    }

    

};


#endif
