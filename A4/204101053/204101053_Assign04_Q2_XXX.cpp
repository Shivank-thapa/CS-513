/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053_Assign04_Q2_XXX.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_Assign04_Q2_XXX.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_Assign04_Q2_XXX.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 4 - Problem 2
 * Summary:     Preorder traversal of Binary Tree using Preorder threads.
*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;


/**
 * A generic class 'Node' which represents a single, unique element in a binary tree.
 * Each node has a data element, a boolean flag to indicate whether the node has preorder successor threads, a pointer to its left child and a pointer to its right child as class members.
 * A sequence of Nodes can be created and their pointers can be set properly to create a binary tree.
 */
template <typename DataType>
class Node {
    // private members of the class
    private:
        DataType element;
        bool isRightChildThread;                                // set to TRUE if this node has a thread in its right child's pointer
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
            this->isRightChildThread = true;
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

        bool getIsRightChildThread() {
            return this->isRightChildThread;
        }

        void setIsRightChildThread(bool isRightChildThread) {
            this->isRightChildThread = isRightChildThread;
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


/* Function 'preorderTraversal' traverses and prints the binary tree in preorder fashion without recursion or auxiliary space.
   It takes as input the root of a generic preorder-threaded binary tree.
   It uses the preorder threads of the binary tree to traverse the tree.
*/
template <typename DataType>
void preorderTraversal(Node<DataType> *root) {
    Node<DataType> *currentNode = root;

    if(root == NULL) {
        cerr << "Root is NULL! Tree is empty." << endl;
        return;
    }

    while(currentNode != NULL) {                                    // traverse until all nodes of tree are not covered
        cout << currentNode->getElement() << " ";                   // print current element            

        if(currentNode->getIsRightChildThread() == true) {          
            currentNode = currentNode->getRightChildPointer();      // if the right pointer of current node is a thread to preorder successor, go to that node
        }

        else if(currentNode->getLeftChildPointer() != NULL) {       // if the left child of current node is not NULL
            currentNode = currentNode->getLeftChildPointer();
        }

        else if(currentNode->getRightChildPointer() != NULL) {      // if the right child of current node is not NULL and is not a preorder thread
            currentNode = currentNode->getRightChildPointer();
        }
    }
}


/* Function 'createPreThreadedBinaryTree' creates a preorder threaded binary tree with right pointer of each node either pointing to the right child or the preorder successor.
   It takes as input the root of binary tree and the number of nodes present in the tree and returns the updated root of the tree.
   For each node it checks if the node is a left child of parent, it copies the preorder successor information from parent.
   If the node is a right child of parent, it copies the preorder successor information from left sibling if exists otherwise from parent and sets their preorder successor to itself.
*/
template <typename DataType>
Node<DataType> *createPreThreadedBinaryTree(Node<DataType> *root, int numberOfNodes) {

    int nodeCount = 0;

    string nodeData;
    Node<DataType> *currentNode;                        // stores the current or parent node
    Node<DataType> *leftNode;                           // stores the left child of parent
    Node<DataType> *rightNode;                          // stores the right child of parent
    queue<Node<DataType> *> tempQueue;                  // queue to convert nodes into threaded binary tree

    cout << "Enter root node's data: ";
    cin >> nodeData;

    root = new Node<DataType>(nodeData);                // create root node

    if(nodeData == "N") {
        cerr << "Root is NULL, Empty tree!" << endl;
        return NULL;
    }
    
    tempQueue.push(root);
    nodeCount++;

    while(nodeCount < numberOfNodes) {                                                              // loop until all nodes are not entered
        currentNode = tempQueue.front();              
        tempQueue.pop();

        cout << "Enter left child of node " << currentNode->getElement() << "(N for NULL): ";
        cin >> nodeData;
        if(nodeData != "N") {                           
            leftNode = new Node<DataType>(nodeData);
            leftNode->setRightChildPointer(currentNode->getRightChildPointer());                    // get preorder successor info from parent
            leftNode->setIsRightChildThread(true);                                                  // set right pointer thread flag to true
            currentNode->setRightChildPointer(NULL);                                                
            currentNode->setIsRightChildThread(false);                                              // reset right pointer thread flag of parent to false 
            currentNode->setLeftChildPointer(leftNode);                                             // make this node as left child of parent
            tempQueue.push(leftNode);                 
            nodeCount++;
        }

        if(nodeCount == numberOfNodes) {
            break;
        }

        cout << "Enter right child of node " << currentNode->getElement() << "(N for NULL): ";
        cin >> nodeData;
        if(nodeData != "N") {                           
            rightNode = new Node<DataType>(nodeData);
            if(currentNode->getLeftChildPointer() != NULL) {
                rightNode->setRightChildPointer((currentNode->getLeftChildPointer())->getRightChildPointer());        // get preorder successor info from left sibling, if exists
                (currentNode->getLeftChildPointer())->setRightChildPointer(rightNode);                                // set preorder successor of left sibling to itself
            }
            else {
                rightNode->setRightChildPointer(currentNode->getRightChildPointer());                                 // get preorder successor info from parent, if left sibling does not exits
            }
            currentNode->setRightChildPointer(rightNode);
            tempQueue.push(rightNode);                   
            nodeCount++;
        }
    }
    
    return root;
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
    int numberOfNodes;                                          // stores the total number of nodes in tree

    displayMessage();
    
    cout << "Enter number of nodes in tree: ";
    cin >> numberOfNodes;

    if(numberOfNodes <= 0){
        cerr << "Please enter a positive value!\n";
        exit(0);
    }

    Node<string> *root;
    
    root = createPreThreadedBinaryTree(root, numberOfNodes);    // create a preorder threaded binary tree from user input

    cout << "\nPreorder traversal" << endl;
    preorderTraversal(root);                                    // display preorder traversal
    cout << endl;
    
    return 0;
}