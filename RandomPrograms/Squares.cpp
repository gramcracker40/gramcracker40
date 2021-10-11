/*****************************************************************************
* Garrett Mathers
* Professor Stringfellow
* 10/20/2021
* Program 2: Squares
*
* - This program takes in an input file of integers (n) and returns
*     the number of squares within an nxn square recursively, itteratively
*     and through a single line formula. 
*
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// prototypes
int reccur(int n);
vector<int> pullInData(string Ifile);
int oneLine(int n);
int iterativeSol(int n);
string programExpl();
void neatOutput(vector<int> NVector, vector<int> numSquaresITT,
                vector<int> numSquaresREC, vector<int> numSquaresOL);


int main() {

  string inputF;
  inputF = programExpl(); // grabbing the name of the input file

  vector<int> NVector = pullInData(inputF); // vector of ints from inputF

  // creating vectors to hold the outcome of each functions output
  vector<int> numSquaresOL, numSquaresREC, numSquaresITT;
  
  // performing each function on the original vector pulled in from
  // the input file creating individual vectors to make sure each is the same
  for(int i = 0; i < NVector.size(); i++){
    numSquaresREC.push_back(reccur(NVector.at(i)));      // reccurance
    numSquaresITT.push_back(iterativeSol(NVector.at(i)));// iterative
    numSquaresOL.push_back(oneLine(NVector.at(i)));      // closed form
  }

  // printing the contents neatly
  neatOutput(NVector, numSquaresITT, numSquaresREC, numSquaresOL);
  
}


/*vector<int> pullInData(string Ifile)
* input - string Ifile - the name of the input file to open
* output - a vector of each element of the input file
* 
* purpose - to pull in each integer from the input file given
*/
vector<int> pullInData(string Ifile) {
  
  int num;              
  vector<int> N;        // declaring temporary vector to be returned
  
  ifstream inputF;    
  inputF.open(Ifile);   // opening input file given

  while(!inputF.eof()){
    inputF >> num;      // pulling in individual elements
    N.push_back(num);   // compiling a vector of each individual element
  }

  return N;             // returns the vector of each element in input file
  inputF.close();       // closing the input file
}


/*vector<int> performOperation(vector<int> NVec)
* input - int n
* output - the num of squares in nxn square
* 
* purpose - a one line formula that takes in n and returns 
*           the number of squares in a nxn square
*/
int oneLine(int n){

  int newN;
  
  newN = n*(n+1)*(2*n+1)/6; // the geometric summation formula for k squared
                            // this works because n = the element before 
  return newN;              // + n squared. 

}


/*int reccur(int n)
* input - int n, the nxn square to calculate 
* output - the num of squares within the nxn square
* 
* purpose - reccurence solution, calls back to add the squared
* numbers until 1 is reached, summing all of the squares
* before n and then adding n squaredon to the end of it
*  
*/
int reccur(int n){
  
  if(n>1) // if n>1 take n squared and add it to each num squared that comes
    return(pow(n,2)+reccur(n-1)); // before num when num = 1 reccur is ended
  else
    return 1;
}


/*iterativeSol(int n)
* input - int n, the nxn square to calculate 
* output - numSq, the num of squares in the nxn square 
* 
* purpose - iterative solution - usage -
*           iteratively summs the number of squares
*/
int iterativeSol(int n){
  int numSq = 0;
  
  //loop starts at 0, add 1 to n for correct answer
  for(int i = 0; i< n + 1; i++){
    numSq += pow(i,2); //summing the num squares
  }

  return numSq; 
}


/*string programExpl()
* input - N/A 
* output - the input file name of which the 
*          user would like to open 
* 
* purpose - to explain the program and return the name of the input
*           file the user would like to manipulate
*/
string programExpl(){

  // the file name to be returned
  string IfileName;

  // introduction message to the program, explains purpose and asks for input
  cout << "Hello! This program was designed to take in an integer (n) \n"
       << "and return the number of squares associated with it (nxn) \n"
       << "this program was inspired by Richard Feynman's lost notes \n"
       << "Please enter the name of the input file you would like to \n"
       << "have the operations done to...\n\n";
  cin >> IfileName;

  return IfileName;
}


/* void neatOutput(vector<int> NVector, vector<int> numSquaresITT,
*                  vector<int> numSquaresREC, vector<int> numSquaresOL)
* input - each various vector manipulated by the different functions
* output - neat, organized output to the file provided by the user
* 
* purpose - to print out orderly output to the file provided and erase
*           30 lines of code from main, which is why I wrote a 6th function
*/
void neatOutput(vector<int> NVector, vector<int> numSquaresITT,
                vector<int> numSquaresREC, vector<int> numSquaresOL)
{
  
  // asking the user for the desired output file and storing in oFile
  string oFile;
  cout << "\nPlease enter the name of the desired output file...\n\n";
  cin >> oFile;
  
  // declaring and opening the outputF
  ofstream outputF; outputF.open(oFile);

  cout << "Printing to '" << oFile << "'...\n";

  // header with the collumns
  outputF << "Garrett Mathers\nProgram 2: Squares\n"  
            <<"10/20/2021\nCMPS-2433 Discrete Structure\n\n"
            << left << setw(7)<< "N"<< right << "LoopSum" << left 
            << setw(12)<<right<< "RecSoln" <<left<< setw(12) 
            <<right << "Closed\n";

  // loops through each vector and displays the results from each 
  for(int i = 0; i< NVector.size(); i++){
    outputF << left << setw(7) << NVector.at(i)
            << right << numSquaresITT.at(i) << left << setw(12) << right
            << numSquaresREC.at(i) << left << setw(12) << right
            << numSquaresOL.at(i) << endl;
  }

  outputF.close(); // closing output file
}
