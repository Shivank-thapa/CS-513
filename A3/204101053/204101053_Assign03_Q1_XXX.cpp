/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053_Assign03_Q1_XXX.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053_Assign03_Q1_XXX.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053_Assign03_Q1_XXX.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 3 - Problem 1
 * Summary:     Implementation of Josephus problem using circular linked list.
*/

#include <iostream>
#include <string>

using namespace std;

/**
 * Person class stores each person present in the Josephus Problem as a node.
 * Each person has a name attribute and a pointer pointing to the person standing next/left to him.
 * The class has getters and setters defined for both its members. 
 * A Josephus ring of people is created by using objects of this class.
*/
class Person {
    // private members of class Person. Each person has a name and a pointer of Person type to point to next person in circle.
    private:
        string name;
        Person *nextPerson;
    
    public:
        // Constructor of Person class accepts the name of the person and initializes the name and next-pointer to NULL;
        Person(string name) {
            this->name = name;
            this->nextPerson = NULL;
        }

        // Setter function for class member name
        void setName(string name) {
            this->name = name;
        }

        // Getter function for class member name
        string getName() {  
            return this->name;
        }

        // Setter function for class member nextPerson
        void setNextPerson(Person *person) {
            this->nextPerson = person;
        }

        // Getter function for class member nextPerson
        Person *getNextPerson() {
            return this->nextPerson;
        }
};


/* This method takes as argument a pointer of type class Person and a name string and inserts the person at end of Josephus ring.
   It first creates a new reference for new person and checks if the ring is empty or not.
   If the ring is empty, the we set the current person as the last person.
   Else, it changes the pointer of previous last person to point to current person and make current person as last.
   The function returns pointer to the last person added to the ring.
*/
Person *insertPersonToRing(Person *lastPerson, string name) {
    Person *currentPerson = new Person(name);
    
    if(lastPerson == NULL) {                                        // if the ring is empty
        lastPerson = currentPerson;
        lastPerson->setNextPerson(lastPerson);
    }
    else {                                                          // if ring is not empty
        currentPerson->setNextPerson(lastPerson->getNextPerson());  
        lastPerson->setNextPerson(currentPerson);                   // change last person's pointer 
        lastPerson = currentPerson;                                 // set currently added person as last person
    }
    
    return lastPerson;
}


/* Utility function to print the name of each person in Josephus ring.
   Can be used to check the ring formed.
   It prints person in list starting from first person added to last person added in ring.
*/
void printPersonList(Person *lastPerson) {
    if(lastPerson == NULL) {
        cout << "No person is currently added. List is empty!\n";
        return;
    }

    Person *currentPerson = lastPerson->getNextPerson();

    do {
        cout << currentPerson->getName() << " ";
        currentPerson = currentPerson->getNextPerson();
    }while(currentPerson != lastPerson->getNextPerson());
    cout << endl;
}


/*  This function creates a ring of all people.
    It iterates over the number of people to be added and assigns each person a name, starting from A, and adds it to the Josephus ring using 'insertPersonToRing' function.
    It returns the pointer to the last added person in the ring
*/
Person *createRingOfPersons(int numberOfPeople) {
    // Using these variables to generate unique names, starting from A.
    // After reaching name Z, names start from A1, B1, C1,...,Z1, A2, B2,... and so on.
    int countTill26 = 1;
    int index = 0;
    char namePrefix = 'A';          // prefix of name like 'A' in name 'A2'
    string nameSuffix = "";         // suffix of name like '2' in name 'A2'
    Person *lastPerson = NULL;      // currently no person is added to ring so last person points to NULL

    for(int peopleCount = 1; peopleCount <= numberOfPeople; peopleCount++) {
        if(countTill26 > 26) {              // if all 26 alphabets are used
            index++;                        
            nameSuffix = to_string(index);  // change name suffix
            countTill26 = 1;                // start count from 1 again till 26
            namePrefix = 'A';               // set name prefix back to 'A' after reaching 'Z'
        }

        string personName = namePrefix + nameSuffix;        
        countTill26++;                                     
        namePrefix++;                                       // change name prefix from 'A' to 'B' and so on.
        lastPerson = insertPersonToRing(lastPerson, personName);    // call method to insert person to ring
    }
    return lastPerson;                                      
}


/*  This function starts terminating/killing person in order described and returns the last standing person.
    It takes as argument a pointer to last person, the total number of people in ring and number of people to skip killing.
    It returns the name of the last person standing in Josephus ring.
*/
void startTerminatingPersons(Person *lastPerson, int numberOfPerson, int skipCount) {
    Person *killer = lastPerson->getNextPerson();
    Person *victim;
    string killerName, victimName;
    long int linkTraversedCount = 0;                        // stores the count of the links traversed while performing the executions in ring
    
    while(numberOfPerson != 1) {                            // runs a loop till only one person remains
        int countTillK = 1;
        if(numberOfPerson == 2 && skipCount == 2) {         // person executes himself without traversing any link
            linkTraversedCount += 0;
        }
        else if(numberOfPerson <= skipCount) {               // use modulo count since there are less people than people to skip
            linkTraversedCount += (skipCount%numberOfPerson);
        } 
        else {                                              
            linkTraversedCount += skipCount;
        }

        victim = killer->getNextPerson();                   
        killerName = killer->getName();                    

        while(countTillK != skipCount) {                    // loop to find the k'th person to be executed
            countTillK++;           
            killer = victim;
            victim = victim->getNextPerson();
        }
        victimName = victim->getName();

        killer->setNextPerson(victim->getNextPerson());     // set pointer of the victim's previous person to victim's next person

        delete(victim);                                     // execute and remove victim from ring

        cout << killerName << " killed " << victimName  << '\n';    
        numberOfPerson--;   

        killer = killer->getNextPerson();                   // set killer as the next person of recently killed person
        linkTraversedCount++;                               // increment link traversed count since we moved to the next person of victim
    }
    cout << "Last person remaining is Person " << killer->getName() << endl;
    cout <<  "Number of links traversed is: " << linkTraversedCount << endl;
}

 
 /* Main method */
int main() {
    int numberOfPeople;             
    int skipCount;
    char repeatOperation = 'Y';
    Person *lastPerson = NULL;

    do {                                                    // repeat the simulation of josephus problem till user's wish
        cout << "Enter number of people in circle: ";
        cin >> numberOfPeople;

        cout << "Enter count of people to skip: ";
        cin >> skipCount;

        if(numberOfPeople > 0) {
            lastPerson = createRingOfPersons(numberOfPeople);                       // create a ring of the entered number of people
            startTerminatingPersons(lastPerson, numberOfPeople, skipCount);         // start executing people in the ring and display result
        }

        else {
            cout << "Please enter a positive value greater than 0!\n";
        }
       cout << "-------------------------------------------------------------------\n\n";
       cout << "Do you want to create another ring? Type (Y/N) and press Enter: ";
       cin >> repeatOperation;
    } while(repeatOperation == 'Y' || repeatOperation == 'y');
    
    return 0;
}
