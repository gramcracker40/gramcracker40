/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            Program 3B Fight Verse
*  Title:            Captain Base 
*  Course:           OOP 2143
*  Semester:         Fall Semester // 2021
* 
*  Description:
*        This program runs a game that can be manipulated by the size of the
*        input file and various other things described within the classes.
*
*
* Usage:
*        Within main declare an instance of battlescene after loading in your
*        vectors accordingly with attackers and defenders and run the program
*        using the Battle() method within battlescene
* 
*  Files:            N/A
*****************************************************************************/


#include <iostream>
#include <vector>
#include <string>
#include <vector> 
#include <fstream>

#include "helpers.hpp"
#include "characters.hpp"
#include "dice.hpp"
#include "battleScene.hpp"

using namespace std;

//prototypes
vector<BaseFighter> defenderLoadIn(int sizeOfAtt); //loads in the defenders based off of size of attackers
vector<BaseFighter> attackerLoadIn();              //loads in attackers from an input file
void printVector(vector<BaseFighter> fighters);    //prints out a vector of type basefighters


int main() {
    srand(time(0));

    //loading in the attackers first 
    vector<BaseFighter> attackers = attackerLoadIn();
    //load in the defenders second so you can use the size of attackers to build your defense
    vector<BaseFighter> defenders = defenderLoadIn(attackers.size()); 

    //create the battlescence
    BattleScene mainBattle(attackers, defenders);

    //runs the battle with the two vectors
    mainBattle.Battle();

    return 0;
}






/**
* Function: vector<BaseFighter> attackerLoadIn()
* 
* Description:
*      -  loads in the attackers from the input file
* 
* Params:
*      - N/A
* 
* Usage: 
*      - used to load in the attackers in to a vector
*/
vector<BaseFighter> attackerLoadIn(){
  vector<BaseFighter> attackers;
  string attacker;

  cout << "In the function"; 

  ifstream inputF; inputF.open("input.txt");

  while(!inputF.eof()){
    inputF >> attacker;

    if(attacker == "warrior"){
      attackers.emplace_back(Warrior());
    }
    else if(attacker == "wizard"){
      attackers.emplace_back(Wizard()); 
    }
    else if(attacker == "archer"){
      attackers.emplace_back(Archer()); 
    }
    else if(attacker == "elf"){
      attackers.emplace_back(Elf()); 
    }
    else if(attacker == "dragonborn"){
      attackers.emplace_back(DragonBorn()); 
    }
  }

  inputF.close();
  return attackers;
}


/**
* Function: vector<BaseFighter> defenderLoadIn(int sizeOfAtt)
* 
* Description:
*      -  loads in the defenders based on the total size of the attackers 
* 
* Params:
*      - (int) sizeOfAtt - size of the attacker vector
* 
* Usage: 
*      - used to create a balanced defender vector to fight with
*/
vector<BaseFighter> defenderLoadIn(int sizeOfAtt){
  vector<BaseFighter> defenders;

  int numDefenders = sizeOfAtt / 20; //divides the total atackers by 20

  for(int i = 0; i < numDefenders; i++){  // this for loop chooses an equal as possible amount of each type
    if(i % 5 == 0){                       // to load into the defenders 
      defenders.emplace_back(Warrior(1));
    }
    else if(i % 5 == 1){
      defenders.emplace_back(Wizard(1)); 
    }
    else if(i % 5 == 2){
      defenders.emplace_back(Archer(1)); 
    }
    else if(i % 5 == 3){
      defenders.emplace_back(Elf(1));
    }
    else if(i % 5 == 4){
      defenders.emplace_back(DragonBorn(1)); 
    }

  }

  return defenders;

}

/**
* Function: void printVector(vector<BaseFighter> fighters)
* 
* Description:
*      -  prints out a vector of type basefighter 
* 
* Params:
*      - (vector<BaseFighter>) fighters -- the attacker vector to determine the appropriate size
* 
* Usage: 
*      - used to create a balanced defender vector to fight with
*/
void printVector(vector<BaseFighter> fighters){
  for(int i = 0; i < fighters.size(); i++){
    cout << "#" << i << endl << fighters.at(i);
  }
}


