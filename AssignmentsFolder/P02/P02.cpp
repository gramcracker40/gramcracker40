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
*        This program deals with a more dynamic vector class that has 
*        different methods
*        from the original
*
*
*Usage:
*        There is a list of methods in the class discription that are self 
*        explanitory and do various assignments. You can call them in 
*        the main function to the coordinating
*        object from the class and do various things with the vector.
*        Also tons of operators useable to manipulate the vectors accordingly
* 
*  Files:            N/A
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip> 


using namespace std;

// Node for our linked list
template <class T>
struct node {
    T data;         // data value (could be a lot more values)

    node *next;     // we always need a "link" in a linked list
    node *previous; // double linking
    
    // constructor to make adding values easy
    node(T x, node<T> *nex = NULL, node<T> *prev = NULL) {
        data = x;
        next = nex;
        previous = prev;
    }
    node(node *prev = NULL){
      int data;
      node *next = NULL;
      node *previous = prev;
    }
};

/**
 * MyVector
 * 
 * Description:
 *      this class creates a vector that can do various dynamic tasks listed
 *      below varying from an assortment of methods and overloaded operators
 * 
 * Public Methods:
 *      - MyVector() - initializes an empty vector
 *      - MyVector(MyVector& V1) - initializes a vector using a vector
 *      - MyVector(int *array, int size) - intializes vector with an array
 *      - MyVector(string FileName) - initializes the vector using a file
 *      - void pushFront(T value) - pushes a value to the front of vector
 *      - void pushFront(MyVector& V2) - pushes a vector in the front
 *      - void pushRear(T value) - pushes a value to the back of vector
 *      - void pushRear(MyVector& V2) - pushes a vector to the back 
 *      - void pushAt(int location, T value)
 *      - void print()
 *      - void print(ofstream &outputFile)
 *      - T popFront()
 *      - T popRear()
 *      - T popAt(int location)
 *      - void inOrderpush(T value)
 *      - int find(T value)
 *
 * Overloaded Operators:
 *      - int &operator[](int position) - access specific position in vector
 *      - MyVector &operator=(MyVector other) - assignment operator
 *      - friend ostream& operator<<(ostream& cout, const MyVector &V) ---
 *          allows us to cout the vector like a normal array
 *      - friend ofstream& operator<<(ofstream& cout, const MyVector &V) ---
 *          allows us to print the vector to an outfile
 *      - MyVector operator+(MyVector& other) - add values together in vector
 *      - MyVector operator-(MyVector& other) - subtract from vector
 *      - MyVector operator*(MyVector& other) - times vector values together
 *      - MyVector operator/(MyVector& other) - divide values in vectors
 *      - bool operator==(MyVector& other) - see if vectors are equivalent
 * 
 * Usage: 
 * 
 *      - initialize a vector and use any of the methods to add, take away,
 *        and manipulate the vector in several different ways 
 */
template <class T>
class MyVector {
private:
    
    node<T> *head; // the front of the vector
    node<T> *tail; // the back of the vector

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
     *      - easily lets the user intialize a vector using an 
     *        array to add the values
     * 
     * Params:
     *      - [int] size - lets the program know how many iterations to make
     *      - [int] *array - the array used to take values from
     */
    MyVector(int array[], int size) {
        head = tail = NULL;     // initializing variables

        for (int i = 0; i < size; i++) {
            pushRear(array[i]); // for every iteration of i add the value
                                // to the back of the vector
        }
    }

    /**
     * Constructor : MyVector(string FileName)
     * 
     * Description:
     *      - easily lets the user intialize a vector using an input file. 
     * 
     * Params:
     *      - [string] FileName - a file name is necessary to use this 
     *        constructor, simply pass an input file through the parameters
     * 
     * Usage: 
     *      - Pass through an input file with all the numbers in the exact 
     *        order you want them added all seperated by a single space
     *        this will allow for easy addition of the values to the vector
     */
    MyVector(string FileName) {
        int num;                // holding variable for the while loop
        head = tail = NULL;     // initializing variables

        ifstream inputF;        // initializing the input file
        inputF.open(FileName);  // opening file in the parameter and linking
                                // to the variable

        while (!inputF.eof()) { // while the file is not empty
            inputF >> num;      // pull in value
            pushRear(num);      // push the value to the vector
        }
    }

     /**
     * Constructor : MyVector(MyVector& V1)
     * 
     * Description:
     *      - easily lets the user intialize a vector using an object 
     *        of the same type. 
     * 
     * Params:
     *      - [MyVector] - you must pass another object of the same type
     * 
     * Usage: 
     *      - pass through an object of the same type and it will 
     *        completely copy it.
     *        
     */
    MyVector(MyVector& V1) {       // copy constructor
      head = NULL;                 // make head = null

      node<T>* tempPtr = V1.head;  // make a temporary pointer pointing
                                   // at the head of the other object

      while(tempPtr){              // while tempPtr is not NULL
        
        pushRear(tempPtr->data);   // push tempPtr's data to the other object
        
        tempPtr = tempPtr->next;   // increment tempPtr to the next node

      }
    }






    /**
     * Method : void pushFront(int value)
     * 
     * Description:
     *      -  a simple method that pushes the desired value to the front 
     *         of the vector
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the front of the vector
     */
    void pushFront(T value) {
        node<T> *tempPtr = new node(value); // creates a new node and
                                            // adds data to it

        if (!head) {                        // if head is null
            head = tail = tempPtr;          // initialize the value as head 
                                            // and tail to start vector
            currentSize++;                  // head = tail = new node(value);

        }

        else {
            // head->previous = new node(value, head);
            // head->previous = head;

            tempPtr->next = head;     // point head as the next value
                                      // after tempPtr
            head->previous = tempPtr; // making the heads previous tempPtr
                                      // before reinitializing head
            
            head = tempPtr;           // make head = value
            currentSize++;            // increment current size
        }
    }
     /**
     * Method : void pushFront(int value)
     * 
     * Description:
     *      -  a simple method that pushes the desired value to 
     *         the front of the vector
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the front of the vector
     */
    void pushFront(MyVector& V2){
      node<T>* tempPtr = V2.tail;     // create temporary pointer=to v2.tail
                              
      int hold;                       // holding variable

      while(tempPtr != NULL){         // while temporary pointer is not equal
                                      // to null
        
        hold = tempPtr->data;         // make holding variable = to the temp
                                      // ptr's data
        pushFront(hold);              // push this data to the front of the 
                                      // original vector

        tempPtr = tempPtr->previous;  // reinitialize temp ptr to the previous
                                      // pointer or 'next' one in the vector
        currentSize++;                // increment current size by 1

      }
    }


    /**
     * Method : void pushRear(int value)
     * 
     * Description:
     *      -  a simple method that pushes the desired value to the back 
     *         of the vector
     * 
     * Params:
     *      - [int] value - the value that the user wants to add
     * 
     * Usage: 
     *      - pushes a value set in the parameter to the rear of the vector
     */
    void pushRear(T value) {
        node<T> *tempPtr = new node(value);// creating temporary pointer with
                                           // the value passed in as data

        if (!head) {                       // if head = null
            head = tail = tempPtr;         // make value = head and tail
            currentSize++;

        } else {
            tail->next = tempPtr;          // tails next = to new value
            tempPtr->previous = tail;      // make temp's prev = tail
            tail = tempPtr;                // make new value the tail

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
      node<T>* tempPtr = V2.head;  // setting the tempptr = to the passed 
                                   // through vector's head
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
     *      - pushes a value set in the parameter to the location 
     *        the user chooses
     */
    void pushAt(int location, T value) {
      int position = 0;       // set position = 0
      
      node<T> *tempPtr = head;// create temp ptr and set = to head

      if (location == 0) {    // if location = 0
          pushFront(value);   // push the value to the front
          currentSize++;
      } else {
          // while tempPtr has a next
          while (tempPtr->next != nullptr) {     

              tempPtr = tempPtr->next;            // point temp at next node
              
              position++;                         // position + 1
              node<T> *temp2 = tempPtr->previous; // creating second tempPtr
            
              if (location == position) {   
                  tempPtr = tempPtr->previous;   
                  
                  // set tempPtr->next equal to a new node that we are 
                  // placing in this position
                  tempPtr->next = new node(value, tempPtr->next, tempPtr); 
                  currentSize++;                  // increment current size
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
        node<T> *temp = head;   // creating temporary holding pointer for head

        while (temp) {          // while temp is not null

            cout << temp->data; // print the value of holding pointer

            if (temp->next) {   // if there is a next item
                cout << "->";   // print an arrow
            }
            temp = temp->next;  // make temp point at next value
        }
        cout << "\n\n";
    }



/**
     * Method : void print(string outfile)
     * 
     * Description:
     *      -  prints out the users vector as it currently is 
     *         but into an output file
     * 
     * Parameters: 
     *      - [string] outfile 
     *
     * Usage: 
     *      - use it to see what the vector is currently holding 
     *        but in an output file
     */
    void print(ofstream &outFile){
      
      // ofstream outFile;
      // outFile.open(outfile);
      
      node<T>* temp = head;    // set temp = head to traverse

      
      while(temp){             // while temp has a next
        outFile << temp->data; // print out temps current data

       
        if(temp->next){        // if temp has a next
          
          outFile <<"->";      // print an arrow
        }
        temp = temp->next;     // set temp = to the next node
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
         *      - use it to pop a value off the front and return it into
         *        a variable if necessary 
         */
    T popFront() {
        T dat;

        if (head) {

            node<T> *temp = head; // creating temporary holding pointer   
            head = head->next;    // assigning the new head to next node
            dat = temp->data;     // assigning the data of temp to dat

            delete temp;          // deleting temp as a pointer
            return dat;           // returning dat to the heap

            currentSize--;        // taking away a value from current size
        } else {
            cout << "There are no values to pop....";
            return -1;
        }
    }

    /**
         * Method : int popRear()
         * 
         * Description:
         *      -  pops the rear value off of the vector and returns it 
         *         to the terminal
         * 
         * 
         * Usage: 
         *      - use it to return the rear value to a variale within 
         *        the main code or simply to remove it
         */
    T popRear() { 
        T dat;

        if (head != NULL) {           // if there are values
            node<T> *temp = tail;     // create temporary holding pointer  
            tail = tail->previous;    // make new tail = to previous node
            tail->next = nullptr;     // tail's next is null
            dat = temp->data;         // hold the data in a variable

            delete temp;              // delete temporary holding pointer
            return dat;               // return the value to the system

            currentSize--;            // increment size -1

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
     *      - pops a value set in the parameter to the location the 
     *        user chooses
     */
    T popAt(int location) {

        int position = -1;       // set position = 0
        T dat;                   // holding variable to be returned
        node<T> *tempPtr = head; // create temp ptr and set = to head

        if (location == 0) {     // if location = 0
            popFront();          // push the value to the front
            currentSize--;
            
        } 
        else {
          // while tempPtr has a next and location is not equal to position
          while(tempPtr->next != NULL && location != position) { 

              tempPtr = tempPtr->next;  // point temp at next node to loop
              position++;               // increment position by 1
             
            }
           
            if(tempPtr == tail){        // if tempPtr == tail
              popRear();                // pop the back element off
              currentSize--;            // take off one from current size
            }

            if(position == location){
              tempPtr = tempPtr -> previous;// point tempPtr at previous
              // the previous node's next = to the node in front of tempPtr
              tempPtr->previous->next = tempPtr->next;    
              // the previous of node in front of tempPtr=node behind tempPtr 
              tempPtr->next->previous = tempPtr->previous;
              dat = tempPtr->data;          // make dat = to tempPtr's data
              currentSize--;
              delete tempPtr;               // delete tempPtr
              return dat;                   // return dat to heap
              
            }

        }
        return -1;
    }


/**
     * Method : void inOrderPush(int value)
     * 
     * Description:
     *      -  pushes a value in order from least to greatest, 
     *         assuming the vector is already sorted
     * 
     * Params:
     *      - [int] value - the value the user wants pushed
     * 
     * Usage: 
     *      - use it to build sorted lists of values
     */
    void inOrderPush(T value) { 

        node<T>* tempPtr = new node(value);    // make the temp node = value
        
        if(!head) {                            // if head is not null
          // head = tail = tempPtr;
          head = new node(value);              // make the new node the head
          currentSize++;                       // increment current size ++
        }
        else{
          // if tempptr's data is less then heads data
          if(tempPtr->data < head->data){      
            tempPtr->next = head;              // make temps next = to head
            head->previous = tempPtr;          // make heads prev = tempptr
            head = tempPtr;                    // make tempptr head
            currentSize++;                     // increment current size
          }
          // if temp ptr's value is greater than the tails value
          else if(tempPtr->data > tail->data){ 
            tempPtr->previous = tail;          // point tempPtr's prev = tail
            tail->next = tempPtr;              // make tails next = to temp
            tail = tempPtr;                    // make tail = tempPtr
            currentSize++;                     // inccrement current size
          }
          else{
            node<T>* prev = head;
            node<T>* curr = head;
            
            // while curr pointer's data is less than tempPtr's data
            while(curr->data < tempPtr->data){
              prev = curr;           // set prev and curr as equivalent
              curr = curr->next;     // curr's next pointing at curr
            }
            prev->next = tempPtr;    // prev next is tempPtr
            tempPtr->previous = prev;// tempPtr's prev is pointing at prev
            tempPtr->next = curr;    // tempPtr's next is curr;
            curr->previous = tempPtr;// the pointer curr's prev is tempPtr
            currentSize++;           // increment size by 1
          }
        }
    }
    /**
     * Method : int find(int value)
     * 
     * Description:
     *      -  looks through the vector to determine if the value in the
     *         paramater is within it
     * 
     * Params:
     *      - [int] value - the value the user wants found
     * 
     * Usage: 
     *      - use it to determine if there are values of interest 
     *        within your vector
     */
    int find(T value){
        
        int position = 0;       // declaring the position in the vector

        node<T>* tempPtr = head;// the pointer tempPtr is equal to head
        

        if(tempPtr == NULL ){   // if tempPtr is Null
          
          return -1;            // return -1
        }

        // while temp not equal to NULL and temp data is not equal to value
        while(tempPtr != NULL && tempPtr->data != value) {    
          position++;                    // increment size by 1
          tempPtr = tempPtr ->next;      // point tempptr at next node

        }
        if(position == currentSize){     
          // print -1 because it does not exist in the vector (false)
          position = -1;                 
        }
        // if it was found the if statement was above and processed the while
        // loop results into position of vector completing task
        return position;                 
    }

    
    
    
    
    /**
     * Overload Method : int &operator[](int position)
     * 
     * Description:
     *      -  over loading the [] brackets allows us to return a specific
     *         positions value
     * 
     * Params:
     *      - [int] position - the position which you want the value from
     * 
     * Usage: 
     *      - you can use this overload to be able to easily return values
     *        from specific locations within the vector
     */
    int &operator[](int position) {                

      if(position >= currentSize){       // if position does not exist
        cout << "Error: index does not exist...";  
        exit(0);
      }else {                            // if position exists
         node<T> *temp = head;           // temp ptr = head
         for(int i = 0; i<position;i++){ // loop to position with temp
           temp = temp->next;           
         }
        return temp->data;               // return the data of temp
      }
    }
    
    /**
     * Overload Method : MyVector &operator=(MyVector other)
     * 
     * Description:
     *      -  over loading the = brackets allows us to copy over entire 
     *         vectors and even the compilation of different vectors into one
     * 
     * Params:
     *      - [MyVector] other - the vector we are copying over into the
     *                           vector before the = sign
     * 
     * Usage: 
     *      - you can use this in a multitude of ways, v1 = v2 + v3; v1 = v3;
     *        v1 = v3 - v2; etc. each will work and each are useful
     */
    MyVector &operator=(MyVector other){    
    
      node<T> *temp = head;          // make temp the head
      node<T> *garbage;              // destruction pointer
      
      while(temp!=nullptr){          // while temp isnt null
        garbage = temp;              // make garbage = temp
        temp = temp->next;           // point temp to next node
        delete garbage;              // delete garbage
      }
      
      head = tail = nullptr;         // reset head and tail to null

      node<T>* curTemp = other.head; // set temp = to other vectors head

      for(int i = 0; i < other.currentSize; i++){
        pushRear(curTemp->data);     // push the data in temp to rear of this
        curTemp = curTemp->next;     // point temp to next node
      }

      // setting current size other the vector were in to the one we copied
      this->currentSize = other.currentSize;
      
      return *this;
    }
    
    
    /**
     * Overload Method : 
     *    friend ostream& operator<<(ostream& cout, const MyVector &V)
     * 
     * Description:
     *      -  over loading the << operator to be able to use the ostream 
     *         operator to print out our vector
     * 
     * Params:
     *      - [ostream] cout - it is passing through the ostream operator 
              and allowing us to use 'cout' within our overload 
     *      - [MyVector] &V - this is the vector we are printing out. 
     *
     * Usage: 
     *      - this perk allows you to be able to print off items in your 
     *        vector using cout in main
     */
    friend ostream& operator<<(ostream& cout, const MyVector &V) {
      cout<<fixed<<setprecision(2);

      node<T> *temp = V.head; // set temp = to other vectors head

      cout << "[";  
        
        while (temp!=NULL) {  
          cout << temp->data; // print the data
          if (temp->next){    // if temp has a next
            cout << ",";      // print a comment
          }
        
          temp = temp->next;  // point temp at next node
          
        }

      cout << "]\n"; 
      return cout;
    }
    
    /**
     * Overload Method : 
     *       friend ostream& operator<<(ostream& cout, const MyVector &V)
     * 
     * Description:
     *      -  over loading the << operator to be able to use the ostream
     *         operator to print out our vector
     * 
     * Params:
     *      - [ostream] cout - it is passing through the ostream operator 
     *        and allowing us to use 'cout' within our overload to print
     *        out items.
     *      - [MyVector] &V - this is the vector we are printing out. 
     *
     * Usage: 
     *      - this perk allows you to be able to print off items in your 
     *        vector using cout in main
     */
    friend ofstream& operator<<(ofstream& cout, const MyVector &V) {
      cout<<fixed<<setprecision(2);

      node<T> *temp = V.head;  // set temp to other vectors head

      cout << "[";  
        
        while (temp!=NULL) {
          cout << temp->data;  // print the data
          if (temp->next){     // if temp has a next
            cout << ",";       // print a comment
          }
        
          temp = temp->next;   // point temp at next node
          
        }

      cout << "]\n"; 
      return cout;
    }

    /**
     * Overload Method : MyVector operator+(MyVector& other)
     * 
     * Description:
     *      -  over loading the + operator to be able to add our vectors 
     *         values together 
     * 
     * Params:
     *      - [MyVector] &other - this is the vector we are adding to the
     *        first vector 
     *
     * Usage: 
     *      - this allows you to be able to add multiple values of your 
     *        vectors together
     */
    MyVector operator+(MyVector& other){
      
      MyVector newVector;

      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;
      // if this vector is smaller than the other vector
      if(this->currentSize <= other.currentSize){
        while(thisTemp != NULL){                    
            //push both vectors first node's data added together to newVector
            newVector.pushRear(thisTemp->data + otherTemp->data);

            thisTemp = thisTemp->next;   // point this temp at next node 
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(otherTemp!= NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;   // point other temp at next node
        }
      }
      // if the other vector is smaller than this vector
      if(other.currentSize <= this->currentSize ){  
        while(otherTemp!= NULL){                    
            //push both vectors first node's data added together to newVector
            newVector.pushRear(thisTemp->data + otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(thisTemp != NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;     // point this temp at next node
        }
      }
      
      return newVector;  // return the temporary vector as new value
    }



    /**
     * Overload Method : MyVector operator-(MyVector& other)
     * 
     * Description:
     *      -  over loading the - operator to be able to subtract values
     *         from a vector off of another vector
     * 
     * Params:
     *      - [MyVector] &other - this is the vector we are subtracting from
     *        the first vector 
     *
     * Usage: 
     *      - this allows you to be able to subtract values from vector 
     *        to vector
     */
    MyVector operator-(MyVector& other){
      
      MyVector newVector;
      
      int hold = 0;

      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;
      // if this vector is smaller than the other vector
      if(this->currentSize <= other.currentSize){
        while(thisTemp != NULL){                    
            // push the outcome of this vector data - other vector data
            newVector.pushRear(thisTemp->data - otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(otherTemp!= NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // if the other vector is smaller than this vector
      if(other.currentSize <= this->currentSize ){
        while(otherTemp!= NULL){                    
            // push the outcome of this vector data - other vector data
            newVector.pushRear(thisTemp->data - otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(thisTemp != NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;  // return the temporary vector as new value
    }
    
    /**
     * Overload Method : MyVector operator*(MyVector& other)
     * 
     * Description:
     *      -  over loading the * operator to be able to multiply values
     *         in our vectors
     * 
     * Params:
     *      - [MyVector] &other - the vector we are multiplying by
     *
     * Usage: 
     *      - this allows you to be able to multiply values from vector
     *        to vector
     */
    MyVector operator*(MyVector& other){
      
      MyVector newVector;
      
      int hold = 0;

      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;

      // if this vector is smaller than the other vector
      if(this->currentSize <= other.currentSize){
        while(thisTemp != NULL){                    
            // push the outcome of this data times other data
            newVector.pushRear(thisTemp->data * otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(otherTemp!= NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // if the other vector is smaller than this vector
      if(other.currentSize <= this->currentSize ){
        while(otherTemp!= NULL){                    
            // push the outcome of this data times other data
            newVector.pushRear(thisTemp->data * otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(thisTemp != NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;  // return the temporary vector as new value
    }
    /**
     * Overload Method : MyVector operator/(MyVector& other)
     * 
     * Description:
     *      -  over loading the / operator to be able to divide values 
     *         from a vector using a vector
     * 
     * Params:
     *      - [MyVector] &other - this is the vector that is the values we   
     *        are dividing by
     *
     * Usage: 
     *      - this allows you to be able to divide values from vector 
     *        to vector
     */
    MyVector operator/(MyVector& other){
      
      MyVector newVector;
      
      int hold = 0;

      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;
      // if this vector is smaller than the other vector
      if(this->currentSize <= other.currentSize){
        while(thisTemp != NULL){                    
            if(otherTemp->data == 0){
              cout<< "Error! Can't divide by zero...";
              exit(0);
            }
            // push the outcome of this data divided by other data
            newVector.pushRear(thisTemp->data / otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node
            otherTemp = otherTemp->next; // point other temp at next node
        }
        // switch to bigger vector
        while(otherTemp!= NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // if the other vector is smaller than this vector
      if(other.currentSize <= this->currentSize ){
        while(otherTemp!= NULL){                    
            if(otherTemp->data == 0){
              cout<< "Error! Can't divide by zero...";
              exit(0);
            }
            // push the outcome of this data divided by other data
            newVector.pushRear(thisTemp->data / otherTemp->data); 

            thisTemp = thisTemp->next;   // point this temp at next node 
            otherTemp = otherTemp->next; // point other temp at next node
            
        }
        // switch to bigger vector
        while(thisTemp != NULL){
          // push the remainder of values in to newVector
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;  // return the temporary vector as new value
    }
    /**
     * Overload Method : bool operator==(MyVector& other)
     * 
     * Description:
     *      -  over loading the == operator to be able to check if the
     *         vectors hold the same values
     * 
     * Params:
     *      - [MyVector] &other - this is the vector we are comparing the
     *        first vector with 
     *
     * Usage: 
     *      - this allows you to be able to compare values from vector to 
     *        vector if(v1 == v2) do this;
     */
    bool operator==(MyVector& other){
      
      node<T>* thisTemp = this->head;  // set this temp = to this head
      node<T>* otherTemp = other.head; // set other temp = other head
      
      if(this->currentSize != other.currentSize){
          return false;                // if size not same they cant be ==
      }
      while(thisTemp){                 // while this temp has a next value
        // if this data is not equal to other data
        if(thisTemp->data != otherTemp->data){
          return false;
        }else{
          thisTemp = thisTemp->next;   // this temp point to next node
          otherTemp = otherTemp->next; // other temp point to next node
        }
        
      }  
      return true;  // all conditions are met
    }

};
        

int main() {


    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };
    
    MyVector<int> v1(a1,5);
    MyVector<int> v2(a2,3);

    ofstream fout;
    fout.open("output.txt");

    cout << v1[2] << endl;
    // writes out 3

    v1[4] = 9;
    // v1 now = [1,2,3,4,9]

    cout << v1 << endl;
    // writes out [1,2,3,4,9]` to console.

    fout << v1 << endl;
    // writes out [1,2,3,4,9]` to your output file.

    MyVector<int> v3 = v1 + v2;
    cout << v3 << endl;
    // writes out [11,22,33,4,9]` to console.

    v3 = v1 - v2;
    cout << v3 << endl;
    // writes out [-9,-18,-27,4,9]` to console.

    v3 = v2 - v1;
    cout << v3 << endl;
    // writes out [9,18,27,4,9]` to console.

    v3 = v2 * v1;
    cout << v3 << endl;
    // writes out [10,40,90,4,9]` to console.

    v3 = v1 * v2;
    cout << v3 << endl;
    // writes out [10,40,90,4,9]` to console.

    v3 = v1 / v2;
    cout << v3 << endl;
    // writes out [0,0,0,4,9]` to console.

    v3 = v2 / v1;
    cout << v3 << endl;
    // writes out [10,10,10,4,9]` to console.

    cout << (v2 == v1)<< endl;
    // writes 0 to console (false) .

    MyVector v4 = v1;
    cout << (v4 == v1) << endl;
    // writes 1 to console (true) . 
}
