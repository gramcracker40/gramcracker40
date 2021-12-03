/*****************************************************************************
* Garrett Mathers
* Professor Stringfellow
* 12/03/2021
* Program 4: Combinatorics
*
* - this program take in 4 seperate numbers, the first two being the total
*   number of schools and the total number of schools attending and the last
*   two being the total number of students at each school then the actual
*   number of students attending the contest from each school. using these
*   four numbers we figure out all of the possible combinations of students
*   from all the different schools
*
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


/* Prototypes
* itFactFunc - iterative factorial function, goes through a loop to find !
* readInOutList - reads in inpute processes it and sends it out
* findCombinations - one line formula that returns the combos of n,r
* programIntro - allows the user to choose the input/output files
* printCombos - more of a testing functions to see if findCombinations works
*/
unsigned long long int itFactFunc(int num);
void readInOutList(string inputN, string outputN);
unsigned long long int findCombinations(int n, int r);
void programIntro(string &input, string &output);
void printCombos(int num1, int num2);


int main() {
  
  string input, output;

  programIntro(input, output); 

  readInOutList(input, output);

  //printCombos(20,18)

  //printCombos(23,14)

  //printCombos(8,4)

} 


/* unsigned long long int findCombinations(int n, int r)
* input - n....r
* output - C(n,r) ... (combinations formula result)
* 
* purpose - to provide a fast calculation for usage elsewhere
*/
unsigned long long int findCombinations(int n, int r){
  return itFactFunc(n) / (itFactFunc(n-r) * itFactFunc(r)); 
}


/* void printCombos(int num1, int num2)
* input - num 1 = n.... num2 = r.
* output - C(n,r) ... (combinations formula result)
* 
* purpose - to print the combinations out
*/
void printCombos(int num1, int num2){
  int combo = findCombinations(num1, num2); 
  cout << combo; 
}


/* void programIntro(string &input, string &output)
* input - the input output files are referenced variables
* output - gets the input output file names
* 
* purpose - to implement a user input interface
*/
void programIntro(string &input, string &output){
  cout << "What is the name of the input file you're opening?\n";
  cin >> input;
  cout << "What is the name of the output file you're opening?\n";
  cin >> output;
}


/* void readInOutList(string inputN, string outputN)
* input - both the input and output file names
* output - sends the combos desired to the output file neatly
* 
* purpose - to find the combinations
*/
void readInOutList(string inputN, string outputN){
  ifstream inputF; inputF.open(inputN); //declaring/opening input file
  ofstream outputF; outputF.open(outputN); //declaring/opening output
  
  //header
  outputF << "Garrett Mathers\nProgram 4: Combinatorial Terms\n\n";

  //B = total students from each school //D = participating students
  int N,A,B,D; //N = total schools // A = #schools participating
  
  unsigned long long int schoolCombos = 0, studCombos = 0;

  //while file is not empty
  while(!inputF.eof()){
 
    inputF >> N;  // pull in 
    inputF >> A;  // each off
    inputF >> B;  // the same 
    inputF >> D;  // line
 
    //find total combinations for schools
    schoolCombos = findCombinations(N, A);
    
    //set student combos to 1
    studCombos = 1;
    
    //raise student combos to the power of A by multiplying it
    //by itself A times. 
    for(int e = 0; e < A ; e++){
     studCombos *= findCombinations(B, D);
    }

    //send the total number of combinations to the output file
    outputF << (studCombos * schoolCombos) % 1000000007 << endl;
 
  }

  //closing the input/output file file
  inputF.close();
  outputF.close(); 
}


/* unsigned long long int itFactFunc(int num)
* input - number to make a factorial of
* output - the single number form of a factorial
* 
* purpose - to make creating factorials easier for other funcs
*/
unsigned long long int itFactFunc(int num){
  unsigned long long int factorial = num;
  
  //check to make sure there are no zeros, compiler no likey divide zero
  if(num == 0){
    return 1; 
  }

  //start at 1 and then times the number by eversingle number until num
  for(int i = 1; i < num; i++){
    factorial *= i;
  }

  return factorial;
}
