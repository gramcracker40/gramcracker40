/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            Vector Class
*  Title:            Basic Project Organization
*  Course:           OOP 2143
*  Semester:         Fall Semester // 2021
* 
*  Description:
*        This program deals with a more dynamic vector class that has different methods
*        from the original
*
*
*Usage:
*        There is a list of methods in the class discription that are self explanitory
*        and do various assignments. You can call them in the main function to the coordinating
*        object from the class and do various things with the vector.
* 
*  Files:            N/A
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Node for our linked list
struct node {
    int data; // data value (could be a lot more values)

    node *next;     // we always need a "link" in a linked list
    node *previous; // double linking

    node(int x, node *nex = NULL, node *prev = NULL) { // constructor to make adding values easy
        data = x;
        next = nex;
        previous = prev;
    }
};

/**
 * MyVector
 * 
 * Description:
 *      this class creates a vector that can do various dynamic tasks
 * 
 * Public Methods:
 *      - MyVector() - initializes an empty vector
 *      - MyVector(int *array, int size) - intializes the vector using an array
 *      - MyVector(string FileName) - initializes the vector using an input file
 *      - void pushFront(int value) - pushes a value to the front of the vector
 *      - void pushRear(int value) - pushes a value to the back of the vector
 *      - void pushAt(int location, int value)
 *      - void print()
 *      - void print(ofstream &outputFile)
 *      - int popFront()
 *      - int popRear()
 *      - int popAt(int location)
 *      - void inOrderpush(int value)
 *      - int find(int value)
 *      -
 *      -
 *      -
 * 
 * 
 * Usage: 
 * 
 *      - initialize a vector and use any of the methods to add, take away, and manipulate the vector in several different ways 
 */
class MyVector {
private:
    node *head; // the front of the vector
    node *tail; // the back of the vector

    int currentSize = 0;

public:
    /**
     * Constructor : MyVector(){
     * 
     * Description:
     *      - initializes key values of the class 
    */
    MyVector() {
        head = tail = NULL;
    }

    /**
     * Constructor : MyVector(int *array, int size)
     * 
     * Description:
     *      - easily lets the user intialize a vector using an array to add the values
     * 
     * Params:
     *      - [int] size - lets the program know how many iterations to make
     *      - [int] *array - the array used to take values from
     */
    MyVector(int *array, int size) {
        head = tail = NULL; // initializing variables

        for (int i = 0; i < size; i++) {
            pushRear(array[i]); // for every iteration of i add the value to the back of the vector
        }
    }

    /**
     * Constructor : MyVector(string FileName)
     * 
     * Description:
     *      - easily lets the user intialize a vector using an input file. 
     * 
     * Params:
     *      - [string] FileName - a file name is necessary to use this constructor, simply pass an input file through the parameters
     * 
     * Usage: 
     *      - Pass through an input file with all the numbers in the exact order you want them added all seperated by a single space
     *        this will allow for easy addition of the values to the vector
     */
    MyVector(string FileName) {
        int num;            // holding variable for the while loop
        head = tail = NULL; // initializing variables

        ifstream inputF;       // initializing the input file
        inputF.open(FileName); // opening file in the parameter and linking to the variable

        while (!inputF.eof()) { // while the file is not empty
            inputF >> num;      // pull in value
            pushRear(num);     // push the value to the vector
        }
    }

/**
     * Constructor : MyVector(MyVector& V1)
     * 
     * Description:
     *      - easily lets the user intialize a vector using an object of the same type. 
     * 
     * Params:
     *      - [MyVector] - you must pass another object of the same type
     * 
     * Usage: 
     *      - pass through an object of the same type and it will completely copy it.
     *        
     */
    MyVector(MyVector& V1) {              // copy constructor
      head = NULL;                        // make head = null

      node* tempPtr = V1.head;            // make a temporary pointer pointing at the head of the other object

      while(tempPtr){                     // while tempPtr is not NULL
        
        pushRear(tempPtr->data);          // push tempPtr's data to the other object
        
        tempPtr = tempPtr->next;          // increment tempPtr to the next node

      }
    }






    /**
     * Method : void pushFront(int value)
     * 
     * Description:
     *      -  a simple method that pushes the desired value to the front of the vector
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the front of the vector
     */
    void pushFront(int value) {
        node *tempPtr = new node(value); // creates a new node and adds data to it

        if (!head) {               // if head is null
            head = tail = tempPtr; // initialize the value as head and tail to start vector
            currentSize++;         // head = tail = new node(value);

        }

        else {
            // head->previous = new node(value, head);
            // head->previous = head;

            tempPtr->next = head;     // point head as the next value after tempPtr
            head->previous = tempPtr; // making the heads previous tempPtr before reinitializing head
            head = tempPtr;           // make head = value
            currentSize++;
        }
    }
/**
     * Method : void pushFront(int value)
     * 
     * Description:
     *      -  a simple method that pushes the desired value to the front of the vector
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the front of the vector
     */
    void pushFront(MyVector& V2){
      node* tempPtr = V2.tail;
      int hold;

      while(tempPtr != NULL){
        
        hold = tempPtr->data;
        pushFront(hold);
        tempPtr = tempPtr->previous;
        currentSize++;

      }
    }


    /**
     * Method : void pushRear(int value)
     * 
     * Description:
     *      -  a simple method that pushes the desired value to the back of the vector
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the rear of the vector
     */
    void pushRear(int value) {
        node *tempPtr = new node(value);

        if (!head) {               // if head = null
            head = tail = tempPtr; // make value = head and tail
            currentSize++;

        } else {
            tail->next = tempPtr;     // tails next = to new value
            tempPtr->previous = tail; // making tempPtr's previous point at the old tail before reinitializing
            tail = tempPtr;           // make new value the tail

            currentSize++;
        }
    }
/**
     * Method : void pushRear(MyVector& V2)
     * 
     * Description:
     *      -  pushes an entire other vector to the back of the vector
     * 
     * Params:
     *      - [MyVector& V2] - passes through the other object to be copied
     * 
     * Usage: 
     *      - use it to push other vectors in to each other
     */
    void pushRear(MyVector& V2){   
      node* tempPtr = V2.head;     // setting the tempptr = to the passed through vector's head
      int hold;             

      while(tempPtr != NULL){
        
        hold = tempPtr->data;      // creating a holding variable for data
        pushRear(hold);            // push the data to the back
        tempPtr = tempPtr->next;   // point tempptr at the next node
        currentSize++;             // increment current size
      }
    }

    /**
     * Method : void pushAt(int location, int value)
     * 
     * Description:
     *      -  pushes the value to the desired location the user chooses
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     *      - [int] location - the desired location 
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the location the user chooses
     */
    void pushAt(int location, int value) {
      int position = 0; // set position = 0
      //node* tempPtr = new node(value);
      node *tempPtr = head; // create temp ptr and set = to head

      if (location == 0) {  // if location = 0
          pushFront(value); // push the value to the front
          currentSize++;
      } else {
          while (tempPtr->next != nullptr) { // while tempPtr has a next

              tempPtr = tempPtr->next; // increment the value of tempPtr to traverse the linked list
              position++;              // increment the value of position by 1

              node *temp2 = tempPtr->previous; // creating second tempPtr value to point at the previous

              if (location == position) {                                  // when location = position
                  tempPtr = tempPtr->previous;                             // place the tempPtr behind the current node linking it to the previous node
                  tempPtr->next = new node(value, tempPtr->next, tempPtr); // set tempPtr->next equal to a new node that we are placing in this position
                  currentSize++;                                           // -- and make its next = to tempPtr's next. but it's previous = to tempPtr

                  // tempPtr->previous = new node(value, tempPtr, temp2);
                  break;
              }
          }
      }
  }

    /**
     * Method : void print()
     * 
     * Description:
     *      -  prints out the users vector as it currently is
     * 
     * 
     * Usage: 
     *      - use it to see what the vector is currently holding
     */
    void print() {
        node *temp = head; // creating temporary holding pointer for head

        while (temp) { // while temp is not null

            cout << temp->data; // print the value of holding pointer

            if (temp->next) { // if there is a next item
                cout << "->"; // print an arrow
            }
            temp = temp->next; // make temp point at next value
        }
        cout << "\n\n";
    }



/**
     * Method : void print(string outfile)
     * 
     * Description:
     *      -  prints out the users vector as it currently is but into an output file
     * 
     * Parameters: 
     *      - [string] outfile 
     *
     * Usage: 
     *      - use it to see what the vector is currently holding but in an output file
     */
    void print(ofstream &outFile){
      
      // ofstream outFile;
      // outFile.open(outfile);
      
      node* temp = head;

      // outFile << 
      while(temp){
        outFile << temp->data;

       
        if(temp->next){
          
          outFile <<"->";
        }
        temp = temp->next;
      }
      
        outFile << endl;
      
    }
    

    /**
         * Method : int popFront()
         * 
         * Description:
         *      -  pops the front value off of the vector
         * 
         * Usage: 
         *      - use it to pop a value off the front and return it into a variable if necessary 
         */
    int popFront() {
        int dat;

        if (head) {

            node *temp = head; // creating temporary holding pointer
            head = head->next; // making the next value in the vector the head
            dat = temp->data;  // assigning the data of temp to a variable

            delete temp; // deleting temp as a pointer
            return dat;  // returning dat to the heap

            currentSize--; // taking away a value from current size
        } else {
            cout << "There are no values to pop....";
            return -1;
        }
    }

    /**
         * Method : int popRear()
         * 
         * Description:
         *      -  pops the rear value off of the vector and returns it to the terminal
         * 
         * 
         * Usage: 
         *      - use it to return the rear value to a variale within the main code or simply to remove it
         */
    int popRear() { //ask griffin - ERRORS
        int dat;

        if (head != NULL) {
            node *temp = tail;     // creating temporary holding pointer
            tail = tail->previous; // make tail = to the previous value of the node
            tail->next = nullptr;
            dat = temp->data;      // hold the data in a variable

            delete temp; // delete temporary holding pointer
            return dat;  // return the value to the system

            currentSize--; // take away a value from the current size

        } else {
            cout << "There are no values to pop...";
            return -1;
        }
    }

/**
     * Method : int popAt(int location)
     * 
     * Description:
     *      -  pops a certain value off at a certain location
     * 
     * Params:
     *      - [int] location - the desired location the user wants popped off
     * 
     * Usage: 
     *      - pops a value set in the parameter to the location the user chooses
     */
    int popAt(int location) {

        int position = -1; // set position = 0
        int dat;
        //node* tempPtr = new node(value);
        node *tempPtr = head; // create temp ptr and set = to head

        if (location == 0) { // if location = 0
            popFront();      // push the value to the front
            currentSize--;
            
        } 
        else {
          while (tempPtr->next != NULL && location != position) {       // while tempPtr has a next and location is not equal to position

              tempPtr = tempPtr->next;  // increment the value of tempPtr to traverse the linked list
              position++;               // increment the value of position by 1
             
            }
           
            if(tempPtr == tail){        // if tempPtr == tail
              popRear();                // pop the back element off
              currentSize--;            // take off one from current size
            }

            if(position == location){
              tempPtr = tempPtr -> previous;                // point tempPtr at previous
              tempPtr->previous->next = tempPtr->next;      // the previous node's next is equal to the node in front of tempPtr
              tempPtr->next->previous = tempPtr->previous;  // the previous of the node in front of tempPtr is equal to the node behind tempPtr 
              
              dat = tempPtr->data;                          // make dat = to tempPtr's data
              currentSize--;
              delete tempPtr;                               // delete tempPtr
              return dat;                                   // return dat to heap
              
            }

        }
        return -1;
    }


/**
     * Method : void inOrderPush(int value)
     * 
     * Description:
     *      -  pushes a value in order from least to greatest, assuming the vector is already sorted
     * 
     * Params:
     *      - [int] value - the value the user wants pushed
     * 
     * Usage: 
     *      - use it to build sorted lists of values
     */
    void inOrderPush(int value) { 

        node* tempPtr = new node(value);              // make the temporary node = to value
        
        if(!head) {                                   // if head is not null
          // head = tail = tempPtr;
          head = new node(value);                     // make the new node the head
          currentSize++;                              // increment current size ++
        }
        else{
          if(tempPtr->data < head->data){             // if tempptr's data is less then heads data
            tempPtr->next = head;                     // make temp ptr's next = to head
            head->previous = tempPtr;                 // make heads previous = tempptr
            head = tempPtr;                           // make tempptr head
            currentSize++;                            // increment current size
          }
          else if(tempPtr->data > tail->data){        // if temp ptr's value is greater than the tails value
            tempPtr->previous = tail;                 // point tempPtr's previous at the tail
            tail->next = tempPtr;                     // make the tails next = to tempptr
            tail = tempPtr;                           // make tail = tempPtr
            currentSize++;                            // inccrement current size
          }
          else{
            node* prev = head;
            node* curr = head;
            
            while(curr->data < tempPtr->data){        // while curr pointer's data is less than tempPtr's data
              prev = curr;                            // set prev and curr as equivalent
              curr = curr->next;                      // curr's next pointing at curr
            }
            prev->next = tempPtr;                     // the pointer prev's next is pointing at tempPtr
            tempPtr->previous = prev;                 // tempPtr's previous is pointing at prev
            tempPtr->next = curr;                     // tempPtr's next is curr;
            curr->previous = tempPtr;                 // the pointer curr's previous is tempPtr
            currentSize++;                            // increment size by 1
          }
        }


        

          
          
    }
    /**
     * Method : int find(int value)
     * 
     * Description:
     *      -  looks through the vector to determine if the value in the paramater is within it
     * 
     * Params:
     *      - [int] value - the value the user wants found
     * 
     * Usage: 
     *      - use it to determine if there are values of interest within your vector
     */
    int find(int value){
        
        int position = 0;       // declaring the position in the vector

        node* tempPtr = head;   // the pointer tempPtr is equal to head
        

        if(tempPtr == NULL ){   // if tempPtr is Null
          
          return -1;            // return -1
        }


        while(tempPtr != NULL && tempPtr->data != value) {    // while tempPtr is not equal to NULL and tempPtr's data is not equal to value
          position++;                    // increment size by 1
          tempPtr = tempPtr ->next;      // make tempPtr equal to tempPtr's next

        }
        if(position == currentSize){     // if the position is equal to the current size
          position = -1;                 // print -1 because it does not exist in the vector (false)
        }
        return position;                 // if it was found the if statement was above and processed the while loop results into position of vector completing task
    }




};          
        

int main() {

  ofstream outputFile;
  outputFile.open("test.out");
    
    
    //string outputFile = "test.out";
    int x;
    MyVector v1;
    v1.pushFront(18);
    v1.pushFront(20);
    v1.pushFront(25);
    v1.pushRear(18);
    v1.pushRear(20);
    v1.pushRear(25);
    v1.print();
    v1.print(outputFile);
    // [25, 20, 18, 18, 20, 25]

    int A[] = {11,25,33,47,51};
    MyVector v2(A,5);
    v2.print();
    v2.print(outputFile);
    // [11, 25, 33, 47, 51]

    v2.pushFront(9);
    v2.inOrderPush(27);
    v2.pushRear(63);
    v2.print(outputFile);
    v2.print();
    // [9, 11, 25, 27, 33, 47, 51, 63]

    v1.pushRear(v2);
    v1.print(outputFile);
    v1.print();
    // [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

    x = v1.popFront();
    x = v1.popFront();
    x = v1.popFront();
    v1.print(outputFile);
    v1.print();
    // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
    cout<<x<<endl;
    outputFile << x << endl;
    // 18

    x = v1.popRear();
    x = v1.popRear();
    x = v1.popRear();
    v1.print(outputFile);
    v1.print();
    // [18, 20, 25, 9, 11, 25, 27, 33]
    cout<<x<<endl;
    outputFile << x << endl;
    // 47

    x = v2.popAt(3);
    v2.print(outputFile);
    v2.print();
    // [9, 11, 25, 33, 47, 51, 63]
    cout<<x<<endl;
    outputFile << x << endl;
    // 27

    x = v2.find(51);
    cout<<x<<endl;
    outputFile << x << endl;
    // 5

    x = v2.find(99);
    cout<<x<<endl;
    outputFile << x << endl;
    // -1

    MyVector v3(v1);
    v3.print(outputFile);
    v3.print();
    // [18, 20, 25, 9, 11, 25, 27, 33]

    v3.pushFront(v2);
    v3.print(outputFile);
    v3.print();
    //[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

    MyVector v4("input.dat");
    v4.pushRear(v3);
    v4.print(outputFile);
    v4.print();
    // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]


}
