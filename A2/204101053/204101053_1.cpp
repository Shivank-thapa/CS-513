/*  Compilation and execution environment: Linux g++

    To compile and get executable file use command:
    `g++ 204101053_1.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_1.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_1.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 2 - Question 1
 * Summary:     Implementation of a insert and delete operations of a queue using two stacks.
*/

#include<iostream>
#include<vector>

using namespace std;

/**
 * The stack class is created as a generic C++ class.
 * It implements general stack operations like push, pop and get top element.
 * The member stackPointer points to the top-most element in stack, stackSize stores the user defined max size of stack and member stackArray stores the elements of stack.
 * It throws exceptions for stack overflow and underflow conditions that must be handled appropriately.
 */
template <typename T>
class Stack {
    private:
        int stackPointer;
        int stackSize;
        vector<T> stackArray;

    public:
        /*  The constructor for stack follows list initialization and initializes
            the stack-pointer to -1 indicating that stack is currently empty,
            sets the stack's size to user's input
        */
        Stack(int maxStackSize) : stackPointer(-1), stackSize(maxStackSize), stackArray(maxStackSize) {

        }


        // Returns true if stack is full, otherwise false
        bool isFull() {
            if(stackPointer == stackSize-1) {
                return true;
            }
            return false;
        }


        // Returns true if stack is empty, otherwise false
        bool isEmpty() {
            if(stackPointer == -1) {
                return true;
            }
            return false;
        }


        // Returns the topmost element of stack, otherwise throws an exception.
        T top(){
            if(isEmpty()) {
                throw "Stack Underflow!";
            }
            return this->stackArray[stackPointer];
        }


        // Pushes an element in the stack if the stack is not full, otherwise throws an exception
        void push(T element) {
            if(isFull()) {
                throw "Stack Overflow!";
            }
            else {
                stackPointer++;
                stackArray[stackPointer] = element;
            }
        }


        // Returns and removes the topmost element from stack if stack is not empty, otherwise throws an exception
        T pop() {
            T element;
            if(isEmpty()) {
                throw "Stack Underflow!";
            }
            element = stackArray[stackPointer];
            stackPointer--;
            return element;
        }


        // Returns the number of elements currently stored in stack
        int getSize() {
            return stackPointer+1;
        }
};


/**
 * The Queue class is created as a generic C++ class.
 * It uses two independent stacks to implement the basic queue operations of insert and remove.
 * It uses two stack objects created using the Stack class for its successful queue implementation.
 * Insertion happens through insertionStack and deletion through deletionStack.
 */
template <typename P>
class Queue {
    private:
        Stack<P> insertionStack;
        Stack<P> deletionStack;

    public:
        // The constructor for Queue uses list initialization and initializes both insertion and deletion stacks' size.
        Queue(int maxStackSize) : insertionStack(maxStackSize), deletionStack(maxStackSize){

        }


        /**
         * This method takes an element as input and tries to insert it into insertionStack.
         * If insertionStack is full, then it checks whether deletionStack is empty or not.
         * If deletionStack is empty, it shifts all elements of insertionStack onto deletionStack and then pushes the new element on insertionStack.
         * If deletionStack is not empty, then it throws an exception as we cannot insert more elements.
         */ 
        void insert(P element) {
            P tempElement;
            if(insertionStack.isFull() == true) {
                if(deletionStack.isEmpty() == true) {               
                    while(insertionStack.isEmpty() == false) {  // if insertion stack gets full and the deletion stack is empty shift elements
                        tempElement = insertionStack.pop();
                        deletionStack.push(tempElement);
                    }
                    insertionStack.push(element);
                }
                else {
                    throw "Queue Overflow!";            // throw and exception as we can't insert any more elements in queue
                }
            }
            else {
                insertionStack.push(element);
            }
            cout << "Inserted succesfully!\n";
        }


        /**
         * This method removes an element from queue if queue is not empty, else throws an excpetion.
         * It checks whether deletionStack is empty or not. If not empty we can simply pop and return an element from deletionStack.
         * Else we can shift all elements from insertionStack to deletionStack and then pop the topmost element from deletionStack.
         */ 
        P remove() {
            P element;

            // If both stacks are empty, we have no elements in queue, throws an exception
            if(insertionStack.isEmpty() && deletionStack.isEmpty()) {
                throw "Queue Underflow!";
            }

            if(deletionStack.isEmpty() == true) {
                while(insertionStack.isEmpty() == false) {              // while there are elements in insertionStack keep shifting to deletionStack
                    element = insertionStack.pop();
                    deletionStack.push(element);
                }
                element = deletionStack.pop();
            }
            else {
                element = deletionStack.pop();
            }
            return element;
        }


        // It returns the number of elements currently present in queue by summing the number of elements in both stacks 
        int getSize() {
            int queueSize = insertionStack.getSize() + deletionStack.getSize();
            return queueSize;
        }
};


// Displays a choice menu to user to perform a desired operation
void displayChoiceMenu() {
    cout << "1. Insert an element in the queue.\n";
    cout << "2. Remove an element from the queue.\n";
    cout << "3. Get size of the queue.\n";
    cout << "4. Exit\n";
    cout << "Enter your choice(1 to 4): ";
}


int main() {
    int userChoice;             // to store desired operation's choice from user

    int element, sizeOfQueue, stackMaxSize;

    cout << "Enter maximum size for the stack (Queue's maximum size will be twice of this): ";      // ask user for size of stack and create two stacks of this size to implement queue 
    cin >> stackMaxSize;
    Queue<int> userQueue(stackMaxSize);           // The Queue class is generic and can be of any datatype, here type in declared as int.
    cout << "A queue of size " << 2*stackMaxSize << " is created.\n\n";

    while(true) {
        displayChoiceMenu();

        cin >> userChoice;

        switch(userChoice)
        {
            // User wants to insert an element to the queue
            case 1:
                cout << "Enter value to insert: ";
                cin >> element;
                try {
                    userQueue.insert(element);
                } catch(char const* message) {                      // catch exception if queue is full
                    cout << message << " Cannot insert element!\n";
                }
                break;
            

            // User wants to delete an element from the queue
            case 2:
                try {
                    element = userQueue.remove();
                    cout << "Removed element is: " << element;
                    cout << endl;
                } catch(char const* message) {                      // catch exception if queue is empty
                    cout << message << " Nothing to remove!\n";
                }
                break;


            // User wants to see the current size of the queue
            case 3:
                sizeOfQueue = userQueue.getSize();
                cout << "Number of elements in the queue are: " << sizeOfQueue;
                cout << endl;
                break;


            // User wants to exit
            case 4:
                exit(0);


            default:
                cerr << "Please enter a valid choice!\n";
        }

        cout << "---------------------------------------------------------------------\n\n";
    }

    return 0; 
}
