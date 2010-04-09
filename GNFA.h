/*
 *  GNFA.h
 *
 */



#include "regex.h"
#include <vector>
#include "multiset.h"

using namespace std;

class GNFA {
	/*
         * This is the GNFA class. There is a regular expression on the transitions between the states
	 * The set of states is taken in the integer noOfStates. It is assumed that set of states is represented by numbers 1 to noOfStates
	 * Initial state is always state 1
	 *
	 *
	 */
public:
  int noOfStates; // the total finite set of states two dimensional arrays of regular expression
  alphabet sigma; // How do you set a class that is inside a class? *question*//
//bitset <20> states; // everythign that is one is a final state. how do you include a bit set that you do not know the lenght to?
//bitset* states; // everythign that is one is a final state. how do you include a bit set that you do not know the lenght to?
  typedef vector <regex> transVector; //creates a new type of column vectors that hold the regular expression pointers called transVector; This will represent the receiveing states?. there will be one transvector for each state. it iwll store regular expresions going to other states. 
  vector <transVector> transFunction; // this is a vector of vectors used to store the transition function. 
  vector<bool> acceptStates;//holds in pointers 0-n-1 states 1 to n
  //no final states


  GNFA(int n);
  bool setTransition (int i, int j, regex k);
  bool clearTransition (int i, int j);
  bool setFinalState(int i);
  bool resetFinalState(int i);
  bool setAlphabet(char* temp);
  bool setAlphabet(alphabet);
	void GNFA::displayStates();
	void GNFA::displayStartState();	
	void GNFA::displayAcceptStates();
	void GNFA::displayAlphabet();
	//void GNFA::displayTransitionFunction();	
	void GNFA::display();	
  bool isDeterministic();
  //multiSet* testfun();
  bool isNonDeterministic();
	
	//friend void operator << (ostream&, GNFA& );
	friend ostream& operator << (ostream&, GNFA& );
	friend istream& operator >> (istream& , GNFA& );
};

//void operator << (ostream&, GNFA& );
ostream& operator << (ostream&, GNFA& );

istream& operator >> (istream& , GNFA& );
//questions, would you want me to set a two dimensional array of regex pointers or regexes?
//should alphabet here be the alphabet class or alphabet pointer. depending on that I will decide whether.h file goes in or .cpp files goes in?is//is it possible for compilers to automatically prepare a .h file?

