/*  Compilation and execution environment: Linux g++

    To compile and get executable file use command:
    `g++ 204101053_2.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_2.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_2.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 2 - Question 2
 * Summary:     Solution of Tower of Hanoi problem non-recursively using Stack data structure
*/

#include<iostream>
#include<math.h>
#include<vector>

#define STACK_SIZE 50        // stack size is defined as 5 for testing purpose, can be modified as will

using namespace std;


/**
 * The stack class is created as a generic C++ class.
 * It implements general stack operations like push, pop and get top element.
 * The member stackPointer points to the top-most element in stack and member stackArray stores the elements of stack.
 * It throws exceptions for stack overflow and underflow conditions that must be handled appropriately.
 */
template <typename DataType>
class Stack {
    private:
        int stackPointer;
        vector<int> stackArray = vector<int>(STACK_SIZE);


    public: 
        // The constructor for stack sets the stack-pointer to -1 indicating that stack is currently empty
        Stack() {
            this->stackPointer = -1;
        }


        // Returns true if stack is empty, otherwise false
        bool isEmpty() {
            if(this->stackPointer == -1)
                return true;
            return false;
        }


        // Returns true if stack is full, otherwise false
        bool isFull() {
            if(this->stackPointer == STACK_SIZE-1)
                return true;
            return false;
        }


        // Returns the number of elements currently stored in stack
        int getSize() {
            return (stackPointer+1);
        }


        // Returns the topmost element of stack, otherwise throws an exception.
        DataType top() {
            DataType element;
            if(this->isEmpty()) {
                throw "Stack Underflow!";
            }
            element = stackArray[stackPointer];
            return element;
        }


        // Pushes an element in the stack if the stack is not full, otherwise throws an exception
        void push(DataType element) {
            if(this->isFull()) {
                throw "Stack Overflow!";
            }
            stackPointer++;
            stackArray[stackPointer] = element;
        }

        
        // Returns and removes the topmost element from stack if stack is not empty, otherwise throws an exception
        DataType pop() {
            DataType element;
            if(this->isEmpty()) {
                throw "Stack Underflow!";
            }
            element = stackArray[stackPointer];
            stackPointer--;
            return element;
        }


        // Display all elements currently present in stack from top to down if stack is non-empty, otherwise throws an exception
        void displayStack() {
            int index;
            if(this->isEmpty()) {
                throw "Stack Underflow!";
            }
            index = stackPointer;
            cout << "[ ";
            while(index >= 0) {
                cout << stackArray[index] << " "; 
                index--;
            }
            cout << " ]\n";
        }
};


/**
 * Shifts the topmost disk from source to destination.
 * Takes as argument two stack references and their names and performs the required shifting of disk.
 * After shifting prints the appropriate message about which disk is shifted in current move from and to which stack.
 */
void shiftDisk(Stack<int> &sourceStack, char sourceName, Stack<int> &destinationStack, char destinationName) {
    int topDiskFromSource, topDiskFromDestination;
    bool isSourceEmpty = false, isDestinationEmpty = false;

    try {
        topDiskFromSource = sourceStack.pop();
    } catch(const char *message) {
        isSourceEmpty = true;
    }

    try {
        topDiskFromDestination = destinationStack.pop();
    } catch(char const *message) {
        isDestinationEmpty = true;
    }

    try {
        if(isSourceEmpty) {
            sourceStack.push(topDiskFromDestination);
            cout << "Move disk " << topDiskFromDestination << " from stack " << destinationName << " to " << sourceName;
        }

        else if(isDestinationEmpty == true) {
            destinationStack.push(topDiskFromSource);
            cout << "Move disk " << topDiskFromSource << " from stack " << sourceName << " to " << destinationName;
        }

        else if(topDiskFromSource > topDiskFromDestination){
            sourceStack.push(topDiskFromSource);
            sourceStack.push(topDiskFromDestination);
            cout << "Move disk " << topDiskFromDestination << " from stack " << destinationName << " to " << sourceName;
        }
        else {
            destinationStack.push(topDiskFromDestination);
            destinationStack.push(topDiskFromSource);
            cout << "Move disk " << topDiskFromSource << " from stack " << sourceName << " to " << destinationName;
        }
        cout << endl;
    } catch(char const *message) {  
        throw message;                  // If stack overflows in middle of operations, throw an exception to calling function
    }   
}


/**
 * Computes the appropriate steps required to solve TOH problem.
 * It initializes three stacks/rods source(S), destination(D) and auxiliary(A) stack on which it performs the steps.
 * The disks are numbered as 1 to N, where N is the number of disks entered by user.
 * At each step the function checks the step number and calls the helper shiftDisk() function to move one disk at a time.
 */
void computeSteps(int numberOfDisks) {
    int diskNumber, moveNumber;
    Stack<int> sourceStack;
    char sourceName = 'S';
    Stack<int> destinationStack;
    char destinationName = 'D';
    Stack<int> auxiliaryStack;
    char auxiliaryName = 'A';

    // The total number of steps for TOH problem is given by the formula (2^N)-1, where N is the total number of disks
    int numberOfSteps = pow(2, numberOfDisks) - 1;

    if(numberOfDisks%2 == 0) {
        destinationName = 'A';
        auxiliaryName = 'D';
    }

    // Initializing the source stack, where the largest disk in placed in bottom and smallest at the topmost position
    for(diskNumber = numberOfDisks; diskNumber > 0; diskNumber--) {
        try {
            sourceStack.push(diskNumber);
        } catch(char const *message) {
            cout << message << " Cannot insert more elements!" << endl;
            return;
        }
    }

    // For each of (2^N)-1 steps, check the step number and call shiftDisk() function to move a disk from one stack to another
    // Modulo 3 is used as the number of stacks are 3, so we check each time which disks are the source and destination of current move using Modulo operation
    for(moveNumber = 1; moveNumber <= numberOfSteps; moveNumber++) {
        try {
            if(moveNumber % 3 == 0) {
                shiftDisk(auxiliaryStack, auxiliaryName, destinationStack, destinationName);
            }
            else if(moveNumber % 3 == 1) {
                shiftDisk(sourceStack, sourceName, destinationStack, destinationName);
            }
            else {
                shiftDisk(sourceStack, sourceName, auxiliaryStack, auxiliaryName);
            }
        }catch(char const *message) {                                       // if the stack gets full or empty in between computation, catch an error
            cout << "Error in computing steps. " << message << endl;
            return;
        }
    }
}


int main() {
    int numberOfDisks;          // stores the count of number of disks on which the algorithm is to run

    cout << "Enter the number of disks: ";
    cin >> numberOfDisks;

    computeSteps(numberOfDisks);           // call to the start the solution to TOH problem

    return 0;
}