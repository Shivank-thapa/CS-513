/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053_Assign03_Q2_XXX.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_Assign03_Q2_XXX.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_Assign03_Q2_XXX.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 3 - Problem 2
 * Summary:     Implementation of MergeSort without using additional intermediate storage using ordered linked representation.
*/

#include <iostream>
#include <math.h>

using namespace std;


/**
 * The node class is a generic C++ class.
 * An object of Node class represents a single element in a list.
 * Each object of Node class has an element attribute and a pointer to the next element in the linked list representation of a sequence of elements.
 * The class has been defined with constructors and getters and setters for each class member.
 */
template <typename DataType>
class Node {
    // private members of the Node class to store a generic element and a next pointer.
    private:
        DataType element;
        Node<DataType> *nextPointer;

    public:
        // default constructor to create a Node object with no data.
        Node() {
            this->nextPointer = NULL;
        }

        // parametrizeed constructor to create a Node object with some data element
        Node(DataType element) {
            this->element = element;
            this->nextPointer = NULL;
        }

        /* getters and setters for members of Node class */
        DataType getElement() {
            return this->element;            
        }

        void setElement(DataType element) {
            this->element = element;
        }

        Node *getNextPointer() {
            return this->nextPointer;
        }

        void setNextPointer(Node<DataType> *nextPointer) {
            this->nextPointer = nextPointer;
        }
};



/* The function 'findMid' finds the middle node of a linked list and returns a pointer to that middle node.
   It takes as input, a pointer to the start of the list and the number of elements in the list.
   It then traverses the list till 'number of elements/2' and returns that node as the middle node.
*/
template <typename DataType>
Node<DataType> *findMid(Node<DataType> *headPointer, int numberOfElements) {
    Node<DataType> *mid = headPointer;
    int nodeCount = 1;

    while(nodeCount < numberOfElements/2) {             // traverse list till mid point is reached
        nodeCount++;
        mid = mid->getNextPointer();
    }
    return mid;                                         // return a pointer to the middle node found
}



/* The 'merge' function combines to sorted list into a single list which is also sorted.
   The function uses no extra space as used in the array representation of the list, only pointers are modified to save space.
   It takes as input two pointers pointing to the start of two sorted lists.
   It then compares the elements of the two lists and keeps updating the pointers two create a single sorted list.
   The function returns the pointer to the start of the resultant sorted list.
*/
template <typename DataType>
Node<DataType> *merge(Node<DataType> *firstList, Node<DataType> *secondList) {
    Node<DataType> *mergedList = new Node<DataType>();
    Node<DataType> *temp = mergedList;

    while(firstList != NULL && secondList != NULL) {                    // traverse and compare the elements till any one list does not becomes empty
        if(firstList->getElement() <= secondList->getElement()) {       // if the element of first list is smaller or equal, update the pointer to first list
            temp->setNextPointer(firstList);                            // increment pointer of first list to compare its next element
            firstList = firstList->getNextPointer();
        }
        else {                                                          // if the element of second list is smaller, update the pointer to second list
            temp->setNextPointer(secondList);                           // increment pointer of second list to compare its next element
            secondList = secondList->getNextPointer();
        }
        temp = temp->getNextPointer();                       
    }

    if(firstList != NULL) {                                             // if first list is not empty, append all its remaining elements to end of resultant list
        temp->setNextPointer(firstList);
    }
    if(secondList != NULL) {                                            // if second list is not empty, append all its remaining elements to end of resultant list
        temp->setNextPointer(secondList);
    }

    return mergedList->getNextPointer();                                // return a pointer to the start of the merged list
}



/* The function 'mergeSort' divides the list to be sorted into two approximately equal halves and recursively solves each half and then combines them to create a single sorted list.
   It takes as input, a pointer to the start of the list to be sorted and the number of elements in the list and divides it into two halves.
   It repeats the above step till the size of list becomes 1 and them starts combining the solutions for each subproblem.
   The function returns the pointer to the start of the sorted list.
*/
template <typename DataType>
Node<DataType> *mergeSort(Node<DataType> *headPointer, int numberOfElements) {
    Node<DataType> *midPointer = NULL;
    Node<DataType> *leftHead = NULL;
    Node<DataType> *rightHead = NULL;

    if(headPointer == NULL) {                               // if there are no elements in the list, return NULL
        return NULL;
    }
    else if(headPointer->getNextPointer() == NULL) {        // if there is only one element in the list, the list is already sorted
        return headPointer;
    }
    else {                                                  // if there are more than 1 elements in the list
        midPointer = findMid(headPointer, numberOfElements);        // call the 'findMid' method to find the middle element 
        leftHead = headPointer;                                     // set start pointer of the left half of the list
        rightHead = midPointer->getNextPointer();                   // set start pointer of the right half of the list
        midPointer->setNextPointer(NULL);                           // this step breaks the list into two halves
        leftHead = mergeSort(leftHead, ceil(numberOfElements/2));       // recursively solve the left half, which contains half elements as that in the original list
        rightHead = mergeSort(rightHead, floor(numberOfElements/2));    // recursively solve the right half, which contains other half elements as that in the original list
        headPointer = merge(leftHead, rightHead);                       // merge the two halves into a single list using 'merge' function 
        return headPointer;                                             // return a pointer to the start of the sorted list
    }
}



/* The function 'insertNodeInList' takes as inserts an element to the end of the linked list.
   It takes as input, the pointer to the first element in the list and an element to be added to the list.
   It traverses the list to find the last inserted node and appends the new node to the end of the last inserted node.
*/
template <typename DataType>
Node<DataType> *insertNodeInList(Node<DataType> *headPointer, DataType elementValue) {
    Node<DataType> *nodeToInsert = new Node<DataType>(elementValue);        // create a new generic node with the received element
    
    if(headPointer == NULL) {                                               // if there is no element currently in the list, make the current node as head node
        headPointer = nodeToInsert;
    }
    else {                                                                  // traverse the list till end and insert the new node at the end
        Node<DataType> *temp = headPointer;
        while(temp->getNextPointer() != NULL) {
            temp = temp->getNextPointer();
        }
        temp->setNextPointer(nodeToInsert);
    }       
    return headPointer;                                                     // return the head pointer to the list
}



/* The function 'printList' is used to print the complete linked list, starting from head.
   It takes as input, the pointer to the first element of the generic linked list and traverses the list till it becomes NULL.
*/
template <typename DataType>
void printList(Node<DataType> *headPointer) {
    while(headPointer != NULL) {
        cout << headPointer->getElement() << " ";
        headPointer = headPointer->getNextPointer();
    }
    cout << endl;
}



/* Main Method */
int main() {
    int numberOfElements;               // stores the number of elements to be sorted
    int currentElement;                 // can be changed to the required data type
    Node<int> *headPointer = NULL;      // creating an empty list of type INT, can be changed to required data type

    cout << "Enter the number of elements to sort: ";
    cin >> numberOfElements;

    if(numberOfElements <= 0) {
        cerr << "Please enter a positive value.\n";
        exit(0);
    }

    cout << "Enter " << numberOfElements << " elements: ";
    for(int elementCount = 0; elementCount < numberOfElements; elementCount++) {
        cin >> currentElement;
        headPointer = insertNodeInList(headPointer, currentElement);                // insert each element to the ed of the linked list
    }
    
    cout << "List before sorting: ";
    printList(headPointer);

    headPointer = mergeSort(headPointer, numberOfElements);                         // sort the list and return the head pointer of the list

    cout << "List after sorting: ";
    printList(headPointer);
    return 0;
}