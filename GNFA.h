/*
 *  GNFA.h
 *
 */



#include "regex.h"
#include <vector>
#include "multiset.h"

using namespace std;
/*
 * This is the GNFA class. There is a regular expression on the transitions between the states
 * The set of states is taken in the integer noOfStates. It is assumed that set of states is represented by numbers 1 to noOfStates
 * As per the design, the Initial state is always state 0, and when there are n states, the states are named state 0 to state n-1
 */

class GNFA {
  public:
    int noOfStates; // The total finite set of states, as a human would count in a Finite State Machine
    alphabet sigma; //Variable to store the alphabet 
    //bitset <20> states; // Everything that is one is a final state. 
    //bitset* states; // everythign that is one is a final state. how do you include a bit set that you do not know the lenght to?
    typedef vector <regexNode*> transVector; //creates a new type of column vectors that hold the regular expression pointers called transVector; This will represent the receiveing states?. there will be one transvector for each state. it iwll store regular expresions going to other states. 
    vector <transVector> transFunction; // this is a vector of vectors used to store the transition function. 
    vector<bool> acceptStates;//holds in pointers 0 to n-1 states 0 to n-


    //Constructor
    GNFA(int );

    //Transition Functions
    bool setTransition (int , int , regexNode* );
    bool clearTransition (int , int );

    //Functions for States
    bool setAcceptState(int );// remember states are numbered 0 to n-1
    bool isAcceptState(int );
    bool resetAcceptState(int );
    
    //Functions for the Alphabet
    bool setAlphabet(char* );
    bool setAlphabet(alphabet);
    alphabet getAlphabet();

    bool setNoOfStates(int);

    //The following are the functions ued for display purposes
    void displayStates();
    void displayStartState();	
    void displayAcceptStates();
    void displayAlphabet();
    void displayTransitionFunction();
    void forceDisplayTransitionFunction();
    void display();	

    //Operations
    bool isNonDeterministic();
    bool isDeterministic();
    regexNode * toRegexp();

    //Friend void operator << (ostream&, GNFA& );
    friend ostream& operator << (ostream&, GNFA& );
    friend istream& operator >> (istream& , GNFA& );


  private:
    bool deleteTransition(int i, int j);
    bool setTransitionPtr(int , int , regexNode* );
    typedef vector <transVector> transMatrix; 
    vector <transMatrix> transCube; // this is a vector of vectors used to store the transition function. 
    
};

//void operator << (ostream&, GNFA& );
ostream& operator << (ostream&, GNFA& );
istream& operator >> (istream&, GNFA& );
