/*
 *  NFA.cpp
 *  
 *
 *  Created by Gagan Awhad on 10/31/09.
 *  Copyright 2009 Unversity of Minnesota. All rights reserved.
 *
 */

#include "bitstream.h"
#include <bitset.h> 
#include "alphabet.cpp"
#include "regexNode.cpp"
#include <vector.h>
#include <iostream.h>


using namespace std;

class GNFA {
	/*
	 * This is the GNFA class. There is a regular expression on the transitions between the states
	 * The set of states is taken in the integer noOfStates. It is assumed that set of states is represented by numbers 1 to noOfStates
	 * Initial state is always state 1
	 */
	
	int noOfStates; // the total finite set of states two dimensional arrays of regular expression
	alphabet sigma; // How do you set a class that is inside a class? *question*//
//	bitset <20> states; // everythign that is one is a final state. how do you include a bit set that you do not know the lenght to?
//	bitset* states; // everythign that is one is a final state. how do you include a bit set that you do not know the lenght to?
	typedef vector <regex> transVector; //creates a new type of column vectors that hold the regular expression pointers called transVector; This will represent the receiveing state; 
	vector <transVector> transFunction; // this is a vector of vectors used to store the transition function. 
	vector<bool> states;
	//no final states


	//This constructor creates a simple GNFA class that has states and has all possible transition functions as null set
	GNFA(int n){
		this->noOfStates = n;
//		transVector.resize(noOfStates);
		this->transFunction.resize(noOfStates);
		for (int i = 0; i<noOfStates; i++) {
			this->transFunction[i].resize(noOfStates);
		}
		this->states.resize(noOfStates);	
//		this->states = new bitset(noOfStates);
		
	}
	
	
	// Here do you want to create another constructor in which the argument n the number of states and a state of functions is given?
	
	
	
	//functions take two states and regular expression and then set the transiontion function
	void setTransition (int i, int j, regex k) {
		transFunction[i][j]= k;	
		cout<<"cool"<<endl;
	}
	
	void clearTransition (int i, int j){
//		transFunction[i][j] = NULL; //find a way to make this null appropriately. 
	}
	
	//function to set a final state
	void setFinalState(int i){
		if(i <= this->noOfStates){
		states[i] = 1;
		}
	}
	
	//set a function to set a non final state
	void resetFinalState(int i){
		if(i <= this->noOfStates){
			states[i] = 0;
		}
	}
	
	void setAlphabet(char* temp){
		sigma.setAlphaSymbols(temp);
	}

	
	bool isDeterministic(){
		//first find a nfa
		//epsilon 
		
		
		
		for (int i = 0 ; i < this->noOfStates; i++){
			for (int j = 0 ; i < this->noOfStates; i++){
				if(transFunction[i][j].isEmpty()){
					return false;
				}
			}
		}
		return true;
	}
	
	bool isNonDeterministic(){
		//iterate through the alphabet
		// count the out going transition, 
		firs
		for (int i = 0 ; i < this->noOfStates; i++){
			for (int j = 0 ; i < this->noOfStates; i++){
				if(!transFunction[i][j].isLeaf()){
					return false;
				}
			}
		}
		return true;
	
	}
	
};


//questions, would you want me to set a two dimensional array of regex pointers or regexes?
//should alphabet here be the alphabet class or alphabet pointer. depending on that I will decide whether.h file goes in or .cpp files goes in?
//is it possible for compilers to automatically prepare a .h file?
