/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053_Assign05_Q2_XXX.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_Assign05_Q2_XXX.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_Assign05_Q2_XXX.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 5 - Problem 2
 * Summary:     Program to check whether a given ordering of vertices is a topological sorting for a given DAG.
*/

#include <iostream>
#include <vector>

using namespace std;


/**
 * Node class represents a single vertex in the given directed acycle graph(DAG).
 * An object of this class is a single vertex with an index representing the index of this vertex and a list representing the vertices
 * which are adjacent to this vertex and have a directed edge from this vertex.
*/
class Node {
    
    // private members of the class Node
    private:
        int index;                          // represents the index/name of the vertex
        vector<int> adjNodesList;           // represents the vertices to which a directed edge is present from this node
        
    
    // public members of the class Node
    public:

        // Constructor for Node class recieves an index/name for this vertex
        Node(int index) {
            this->index = index;
        }

        // getter function to return index of this Node
        int getIndex() {
            return this->index;
        }


        // getter function to return the list of adjacent vertices to this vertex
        vector<int> getAdjNodesList() {
            return this->adjNodesList;
        }


        // function to add a new adjacent vertex to this node
        void addAdjacentNode(int v) {
            this->adjNodesList.push_back(v);
        }


        // function to print the list of vertices that are adjacent to this vertex
        void showAdjacentNodes() {
            for(int i=0; i<adjNodesList.size(); i++) {
                cout << this->adjNodesList[i] << " ";
            }
        }
};


/*
   The function 'initialiseVertices' takes as parameter an empty list and initialises it with all vertices present in DAG 
*/ 
void initialiseVertices(vector<Node *> &vertices) {
    for(int vertexNumber = 1; vertexNumber < vertices.size(); vertexNumber++) {
        vertices[vertexNumber] = new Node(vertexNumber);                          // create a new vertex with proper index(between 1 and |V|) and add it to list of vertices
    }
}


/* 
   The function 'isVertexInSortedOrder' checks whether the recieved vertex is in topological sorted order of the DAG.
   It takes as parameters the current vertex, a boolean visited array for DAG, a boolean visited array for traversing depth of graph, and the list of vertices in DAG. 
   It checks from the current vertex, if any vertex that is reachable from current vertex is already visited, then the vertex does not follow the topological ordering and
   thus the orering given is not topological sorted.
   It runs depth first traversal on the DAG starting from the current vertex and returns false if there is a vertex that is reachable from current vertex and is already visited,
   else it returns true. 
*/
bool isVertexInSortedOrder(Node *currentVertex, vector<bool> visited, vector<bool> depthVisited, vector<Node *> vertices) {

    depthVisited[currentVertex->getIndex()] = true;                                             // mark current vertex as visited in Depth First Traversal

    vector<int> adjNodesList = currentVertex->getAdjNodesList();                                // retrieve adjacent vertices of current vertex
    
    // perform DFS on all adjacent vertices
    for(auto iterator = adjNodesList.begin(); iterator != adjNodesList.end(); iterator++) {     
        if(visited[*iterator] == true) {                                                    
            return false;                                                                       // if some vertex reachable from current vertex in order is already visited, return false
        }
        if(!depthVisited[*iterator]) {
            isVertexInSortedOrder(vertices[*iterator], visited, depthVisited, vertices);        // perform DFS of adjacent vertex
        }
    }
    
    return  true;
}


/*  
*/
bool performDepthTraversal(Node *currentVertex, vector<bool> visited, vector<Node *> vertices) {
    int numberOfVertices = vertices.size();
    vector<bool> depthVisited(numberOfVertices, false);

    bool isSorted = isVertexInSortedOrder(currentVertex, visited, depthVisited, vertices);
    
    return isSorted;
}


/*
    The function 'isOrderingSorted' checks for each vertex in the provided ordering, if it follows a topological sort of DAG.
    For each vertex in ordering, it calls performDepthTraversal function to check it follows a valid ordering or not.
    It takes as input an ordering provided by user and a list of all vertices in DAG and returns false if any vertex does not follow
    topological sort, else returns true.
*/
bool isOrderingSorted(vector<int> ordering, vector<Node *> vertices) {
    int currentNodeInOrdering;
    int numberOfVertices = vertices.size();

    vector<bool> visited(numberOfVertices, false);                                          // to mark and check the visited vertices

    // check for each vertex in ordering
    for(int vertexNumber = 1; vertexNumber < ordering.size(); vertexNumber++) {
        currentNodeInOrdering = ordering[vertexNumber];                                     

        if(currentNodeInOrdering < 1 || currentNodeInOrdering > vertices.size()-1) {        // if vertex number in ordering is incorrect, return false
            return false;
        }

        else if(visited[currentNodeInOrdering] == true) {                                   // if vertex is already visited, return false
            return false;
        }

        else {
            Node *currentVertex = vertices[currentNodeInOrdering];
            visited[currentVertex->getIndex()] = true;
            bool isOrdered = performDepthTraversal(currentVertex, visited, vertices);       // check all vertices reachable from current vertex should not be visited

            if(!isOrdered) {
                return false;
            }
        }
    }

    return true;
}


int main() {
    int numberOfVertices;                               // stores the number of vertices in DAG
    int numberOfEdges;                                  // stores the number of edges in DAG
    int sourceVertex, destinationVertex;         

    cout << "Enter number of vertices: ";
    cin >> numberOfVertices;

    vector<Node *> vertices(numberOfVertices+1);

    initialiseVertices(vertices);                       // initialise all vertices present in DAG

    cout << "Enter number of edges: ";
    cin >> numberOfEdges;

    cout << "Enter " << numberOfEdges << " directed edges in following order: ";
    cout << "source_vertex_number destination_vertex_number\n";
    cout << "Each vertex number should be in the range 1 to " << numberOfVertices << endl;
    
    // create the DAG by adding edges
    for(int i = 0; i < numberOfEdges; i++) {
        cin >> sourceVertex >> destinationVertex;
        vertices[sourceVertex]->addAdjacentNode(destinationVertex);                // add adjacent vertex to source
    } 

    // loop until user enters 'N' or 'n'
    while(true) {
        char choice;
        
        vector<int> ordering(numberOfVertices+1);

        cout << "Enter topological sort of " << numberOfVertices << " vertices to check: ";
        for(int i = 1; i <= numberOfVertices; i++) {
           cin >> ordering[i];                                                  
        }

        if(isOrderingSorted(ordering, vertices)) {                                  // check if provided ordering is topological sort
            cout << "TRUE\n";
        }
        else {
            cout << "FALSE\n";
        }

        cout << "-----------------------------------------------------------------------------------------------------\n\n";

        cout << "Do you want to test another ordering? (Y/N):  ";
        cin >> choice;

        if(choice == 'N' || choice == 'n')
            break;
    }

    return 0;
}