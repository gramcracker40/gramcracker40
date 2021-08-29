/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            A04
*  Title:            Basic Project Organization
*  Course:           OOP 2143
*  Semester:         Fall Semester // 2021
* 
*  Description:
*        This program runs a circular queue that adds the pushed value 
*        to the back and removes from the front. 
*  
*
*
*Usage:
*        Simply add commands from the class into main. ex: C1.Push(3) - this will add a integer
*        to the end of the circular queue... ex: C1.Pop() -- this takes the front integer and 
*        removes it, hence the circular queue. 
* 
*  Files:            N/A
*****************************************************************************/
#include <iostream>

using namespace std;

/**
 * Circular Array Queue
 * 
 * Description:
 *      this class contains the building blocks for a circular queue,(linked list that adds to the back and removes from the front)
 * 
 * Public Methods:
 *      - void Push(int item) // pushes the item to the back of the queue
 *      - void Pop() - // removes the front item
 *      - CircularArrayQue() //constructor with a default size of 10 locations
 *      - CircularArrayQue(int size) //constructor that allows a specified size 
 * 
 * Private Methods:
 *      - void init(int size = 0) // initializes the 'object'
 *      - bool Full() //comparative method that lets the user know when the list is full
 * 
 * Usage: 
 * 
 *      - There is two constructors, either set a specific size for the queue or let it initialize a defaulted queue to 10 integers
 *      - once initialized you can beging pushing elements into the queue and removing them with the push and pop methods. 
 *      - If you exceed the maximum amount of elements held it will print a message and let you know 
 *      
 */
class CircularArrayQue {
private:
    int *Container;  //pointer that manages all the values
    int Front;       //front of the queue
    int Rear;        //back of the queue
    int QueSize;     // # of items in the queue
    int CurrentSize; //the current size of the queue
    
   
    /**
     * Method : void init(int size = 0)
     * 
     * Description:
     *      initializes key values of the class 
     * 
     * Params:
     *      - [int] size - a parameter that signals to the method what the max number of values is for the queue
     *     
     * Returns:
     *      //void - N/A
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    /**
     * Method : bool Full()
     * 
     * Description:
     *      signals to the code when the queue is full 
     */    
    bool Full() {
        return CurrentSize == QueSize; // either true or false is returned, true when it is full, false when it is not
    }

public:
    /**
     * Method : CircularArrayQue()
     * 
     * Description:
     *      a defaulted constructor set to 10 - creates the object 
     */    
    CircularArrayQue() {
        Container = new int[10]; //creates container that holds 10 values
        init(10); //initializing all private variable
    }
    
    /**
     * Method : CircularArrayQue(int size)
     * 
     * Description:
     *      a constructor with a size paramater - allows the user to specify the number of values they want in the queue
     *      while also intializing all values and setting up the queue 
     * 
     * Params:
     *      - [int] size - a parameter that signals to the method what the max number of values is for the queue
     *     
     * Returns:
     *      //void - N/A
     */
    CircularArrayQue(int size) {   
        Container = new int[size]; //initializing the container to hold the right amount of values
        init(size); // initializing all private variable
    }

    /**
     * Method : void Push(int item)
     * 
     * Description:
     *      takes in an integer value and allocates it to the back of the list (queue push method)
     * 
     * Params:
     *      - [int] item - the value the user wants to attach to the end of the list
     *     
     * Returns:
     *      "Full!!!!" - if the queue has more values than originally designated in the constructor
     *      Nothing - the value was added to the end of the queue
     */
    void Push(int item) {
        if (!Full()) {                      // if queue is not full
            Container[Rear] = item;         // add item to back of queue
            Rear = (Rear + 1) % QueSize;    // redesignate the rear as the new item
            CurrentSize++;                  // redesignate the size of queue by adding 1 value
        } else {                            // if queue is full
            cout << "FULL!!!!" << endl;     // print the message "Full!!!!"
        }
    }

    /**
     * Method : int Pop()
     * 
     * Description:
     *      it removes the first item in the queue
     * 
     * Params:
     *      - [int] item - the value the user wants to attach to the end of the list
     *     
     * Returns:
     *      temp - the value that was taken from the front of the queue
     */
    int Pop() {
        int temp = Container[Front];      // creating temporary variable to hold the front value
        Front = (Front + 1) % QueSize;    // redesignating what the front value is to the class
        CurrentSize--;                    // taking a value away from the current size
        return temp;                      // returning temp
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

// Overloading cout in order to print this data type easily using cout syntax.
// This will print all items in the array when writing to stdout or a file.
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);             //pushing values
    C1.Push(2);
    C1.Push(3);
    C1.Push(4);
    C1.Pop();               //popping values
    
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;     //printing the queue

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << '\n';
}
