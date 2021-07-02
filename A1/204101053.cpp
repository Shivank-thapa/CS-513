/*  Compilation and execution environment: Linux G++

    To compile and get executable file use command:
    `g++ 204101053.cpp -o execution_file_name`
    or
    `g++ -std=c++11 204101053.cpp -o execution_file_name` 
*/

/**
 * Filename:    204101053.cpp
 * Author Name: Shivank Thapa
 * Course:      CS-513
 * Subject:     Assignment 1
 * Summary:     Perform various operations like addition, subtraction, updation, evaluation
 *              on polynomial expressions based on user choice.
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/* Poly class to create, store and perform operations on polynomial expressions
   by overloading certain operators */ 
class Poly {
    private:
        vector<pair<double, int>> terms;                           // this vector contains all the terms of a polynomial in a pair of coefficient and exponent

    public:
        /**
         * Parameterized constructor to create new term
         * @param coefficient double
         * @param exponent int
         */
        Poly(double coefficient, int exponent) {
            pair<double, int> newTerm = make_pair(coefficient, exponent);
            terms.push_back(newTerm);
        }


        // Default constructor to create temporary polynomial terms
        Poly () { }


        // Getter function for retrieving terms of polynomial
        vector<pair<double, int>> getTerms() {
            return this->terms;
        }


        // Setter function to set terms of polynomial
        void setTerms(vector<pair<double, int>> terms) {
            this->terms = terms;
        }


        // Overloaded operator += to add a term/polynomial onto another term/polynomial
        void operator +=(Poly &operand2) {
            vector<pair<double, int>> secondPolyTerms = operand2.getTerms();
            
            // iterates through both polynomials' terms and updates the first one if both have a term of same exponent
            for(auto iterator1 = this->terms.begin(); iterator1 != this->terms.end(); ++iterator1) {
                for(auto iterator2 = secondPolyTerms.begin(); iterator2 != secondPolyTerms.end(); ++iterator2) {
                    if(iterator1->second == iterator2->second) {                   
                        iterator1->first = (iterator1->first + iterator2->first);          
                        iterator2->second = -1;        
                        break;
                    }
                }
            }

            // append the remaining terms of second polynomial on the first polynomial's terms list
            for(auto &secondPolyTerm : secondPolyTerms) {
                if(secondPolyTerm.second != -1) {
                    this->terms.push_back(secondPolyTerm);
                }
            }
        }


        // Overloaded operator -= to subtract a term/polynomial from another term/polynomial
        void operator -=(Poly &operand2) {
            vector<pair<double, int>> secondPolyTerms = operand2.getTerms();

            // iterates through both polynomials' terms and updates the first one if both have a term with same exponent
            for(auto iterator1 = this->terms.begin(); iterator1 != this->terms.end(); ++iterator1) {
                for(auto iterator2 = secondPolyTerms.begin(); iterator2 != secondPolyTerms.end(); ++iterator2) {
                    if(iterator1->second == iterator2->second) {
                        iterator1->first = (iterator1->first - iterator2->first);
                        iterator2->second = -1;
                        break;
                    }
                }
            }

            // append the remaining terms of second polynomial on the first polynomial's terms list
            for(auto &secondPolyTerm : secondPolyTerms) {
                if(secondPolyTerm.second != -1) {
                    this->terms.push_back(make_pair(secondPolyTerm.first * -1, secondPolyTerm.second));         // negate the coefficient since we are subtracting
                }
            }
        }

        
        // Overloaded operator + to add a term/polynomial with another term/polynomial and return a new polynomial expression
        Poly operator +(Poly &operand2) {
            Poly resultPolynomial;

            vector<pair<double, int>> firstPolyTerms = this->getTerms();
            vector<pair<double, int>> secondPolyTerms = operand2.getTerms();
            vector<pair<double, int>> resultPolyTerms;
            pair<double,int> term;

            // iterate through both polynomials' terms and add them if they have same exponent
            for(auto iterator1 = firstPolyTerms.begin(); iterator1 != firstPolyTerms.end(); ++iterator1) {
                for(auto iterator2 = secondPolyTerms.begin(); iterator2 != secondPolyTerms.end(); ++iterator2) {
                    if(iterator1->second == iterator2->second) {
                        term = make_pair(iterator1->first + iterator2->first, iterator1->second);
                        resultPolyTerms.push_back(term);
                        iterator1->second = -1;
                        iterator2->second = -1;
                        break;
                    }
                }
            }

            // append remaining terms of first polynomial on the result polynomial's terms list
            for(auto &firstPolyTerm : firstPolyTerms) {
                if(firstPolyTerm.second != -1)
                    resultPolyTerms.push_back(firstPolyTerm);
            }

            // append remaining terms of second polynomial on the result polynomial's terms list
            for(auto &secondPolyTerm : secondPolyTerms) {
                if(secondPolyTerm.second != -1)
                    resultPolyTerms.push_back(secondPolyTerm);
            }
            
            resultPolynomial.setTerms(resultPolyTerms);

            return resultPolynomial;
        }

        
        // Overloaded operator - to add a term/polynomial from another term/polynomial and return a new polynomial expression
        Poly operator -(Poly &operand2) {
            Poly resultPolynomial;

            vector<pair<double, int>> firstPolyTerms = this->getTerms();
            vector<pair<double, int>> secondPolyTerms = operand2.getTerms();
            vector<pair<double, int>> resultPolyTerms;
            pair<double,int> term;

            // iterate through both polynomials' terms list and subtract them if they have same exponent
            for(auto iterator1 = firstPolyTerms.begin(); iterator1 != firstPolyTerms.end(); ++iterator1) {
                for(auto iterator2 = secondPolyTerms.begin(); iterator2 != secondPolyTerms.end(); ++iterator2) {
                    if(iterator1->second == iterator2->second) {
                        term = make_pair(iterator1->first - iterator2->first, iterator1->second);
                        resultPolyTerms.push_back(term);
                        iterator1->second = -1;
                        iterator2->second = -1;
                        break;
                    }
                }
            }

            // append remaining terms of first polynomial on the result polynomial's terms list
            for(auto &firstPolyTerm : firstPolyTerms) {
                if(firstPolyTerm.second != -1)
                    resultPolyTerms.push_back(make_pair(firstPolyTerm.first, firstPolyTerm.second));
            }

            // append remaining terms of second polynomial on the result polynomial's terms list
            for(auto &secondPolyTerm : secondPolyTerms) {
                if(secondPolyTerm.second != -1)
                    resultPolyTerms.push_back(make_pair(secondPolyTerm.first * -1, secondPolyTerm.second));         // negate the coefficient since we are subtracting second term from first
            }

            resultPolynomial.setTerms(resultPolyTerms);

            return resultPolynomial;
        }


        // Overloaded operator *= to multiply a constant with a polynomial expression
        void operator *=(double operand2) {
            for(auto &term : this->terms) {
                if(term.first == 0 || operand2 == 0)
                    term.first = 0;
                else
                    term.first = term.first * operand2;             // multiply each non-zero coefficient with the constant provided
            }
        }


        // Evaluates and returns the value of polynomial expression at a particular value
        double at(const double valueOfX) {
            double result = 0.0;
            double currentTermValue = 0.0;

            for(auto &term : terms) {
                currentTermValue = pow(valueOfX, term.second);       // evaluate power of the term value
                currentTermValue *= term.first;
                result += currentTermValue;
            }

            return result;
        }

};


/**
 * Displays a single polynomial expression.
 * @param Poly A poly class object.
 */
void displayPolynomial(Poly polynomial) {
    int index;
    pair<double, int> currentTerm;
    vector<pair<double, int>> polynomialExpression = polynomial.getTerms();

    for(index = 0; index < polynomialExpression.size(); index++) {
        currentTerm = polynomialExpression[index];
        if(currentTerm.first == 0)                              // if our coefficient is 0
            continue;
        if(currentTerm.second == 0)                             // if our exponent is 0
            cout << "(" << currentTerm.first << ")";
        else
            cout << "(" << currentTerm.first << "x^" << currentTerm.second << ")";
        if(index+1 < polynomialExpression.size())               // avoid displaying + sign after last term
            cout << "+";
    }
}


/**
 * Displays all polynomials created.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void displayUserPolynomials(const vector<Poly> &userPolynomialsList) {
    int index = 0;

    cout << "\nHere is your list of polynomials:";
    for(auto &currentPolynomial : userPolynomialsList) {            // iterate through our polynomial list
        cout << "\nPolynomial " << index << ": "; 
        displayPolynomial(currentPolynomial);
        index++;
    }
    cout << "\n";
}


/**
 * Create a new Poly class object and adds to the polynomials list.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void createNewPolynomial(vector<Poly> &userPolynomialsList) {
    double coefficient;
    int exponent, numberOfTerms;
    Poly newPolynomial;

    cout << "Enter the number of terms in the polynomial expression: ";
    cin >> numberOfTerms;

    if(numberOfTerms <= 0) {
        cerr << "\nPlease enter a positive value.\n";
        return;
    }

    for(int index = 0 ; index < numberOfTerms; index++) {
        cout << "Enter the coefficient and exponent for term " << index+1 << ": ";
        cin >> coefficient >> exponent;         
        if(exponent < 0) {                                  // check for exponent to be a non-negative value
            cerr << "Error while creating polynomial. Exponent should be non-negative value.\n";
            index--;
            continue;
        }
        Poly term(coefficient, exponent);                   // creates temporary terms to be concatenated in polynomial
        newPolynomial += term;
    }
    
    cout << "Polynomial expression created: ";
    displayPolynomial(newPolynomial);
    userPolynomialsList.push_back(newPolynomial);           // add the new polynomial to our list
    cout << '\n';
}


/**
 * Adds a term/polynomial onto another term/polynomial and updates it.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void addToExistingPolynomial(vector<Poly> &userPolynomialsList) {
    int index1, index2;

    cout << "Enter the polynomial index to update(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index1;

    if(index1 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly firstExpression = userPolynomialsList[index1];
    
    cout << "Enter the polynomial index to be added(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index2;

    if(index2 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly secondExpression = userPolynomialsList[index2];
    
    firstExpression += secondExpression;

    cout << "Resultant polynomial expression after addition is:";
    displayPolynomial(firstExpression);
    userPolynomialsList[index1] = firstExpression;                  // update our existing polynomial
    cout << '\n';
}


/**
 * Subtracts a term/polynomial from another term/polynomial.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void subtractFromExistingPolynomial(vector<Poly> &userPolynomialsList) {
    int index1, index2;

    cout << "Enter the polynomial index to update(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index1;

    if(index1 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly firstExpression = userPolynomialsList[index1];
    
    cout << "Enter the polynomial index to be subtracted(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index2;

    if(index2 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly secondExpression = userPolynomialsList[index2];
    
    firstExpression -= secondExpression;

    cout << "Resultant polynomial expression after subtraction is:";
    displayPolynomial(firstExpression);
    userPolynomialsList[index1] = firstExpression;                  // update our existing polynomial
    cout << '\n';
}


/**
 * Adds two terms/polynomials and inserts the new polynomial in list.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void addPolynomials(vector<Poly> &userPolynomialsList) {
    int index1, index2;

    cout << "Enter first polynomial index(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index1;

    if(index1 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly firstExpression = userPolynomialsList[index1];
    
    cout << "Enter second polynomial index(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index2;

    if(index2 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }

    Poly resultPolynomial = userPolynomialsList[index1] + userPolynomialsList[index2];          // put the result in a new polynomial object
    cout << "Resultant polynomial expression after addition is:";
    displayPolynomial(resultPolynomial);                        
    userPolynomialsList.push_back(resultPolynomial);                                            // insert the new polynomial to our list
    cout << '\n';
}


/**
 * Subtracts two terms/polynomials and inserts the new polynomial into list.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void subtractPolynomials(vector<Poly> &userPolynomialsList) {
    int index1, index2;

    cout << "Enter first polynomial index(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index1;

    if(index1 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly firstExpression = userPolynomialsList[index1];
    
    cout << "Enter second polynomial index(0 to " << userPolynomialsList.size()-1 << "): ";
    cin >> index2;

    if(index2 > userPolynomialsList.size()-1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }

    Poly resultPolynomial = userPolynomialsList[index1] - userPolynomialsList[index2];          // put the result in a new polynomial object          
    cout << "Resultant polynomial expression after subtraction is:";
    displayPolynomial(resultPolynomial);            
    userPolynomialsList.push_back(resultPolynomial);                                            // insert the new polynomial to our list
    cout << '\n';
}


/**
 * Multiplies a polynomial from a constant value and updates it.
 * @param vector<Poly> Reference to a list of Poly class objects.
 */
void multiplyWithConstant(vector<Poly> &userPolynomialsList) {
    int index;
    double constantValue;

    cout << "Enter the polynomial index to be multiplied(0 to " << userPolynomialsList.size()-1 << "): "; 
    cin >> index;

    if(index > userPolynomialsList.size() - 1) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly polyExpression = userPolynomialsList[index];

    cout << "Enter the value to multiply: ";
    cin >> constantValue;

    polyExpression *= constantValue;                    // usage of overloaded operator *=

    cout << "Resultant polynomial expression after multiplication is:";
    displayPolynomial(polyExpression);
    userPolynomialsList[index] = polyExpression;
    cout << '\n';
}


/**
 * Evaluates a polynomial expression for a given value.
 * @param vector<Poly> Reference to a list of Poly class objects
 */
void evaluatePolynomial(vector<Poly> &userPolynomials) {
    int index;
    double valueOfX;

    cout << "Enter the polynomial index to be evaluated(0 to " << userPolynomials.size()-1 << "): ";
    cin >> index;

    if(index > userPolynomials.size()) {
        cerr << "Invalid index! No such polynomial exists.\n";
        return;
    }
    Poly polyExpression = userPolynomials[index];

    cout << "Enter the value at which the polynomial should be evaluated: ";
    cin >> valueOfX;

    double result = polyExpression.at(valueOfX);      

    cout << "The value of polynomial expression ";
    displayPolynomial(polyExpression);
    cout << " at x = " << valueOfX << " is: " << result << endl;
}


// Displays the list of available choices to the user
void displayChoiceMenu() {
    cout << '\n';
    cout << "1. Write a new polynomial.\n";
    cout << "2. Show all created polynomials.\n";
    cout << "3. Add and overwrite a polynomial expression with another expression.\n";
    cout << "4. Subtract and overwrite a polynomial expression from another expression.\n";
    cout << "5. Add two polynomials.\n";
    cout << "6. Subtract two polynomials.\n";
    cout << "7. Multiply polynomial with a constant.\n";
    cout << "8. Evaluate the polynomial at a particular value.\n";
    cout << "9. Exit.\n\n";
    cout << "Enter your choice(1 to 9): ";
}


// Main entry point of the program
int main() {
    int userChoice;
    vector<Poly> userPolynomialsList;         // maintains a list of all polynomials created as well as result after operations performed

    // iterate over the choices until user chooses option to exit
    do {
        displayChoiceMenu();
        cin >> userChoice;

        // based on user choice between 1 to 9, call the required method that performs the required operation
        switch (userChoice)
        {
        case 1:
            createNewPolynomial(userPolynomialsList);
            break;

        case 2:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
            } 
            else {
                cerr << "\nYou don't have any polynomials created.\n";  
            }
            break;


        case 3:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
                addToExistingPolynomial(userPolynomialsList);
            }
            else {
                cerr << "\nYou don't have any polynomials created.\n"; 
            }
            break;


        case 4:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
                subtractFromExistingPolynomial(userPolynomialsList);
            }
            else {
                cerr << "\nYou don't have any polynomials created.\n"; 
            }
            break;


        case 5:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
                addPolynomials(userPolynomialsList);
            }
            else {
                cerr << "\nYou don't have any polynomials created.\n";
            }
            break;

        
        case 6:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
                subtractPolynomials(userPolynomialsList);
            }
            else {
                cerr << "\nYou don't have any polynomials created.\n";
            }
            break;

        
        case 7:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
                multiplyWithConstant(userPolynomialsList);
            }
            else {
                cerr << "\nYou don't have any polynomials created.\n";
            }
            break;


        case 8:
            if(userPolynomialsList.size() > 0) {
                displayUserPolynomials(userPolynomialsList);
                evaluatePolynomial(userPolynomialsList);
            }
            else {
                cerr << "\nYou don't have any polynomials created.\n";
            }
            break;


        case 9:
            exit(0);

        default:
            cerr << "\nInvalid choice! Please enter a valid choice.\n";
        }

        cout << "--------------------------------------------------------------------------------------------\n\n";
    }while(true);

    return 0;
}
