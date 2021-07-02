/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053_Assign05_Q1_XXX.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_Assign05_Q1_XXX.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_Assign05_Q1_XXX.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 5 - Problem 1
 * Summary:     Program to find the k-closest elements from a given element in an array.
*/

#include <iostream>
#include <vector>

using namespace std;

/**
 * MaxHeap class that represents a max-heap data structure of integer elements and supports operations on a max-heap.
 * The main operations that can be performed on an object of this class are max-heapify, extract-max, build-max-heap.
 * These operations take support of some other helper functions like find-parent, find-left-child, find-right-child, get-size, is-empty.
 * We can pass an array of integers and its size in the constructor of MaxHeap object to build a heap for the elements in that array.
*/
class MaxHeap {
    // private members of the class
    private:
        vector<int> heapArray;              // array to store the elements currently in heap
        int heapCapacity;                   // stores the total capacity of the heap

    // public members of the class
    public:
        /* The constructor for MaxHeap class takes as input an array and its size.
           It sets the capacity of the heap to be the number of elements in array and stores elements in heapArray.
           It then calls buildMaxHeap function to converts the heapArray into a max-heap.
        */
        MaxHeap(vector<int> &arr, int maxHeapCapacity) : heapCapacity(maxHeapCapacity), heapArray(maxHeapCapacity) {
            for(int index = 0; index < heapCapacity; index++) {     
                heapArray[index] = arr[index];                      // copy the array elements to heapArray
            }
          
            buildMaxHeap(heapCapacity);                             // build a max heap from elements in heapArray
        }

        /* returns the index of the parent node of an element in heap */
        int findParent(int index) {
            return (index-1)/2;
        }


        /* returns the left child's index of a node in heap */
        int findLeftChild(int index) {                             
            return (2*index + 1);
        }


        /* returns the right child's index of a node in heap */
        int findRightChild(int index) {
            return (2*index+2);
        }

        /* returns the number of elements currently present in heap */
        int getSize() {
            return heapArray.size();
        }

        /* returns true if heap has no elements, else returns false */
        bool isEmpty() { 
            if(getSize() == 0) {
                return true;
            }
            return false;
        }


        /* The function maxHeapify maintains the max-heap property if the heap.
           It takes as arguments the index of the node which we want to move to its correct position in the max-heap.
           The function compares the node's value with its children and swaps its value with the child having largest value if exists.
           It then calls maxHeapify recursively to maintain the heap order at position with which we swapped.
        */ 
        void maxHeapify(int parentIndex) {
            int largestElementIndex = parentIndex;  

            int leftChildIndex = findLeftChild(parentIndex);                                                    // find left child of node
            int rightChildIndex = findRightChild(parentIndex);                                                  // find right child of node
            int heapSize = getSize();

            // check if leftChild is within the heap's range and has a value larger than parent's value
            if((leftChildIndex < heapSize) && (heapArray[leftChildIndex] > heapArray[largestElementIndex])) {
                largestElementIndex = leftChildIndex;
            }

            // check if rightChild is within the heap's range and has a value larger than largest value
            if((rightChildIndex < heapSize) && (heapArray[rightChildIndex] > heapArray[largestElementIndex])) {
                largestElementIndex = rightChildIndex;
            }

            // if parent was not in its correct position in max-heap, swap it with largest child and call heapify to correct the swapped node's position
            if(largestElementIndex != parentIndex) {
                int temp = heapArray[largestElementIndex];
                heapArray[largestElementIndex] = heapArray[parentIndex];
                heapArray[parentIndex] = temp;

                maxHeapify(largestElementIndex);
            }
        }

        
        /* returns the maximum/root of the heap if exists, else throws an error */
        int getMax() {
            if(isEmpty()) {
                throw "Heap is empty!";
            }
            return heapArray[0];
        }


        /* he function extractMax returns the maximum/root of the heap if exists and removes it from heap, else throws and error
           after removing the root, heap order can be disturbed so call heapify from the new root */
        int extractMax() {
            if(isEmpty()) {
                throw "Heap is empty!";
            }

            int maxElement = heapArray[0];              
            heapArray[0] = heapArray[getSize()-1];          // put the last element of heap in root's position
            heapArray.pop_back();                           // remove last element from heap, and decreasing size of heapArray

            maxHeapify(0);                                  // heapify the root to maintain max-heap property
            return maxElement;
        }


        /* The function buildMaxHeap takes as argument the size of the heapArray and calls the maxHeapify function for all non-leaf nodes to create a max-heap */ 
        void buildMaxHeap(int size) {
            for (int index = size/2; index >= 0; index--)   {
                maxHeapify(index);
            }
            
        }


        // displays the elements present in heap currently
        void displayHeap() {
            int heapSize = getSize();
            for(int index = 0; index < heapSize; index++) {
                cout << heapArray[index] << " ";
            }
            cout << endl;
        }
};


/**
 * MinHeap class that represents a min-heap data structure of integer elements and supports operations on a min-heap.
 * The main operations that can be performed on an object of this class are min-heapify, extract-min, build-min-heap.
 * These operations take support of some other helper functions like find-parent, find-left-child, find-right-child, get-size, is-empty.
 * We can pass an array of integers and its size in the constructor of MinHeap object to build a heap for the elements in that array.
*/
class MinHeap {
    // private members of the class
    private:
        vector<int> heapArray;              // array to store the elements currently in heap
        int heapCapacity;                   // stores the total capacity of the heaps

    // public members of the class
    public:
        /* The constructor for MinHeap class takes as input an array and its size.
           It sets the capacity of the heap to be the number of elements in array and stores elements in heapArray.
           It then calls buildMinHeap function to converts the heapArray into a min-heap.
        */
        MinHeap(vector<int> &arr, int heapCapacity) : heapCapacity(heapCapacity), heapArray(heapCapacity) {
            for(int index = 0; index < heapCapacity; index++) {
                heapArray[index] = arr[index];                                  // copy the array elements to heapArray
            }
            buildMinHeap(heapCapacity);                                         // build a min heap from elements in heapArray
        }

        /* returns the index of the parent node of an element in heap */
        int findParent(int index) {
            return (index-1)/2;
        }

        /* returns the left child's index of a node in heap */
        int findLeftChild(int index) {
            return (2*index + 1);
        }

        /* returns the right child's index of a node in heap */
        int findRightChild(int index) {
            return (2*index+2);
        }


        /* returns the number of elements currently present in heap */
        int getSize() {
            return heapArray.size();
        }

        /* returns true if heap has no elements, else returns false */
        bool isEmpty() { 
            if(getSize() == 0) {
                return true;
            }
            return false;
        }


        /* The function minHeapify maintains the min-heap property if the heap.
            It takes as arguments the index of the node which we want to move to its correct position in the min-heap.
            The function compares the node's value with its children and swaps its value with the child having smallest value if exists.
            It then calls minHeapify recursively to maintain the heap order at position with which we swapped.
        */ 
        void minHeapify(int parentIndex) {
            int smallestElementIndex = parentIndex;

            int leftChildIndex = findLeftChild(parentIndex);                                                         // find left child of node
            int rightChildIndex = findRightChild(parentIndex);                                                       // find right child of node
            int heapSize = getSize();

            // check if leftChild is within the heap's range and has a value smaller than parent's value
            if((leftChildIndex < heapSize) && (heapArray[leftChildIndex] < heapArray[smallestElementIndex])) {
                smallestElementIndex = leftChildIndex;
            }

            // check if rightChild is within the heap's range and has a value larger than smallest value
            if((rightChildIndex < heapSize) && (heapArray[rightChildIndex] < heapArray[smallestElementIndex])) {
                smallestElementIndex = rightChildIndex;
            }

            // if parent was not in its correct position in min-heap, swap it with smallest child and call heapify to correct the swapped node's position
            if(smallestElementIndex != parentIndex) {
                int temp = heapArray[smallestElementIndex];
                heapArray[smallestElementIndex] = heapArray[parentIndex];
                heapArray[parentIndex] = temp;

                minHeapify(smallestElementIndex);
            }
        }

        /* returns the minimum/root of the heap if exists, else throws an error */
        int getMin() {
            if(isEmpty()) {
                throw "Heap is empty!";
            }
            return heapArray[0];
        }

        /* he function extractMin returns the minimum/root of the heap if exists and removes it from heap, else throws and error
           after removing the root, heap order can be disturbed so call heapify from the new root */
        int extractMin() {
            if(isEmpty()) {
                throw "Heap is empty!";
            }
            int minElement = heapArray[0];
            heapArray[0] = heapArray[getSize()-1];                          // put the last element of heap in root's position
            heapArray.pop_back();                                           // remove last element from heap, and decreasing size of heapArray
            minHeapify(0);                                                  // heapify the root to maintain min-heap property

            return minElement;
        }

        
        /* The function buildMinHeap takes as argument the size of the heapArray and calls the minHeapify function for all non-leaf nodes to create a min-heap */ 
        void buildMinHeap(int size) {
            for (int index = size/2 - 1; index >= 0; index--)   {
                minHeapify(index);
            }
            
        }

        // displays the elements present in heap currently
        void displayHeap() {
            int heapSize = getSize();
            for(int index = 0; index < heapSize; index++) {
                cout << heapArray[index] << " ";
            }
            cout << endl;
        }
};

/*
   The function finds the index of the first occurence key value in the array and returns it.
   If the element is not present, returns -1. 
*/
int findKeyIndex(vector<int> &arr, int key) {
    for(int index = 0; index < arr.size(); index++) {
        if(arr[index] == key) {
            return index;                                       // return the index of first occurence of key element
        }
    }
    return -1;
}


/*
   The function 'partition' partitions the array around the key element such that, all elements less than key element are in its right
   and all elements in greater than key element are on its left.
s   It then returns the new index of the key element(pivot)
*/
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];                                      // set pivot element as the key element   
    int i = low-1;                      

    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {                                    // if element is less than key, shift it to left
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }   
    int temp = arr[i+1];                                        // move the pivotto its correct position
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i+1;                                                 // return the index of pivot
}


int main() {
    int arraySize;                                              
    int keyX;                                                   
    int kClosestElements;                                       

    cout << "Enter the size of array: ";
    cin >> arraySize;

    vector<int> arr(arraySize);                                     // creating an aray of elements

    cout << "Enter " << arraySize << " elements: ";
    for(int index = 0; index < arraySize; index++) {
        cin >> arr[index];
    }

    cout << "Enter the value of x (key value from which the closest numbers are to be found): ";
    cin >> keyX;

    cout << "Enter the value of k (count of closest numbers to be found): ";
    cin >> kClosestElements;

    if(kClosestElements > arraySize-1) {
        cerr << "Cannot find closest elements greater than " << arraySize-1 << endl;
        exit(0);
    }


    int index = findKeyIndex(arr, keyX);                                        // find the index of key element in array

    if(index == -1) {
        cerr << "Key element not found in array!\n";
        exit(0);
    }

    // swap the key element with the last element of array
    int temp = arr[index];
    arr[index] = arr[arraySize-1];
    arr[arraySize-1] = temp;

    int pivot = partition(arr, 0, arraySize-1);                     // partition the array around the key element

    vector<int> leftArray(arr.begin(), arr.begin()+pivot);          // store the left side elements of arr
    vector<int> rightArray(arr.begin()+pivot+1, arr.end());         // stores the right side elements of arr

    MaxHeap heap1(leftArray, pivot);                                // create a max-heap of elements in the left-array

    MinHeap heap2(rightArray, arraySize-pivot-1);                   // create a min-heap of elements in the right-array

    int heap1Root, heap2Root;
    
    cout << kClosestElements << " closest elements to " << keyX << " are: ";
    while(kClosestElements > 0) {                                   // loop until k elements are not found
        try {
            heap1Root = heap1.getMax();                             // get the max element from max-heap
        } catch(const char *message) {
            cout << heap2.extractMin() << " ";                      // if max-heap is empty, extract min element from min-heap
            kClosestElements--;
            continue;
        }

        try {
            heap2Root = heap2.getMin();                             // get the min element from min-heap
        } catch(const char *message) {
            cout << heap1.extractMax() << " ";                      // if min heap is empty, extract max element from max-heap
            kClosestElements--;
            continue;
        }

        if(keyX - heap1Root <= heap2Root - keyX) {                  // find which element is closer to the key element
            cout << heap1Root << " ";
            heap1.extractMax();
        }
        else {
            cout << heap2Root << " ";
            heap2.extractMin();
        }
        kClosestElements--;
    }
    cout << endl;
    return 0;
}