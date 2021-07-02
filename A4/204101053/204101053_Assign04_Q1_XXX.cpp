/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053_Assign04_Q1_XXX.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_Assign04_Q1_XXX.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_Assign04_Q1_XXX.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 4 - Problem 1
 * Summary:     Preorder and postorder traversal of a binary tree without recursion.
*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;


/**
 * A generic class 'Node' which represents a single, unique element in a binary tree.
 * Each node has a data element, a pointer to its left child and a pointer to its right child as class members.
 * A sequence of Nodes can be created and their pointers can be set properly to create a binary tree.
 */
template <typename DataType>
class Node {
    // private members of the class
    private:
        DataType element;
        Node<DataType> *leftChildPointer;                       // pointer to the left child of node
        Node<DataType> *rightChildPointer;                      // pointer to the right child of node

    public:
        // default constructor of the class. It creates an empty node.
        Node() {
            this->leftChildPointer = NULL;
            this->rightChildPointer = NULL;
        }

        // parametrized constructor of the class. It cretes a new node with some data in it.
        Node(DataType element) {
            this->element = element;
            this->leftChildPointer = NULL;
            this->rightChildPointer = NULL;
        }

        /* Getters and Setters of the class members */
        DataType getElement() {
            return this->element;
        }

        void setElement(DataType element) {
            this->element = element;
        }

        Node<DataType> *getLeftChildPointer() {
            return this->leftChildPointer;
        }

        void setLeftChildPointer(Node<DataType> *leftChildPointer) {
            this->leftChildPointer = leftChildPointer;
        }

        Node<DataType> *getRightChildPointer() {
            return this->rightChildPointer;
        }

        void setRightChildPointer(Node<DataType> *rightChildPointer) {
            this->rightChildPointer = rightChildPointer;
        }
};


/** A generic stack class implementing a stack data structure and all the operations related to stack.
 * The stack class can be used to create objects that support push, pop, top operations in LIFO manner.
 * Stack objects are used instead of recursion stack to store intermediate traversed nodes of a tree and display them in required order.
 * An object of Stack class has members stackPointer, pointing to the topmost element of stack if exists, capacity of the stack indicating the maximum elements stack can hold.
 * The stackArray member of class actually stores the elements of stack.
 */
template <typename DataType>
class Stack {
    // private members of stack class
    private:
        int stackPointer;                       // points to the top of stack
        int capacity;                           // stores capacity of stack
        DataType *stackArray;                   // stores elements of stack

    public:
        // parameterized constructor of stack class sets the capacity of stack and creates a new stackArray of required capacity
        Stack(int stackSize) {
            this->stackPointer = -1;
            this->capacity = stackSize;
            this->stackArray = new DataType[stackSize];
        }


        // returns the capacity if Stack
        int getSize() {
            return this->capacity;
        }


        // function to check whether the stack is empty or not
        bool isEmpty() {
            if(this->stackPointer == -1) {
                return true;
            }
            return false;
        }


        // function to check whether the stack is full or not
        bool isFull() {
            if(this->stackPointer == capacity-1) {
                return true;
            }
            return false;
        }


        // function to push the data passed by user into the top of stack if the stack is not full, else throws an exception
        void push(DataType data) {
            if(isFull()) {
                throw "Stack Overflow!";
            }
            stackPointer++;
            stackArray[stackPointer] = data;
        }


        // function to pop the topmost element from stack if the stack is not empty, else throws an exception
        void pop() {
            if(isEmpty()) {
                throw "Stack underflow!";
            }
            stackPointer--;
        }


        // function to return the element at the top of stack if the stack is not empty, else throws an exception
        DataType top() {
            if(isEmpty()) {
                throw "Stack underflow!";
            }
            return stackArray[stackPointer]; 
        }
};


/* Function 'preorderTraversal' traverses and prints a generic binary tree in a preorder fashion.
   It takes as input the root of the tree and the number of nodes in the binary tree.
   A stack of pointers to tree nodes is used to store the intermediate nodes during traversal and popped at their correct preorder place.
*/
template <typename DataType>
void preorderTraversal(Node<DataType> *root, int numberOfNodes) {
    Node<DataType> *currentNode;                                  

    if(root == NULL) {                                  // if root is NULL, then tree is empty
        cerr << "Root in NULL, tree is empty!\n";
        return;
    }  

    Stack<Node<DataType> *> stack(numberOfNodes);       // create a stack of pointers to nodes
    try {
        stack.push(root);                               // push the root node's pointer to stack
    } catch(char const *message) {
        cerr << message << " Cannot insert element!\n";
        return;
    }

    // push each node into stack one-by-one and pop them in Node-Left-Right (preorder) fashion
    while(!stack.isEmpty()) {                           
        try {
            currentNode = stack.top();                  // pop an element from stack
            stack.pop();
        } catch(char const *message) {
            cerr << message << " Nothing to pop!\n";
            return;
        }

        cout << currentNode->getElement() << " ";                   // print the recently popped element

        if(currentNode->getRightChildPointer() != NULL) {           
            try {
                stack.push(currentNode->getRightChildPointer());    // push the right child of current node first, so that it is popped later since Stack follows FILO structure
            } catch(char const* message) {
                cerr << message << " Cannot insert element!\n";
                return;
            }
        }

        if(currentNode->getLeftChildPointer() != NULL) {
            try {
                stack.push(currentNode->getLeftChildPointer());     // push the left child of current node second, so that it is popped earlier
            } catch(char const* message) {
                cerr << message << " Cannot insert element!\n";
                return;
            }
        }
    }

}


/* Function 'postorderTraversal' traverses and prints a generic binary tree in a postorder fashion.
   It takes as input the root of the tree and the number of nodes in the binary tree.
   A stack of pointers to tree nodes is used to store the intermediate nodes during traversal.
   It uses another stack which stores the reverse postorder traversal of the tree and then pop every element of this stack to get the postorder traversal.
*/
template <typename DataType>
void postorderTraversal(Node<DataType> *root, int numberOfNodes) {
    if(root == NULL) {                                                  // if root is NULL, tree is empty
        cerr << "Root is NULL, tree is empty!\n";
        return;
    }  

    Stack<Node<DataType> *> stack(numberOfNodes);                       // stack to store pointers to nodes of tree
    Stack<DataType> displayStack(numberOfNodes);                              // stack to store the data items of nodes in reverse postorder fashion
    Node<DataType> *current;

    try {
        stack.push(root);                                               // push the root into stack
    } catch(char const* message) {
        cerr << message << " Cannot insert element!\n";
        return;
    }

    while(!stack.isEmpty()) {                                           
        try {
            current = stack.top();                                      // pop an element from stack
            stack.pop();
        } catch(char const *message) {
            cerr << message << " Nothing to pop!\n";
            return;
        }

        try {
            displayStack.push(current->getElement());                   // push current element's data into display stack
        }
        catch(char const* message) {
            cerr << message << " Cannot insert element!\n";
            return;
        }

        if(current->getLeftChildPointer() != NULL) {                    
            try {
                stack.push(current->getLeftChildPointer());             // push the pointer to left child of current node into stack
            } catch(char const* message) {
                cerr << message << " Cannot insert element!\n";
                return;
            }
        }

        if(current->getRightChildPointer() != NULL) {
            try {
                stack.push(current->getRightChildPointer());            // push the pointer to right child of current node into stack
            } catch(char const *message) {
                cerr << message << " Cannot insert element!\n";
                return;
            }
        }
    }

    // pop every element of displayStack to print the postOrder traversal of binary tree
    while(!displayStack.isEmpty()) {
        cout << displayStack.top() << " ";
        displayStack.pop();
    }
}


/* Function 'constructBinaryTree' creates a generic binary tree from user input.
   It takes as input the root pointer of the tree and the number of nodes in the binary tree.
   It contructs a binary tree and returns the updated root of the tree.
   A queue is used to store the nodes which are currently in the tree and whose child pointers are not yet updated.
*/
template <typename DataType>
Node<DataType> *constructBinaryTree(Node<DataType> *root, int numberOfNodes) {
    
    int nodeCount = 0;
    string nodeData;
    Node<DataType> *currentNode;                        // pointer to the current node
    Node<DataType> *leftNode;                           // pointer to the left child 
    Node<DataType> *rightNode;                          // pointer to the right child
    queue<Node<DataType> *> tempQueue;                  // a queue of pointers to Node to store nodes to be added in binary tree

    cout << "Enter root node's data: ";                 
    cin >> nodeData;

    if(nodeData == "N") {
        cerr << "Root is NULL, Empty tree!";
        return NULL;
    }

    root = new Node<DataType>(nodeData);
    tempQueue.push(root);                               // enqueue the root node's pointer
    nodeCount++;

    while(nodeCount < numberOfNodes) {                  // loop till all nodes are not added to binary tree
        currentNode = tempQueue.front();                // remove a node from queue
        tempQueue.pop();

        cout << "Enter left child of node " << currentNode->getElement() << "(N for NULL): ";
        cin >> nodeData;
        if(nodeData != "N") {                           // if left child of current node is not NULL
            leftNode = new Node<DataType>(nodeData);
            currentNode->setLeftChildPointer(leftNode); // set left child pointer of current node
            tempQueue.push(leftNode);                   // enqueue the left child in queue
            nodeCount++;
        }

        if(nodeCount == numberOfNodes) {
            break;
        }

        cout << "Enter right child of node " << currentNode->getElement() << "(N for NULL): ";
        cin >> nodeData;
        if(nodeData != "N") {                               // if right child of current node is not NULL
            rightNode = new Node<DataType>(nodeData);       
            currentNode->setRightChildPointer(rightNode);   // set right child of current node
            tempQueue.push(rightNode);                      // enqueue the right child of current node
            nodeCount++;
        }
    }

    return root;                                            // return the root node's pointer
}



void displayMessage() {
    cout << " ------------------------------------------------------------------------\n";
    cout << "|    Hello! Please enter N for node values which should be NULL.        |\n"; 
    cout << "|    Here is a small example to create the following binary tree.       |\n";
    cout << "|    1                                                                  |\n";
    cout << "|     \\                                                                 |\n";
    cout << "|      2                                                                |\n";
    cout << "|     /                                                                 |\n";
    cout << "|    3                                                                  |\n";
    cout << "|    Enter the number of nodes: 3                                       |\n";            
    cout << "|    Enter root node's data: 1                                          |\n";
    cout << "|    Enter left child of node 1: N                                      |\n";
    cout << "|    Enter right child of node 1: 2                                     |\n";
    cout << "|    Enter left child of node 2: 3                                      |\n";
    cout << "|    Enter right child of node 2: N                                     |\n";
    cout << "|    PreOrder traversal                                                 |\n";  
    cout << "|    1 2 3                                                              |\n";
    cout << "|    PostOrder travesal                                                 |\n";
    cout << "|    3 2 1                                                              |\n";
    cout << " ------------------------------------------------------------------------\n\n";
}


int main() {
    int numberOfNodes;                                      // stores the number of nodes in the tree

    displayMessage();

    cout << "Enter the number of nodes: ";
    cin >> numberOfNodes;
    
    if(numberOfNodes <= 0) {
        cerr << "Please enter a positive value!\n";
        exit(0);
    }

    Node<string> *root;                                     // pointer to the root node of binary tree

    root = constructBinaryTree(root, numberOfNodes);        // create binary tree from user input
    
    cout << "\nPreOrder traversal\n";
    preorderTraversal(root, numberOfNodes);                 // traverse and print the pre-order traversal of binary tree
    
    cout << endl;

    cout << "PostOrder travesal\n";
    postorderTraversal(root, numberOfNodes);                // traverse and print the post-order traversal of binary tree
    
    cout << endl;
    return 0;
}