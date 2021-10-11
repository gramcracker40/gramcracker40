/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            Rock, Paper, Scissors, Lizard, Spock
*  Title:            Basic Project Organization
*  Course:           OOP 2143
*  Semester:         Fall Semester // 2021
* 
*  Description:
*        This program employs rock paper scissors with a twist, a ton more
*        possibilities are achievable throwing in a lizard and a spock
*
*
* Usage:
*        Play it and have fun, also uses Multiple OOP topics...
* 
*  Files:            N/A
*****************************************************************************/

#include <iostream>
#include <random> 
#include <string> 
#include <map>
#include <functional>
#include "emoji.h" 

using namespace std;

//defining emojis to be used within the code
#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"



class DieRoll {
    int sides;

    int Random(int max) {
        return 1 + (rand() % max);
    }

    // min = 40 max = 100
    int Random(int min, int max) {
        return 1 + min + (rand() % (max - min));
    }
    void init(int _seed, int _sides) {
        sides = _sides;
        srand(_seed);
    }
public:
    DieRoll() {
        //cout << "default base" << endl;
        init(time(0), 6);
    }
    DieRoll(int _seed) {
        //cout << "overloaded const" << endl;
        init(_seed, 6);
    }
    DieRoll(int _seed, int _sides) {
        //cout << "overloaded const" << endl;
        init(_seed, _sides);
    }

    void setDie(int _sides) {
        sides = _sides;
    }

    int Roll(int sides, int times) {
        int sum = 0;
        while (times--) {
            sum += Random(sides);
        }
        return sum;
    }

};

struct Hands {
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;

    static map< string, string > Emojis;  // stl map
    //         name  , emoji

    static map< string, string > Names;  // stl map
    //         emoji  , name

    static string RandHand() {
        auto it = Emojis.begin();  // iterator to front of map

        std::advance(it, rand() % Emojis.size());  // advance some random amnt
                                                   //   of steps

        string random_hand = it->second;  // grab emoji from map

        return random_hand;  // return rand emoji
    }

    static string Rock() {
        return Emojis["rock"];
    }
    static string Paper() {
        return Emojis["paper"];
    }
    static string Scissors() {
        return Emojis["scissors"];
    }
    static string Lizard() {
        return Emojis["lizard"];
    }
    static string Spock() {
        return Emojis["spock"];
    }
};
// maps to use within 'Hands' to be able to easily access
// the emojis
map< string, string > Hands::Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}};
// initialize static data member for
// hands struct (class)
map< string, string > Hands::Names = {
    {ROCK2, "rock"},
    {PAPER2, "paper"},
    {SCISSORS2, "scissors"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"}};

/**
 * Rock Paper Scissors Lizard Spock
 * 
 * @description: A class to run the rock papers scissors game
 * 
 */
class RPSLS : public DieRoll, public Hands {
public:
    RPSLS(): DieRoll(time(0)){            
        string h = RandHand();
        cout<<Names[h]<<": " <<h<<endl;
    };
    RPSLS(int seed) : DieRoll(seed) {
        cout << "Rock: " << Rock() << endl;
    }
};


/**
 * Class: Player()
 * 
 * Description:
 *      - Creates the object type 'player' allowing us to make instances of player
 *        quickly and easily, The Player class determines if a player wins or loses
 *        and can be manipulated with many methods listed below.
 * 
 * Public Methods:
 *      - Player()
 *      - void setWeapon(int val)
 *      - void printAllWeapons
 *      - string weaponCheck(int position)
 *      - void weaponReset()
 *
 * Overloaded Operators:
 *      - friend ostream& operator<<(ostream& cout, const Player &P1)
 *      - bool operator>(Player& other)
 *      
 * Usage: 
 * 
 *      - 
 */
class Player {
  private:
    string weapons[2]; // giving the player two weapons in an array for easy testing    
    int weapon;        // used to change the weapon that is outputted to ostream
  public:
    
    /**
     * Constructor : Player()
     * 
     * Description:
     *      - Base constructor used to declare objects of the type 'Player'
     * 
     * Usage: 
     *      - Use it to make players with random 'weapons'
     */
    Player() {
      //Giving random weapons to the player
        
      for(int e = 0; e < 2; e++) {
        weapons[e] = Hands::RandHand();
      }
 
       // if weapon 1 and 2 are same change 2 until it's different
      while((weapons[0]) == (weapons[1])){
        weapons[1] = Hands::RandHand(); 
      }
      weapon = 0;
    }
    
    /**
     * Method : void setWeapon
     * 
     * Description:
     *      -  sets the weapon that is outputted by ostream
     *
     * Usage: 
     *      - used to set the outputted weapon based on specific conditions in main
     */
    void setWeapon(int val){
      weapon = val;
    }

    
    /**
     * Method : void printAllWeapons()
     * 
     * Description:
     *      -  prints the weapons that the player obtained
     *
     * Usage: 
     *      - used to display the weapons to the user in an orderly fashion
     */
    void printAllWeapons(){
      cout << "Weapon One: " << weapons[0]
          << " Weapon Two: " << weapons[1] << endl;
    }

     /**
     * Method : string weaponCheck(int i)
     * 
     * Description:
     *      -  returns the weapon in the int position
     * 
     * Usage: 
     *      - used to check the weapon in the positions passed through 
     *        allows us to check for ties more freely
     */
    string weaponCheck(int position){
      return weapons[position];
    }

  
     /**
     * Method : void weaponReset()
     * 
     * Description:
     *      -  resets all weapons of the player
     *
     * Usage: 
     *      - used to reset weapons after each game played
     */
    void weaponReset(){
      
      for(int e = 0; e < 2; e++) {
        weapons[e] = Hands::RandHand();
      }
 
       // if weapon 1 and 2 are same change 2 until it's different
      while((weapons[0]) == (weapons[1])){
        weapons[1] = Hands::RandHand(); 
      }
      weapon = 0;  
    }
  
  
     /**
     * Overload Method : 
     *    friend ostream& operator<<(ostream& cout, const Player &P1)
     * 
     * Description:
     *      -  over loading the << operator to be able to use the ostream 
     *         operator to print out our players 'weapon' that is set 
     * 
     * Params:
     *      - [ostream] cout - it is passing through the ostream operator 
     *         and allowing us to use 'cout' within our overload 
     *      - const [Player] &P1 The Player of which we are printing
     *         off the weapons 
     *
     * Usage: 
     *      - displaying the players weapon that won
     */
    friend ostream& operator<<(ostream& cout, const Player &P1){

      cout << P1.weapons[P1.weapon];
        return cout;
    }
    
    
    // overloading the > operator to be able to easily determine a winner
    bool operator>(Player& other){
        
        //spock beats rock
        if(this->weapons[weapon] == Hands::Spock() && other.weapons[weapon] == Hands::Rock()){          
          return true;
        }
        //rock beats scissors
        else if(this->weapons[weapon] == Hands::Rock() && other.weapons[weapon] == Hands::Scissors()){          
          return true;
        }
        //paper beats rock
        else if(this->weapons[weapon] == Hands::Paper() && other.weapons[weapon] == Hands::Rock()){          
          return true;
        }
        //rock beats lizard
        else if(this->weapons[weapon] == Hands::Rock() && other.weapons[weapon] == Hands::Lizard()){          
          return true;
        }
        //scissors beats paper
        else if(this->weapons[weapon] == Hands::Scissors() && other.weapons[weapon] == Hands::Paper()){          
          return true;
        }
        //lizard beats spock
        else if(this->weapons[weapon] == Hands::Lizard() && other.weapons[weapon] == Hands::Spock()){          
          return true;
        }
        //spock beats scissors
        else if(this->weapons[weapon] == Hands::Spock() && other.weapons[weapon] == Hands::Scissors()){          
          return true;
        }
        //scissors beats lizard
        else if(this->weapons[weapon] == Hands::Scissors() && other.weapons[weapon] == Hands::Lizard()){ 
          return true;
        }
        //lizard beats paper
        else if(this->weapons[weapon] == Hands::Lizard() && other.weapons[weapon] == Hands::Paper()){          
          return true;
        }
        //paper beats spock
        else if(this->weapons[weapon] == Hands::Paper() && other.weapons[weapon] == Hands::Spock()){          
          return true;
        }
        return false;
    }
  
  
};


int main() {

//main variables
bool winner;
Player p1, p2;
int input, p1Score = 0, p2Score = 0;


cout << "Hello, Welcome to Rock, Paper, Scissors, Lizard, Spock\n"
     << "This is a more 'complex' version of the original game \n"
     << "Press '1' to play and '0' to quit at anytime. Enjoy!!!\n\n";
cin >> input;

// loop that runs the game, if user enters 0 program is terminated
while(input != 0){
  // winner will be set to true when one is found, completing the current loop 
  // and waiting for more input to determine if it will run again..
  while(winner==false){
    
    // begins by printing out the players weapons
    cout << "\nPlayer One: ";
    p1.printAllWeapons();
    
    cout << "\nPlayer Two: ";
    p2.printAllWeapons();
    
    cout << endl;

    // if we get a total tie, do this
    if(p1.weaponCheck(0) == p2.weaponCheck(0) && p1.weaponCheck(1) == p2.weaponCheck(1)){
      cout << "Its a Tie!!!" << endl;
      winner = true;
    }


    // if just the first weapons are the same do this
    if(p1.weaponCheck(0) == p2.weaponCheck(0)){
      
      p1.setWeapon(1); // setting the outputted weapon and conditional check to 1 
      p2.setWeapon(1); // this allows the checks to happen on the second weapon
      
      // the driving logic behind the game, this will determine the winner of the second weapons
      if(p1>p2){
        cout << "Player 1's " << p1 << " Beat Players 2's " << p2 << endl; 
        p1Score++;      // add score
        winner = true;  // back to top 
      }else if(p2>p1){
        cout << "Player 2's " << p2 << " Beat Players 1's " << p1 << endl; 
        p2Score++;      // add score
        winner = true;  // back to top 
      }
    }

    // if the first weapons arent the same do this
    if(p1.weaponCheck(0) != p2.weaponCheck(0)){
      if(p1>p2){
        cout << "Player 1's " << p1 << " Beat Players 2's " << p2 << endl;
        p1Score++;     // add score
        winner = true; // back to top 

      }else if(p2>p1){
        cout << "Player 2's " << p2 << " Beat Players 1's " << p1 << endl; 
        p2Score++;     // add score
        winner = true; // back to top 
      }
    }
    cout << "\nPlayer 1 Score: " << p1Score 
         << "  Player 2 Score: " << p2Score <<"\n\n";
    p1.weaponReset();
    p2.weaponReset();
  }
  winner = false; // make winner = false
  cin >> input;   // collect more input
  
}

}
