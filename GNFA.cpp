/*
 *  GNFA.cpp
 *  This GNFA does not the gGNFA as described by the text. 
 *  Crudely put, it provides a way to store things that are relevant to state machines in general
 *  It does have validity tests to check if it is indeed a gNFA or NFA or DFA of the text. 
 *  Created by Gagan Awhad on 10/31/09.
 *  Copyright 2009 Unversity of Minnesota. All rights reserved.
 *
 */



#include "GNFA.h"
#include <iostream>

//This constructor creates a simple GNFA class that has states and has all possible transition functions as null set

GNFA::GNFA(int n){
  this->noOfStates = n;
  this->acceptStates.resize(noOfStates);
  
  for (int i = 0; i< noOfStates; i++){
    transVector temp;
    for (int j = 0; j< noOfStates; j++){
      //cout<<i<<j<<endl; //used for the sake of debugging
      temp.push_back(new leafNode(NULLSET));
    }	

    transFunction.push_back(temp);
  }
  
  cout<<"this is 0 4 on creation";
  transFunction[0][4]->display();
  cout<<endl;

}
	


//Take two states and regular expression and then set the transiontion function
bool GNFA::setTransition (int i, int j, regexNode* k) {
  if (i < this->noOfStates && j < this->noOfStates){
    deleteTransition(i,j);
    transFunction[i][j] = k;	
    return true;
  }
  else {
    cout<<"Either one or both of the states are not in the rage"<<endl;
    return false;
  }
}

// Here do you want to create another constructor in which the argument n the number of states and a state of functions is given?
bool GNFA::deleteTransition(int i, int j){
  delete transFunction[i][j];
  return true;
}


bool GNFA::clearTransition (int i, int j){
  delete transFunction[i][j];
  transFunction[i][j]= new leafNode(NULLSET); //find a way to make this null appropriately. 
  return true;
}
	

//function to set a final state
bool GNFA::setAcceptState(int i){
  if(i < this->noOfStates){
    acceptStates[i] = 1; 
    return true;
  }
  else {
    cout<<"State out of range. States are from State 0 to State "<<noOfStates-1<<endl;
    return false;
  }
}



//Function to check if state is an accept state
bool GNFA::isAcceptState(int i){
  if(acceptStates[i]==1){
    return true;
  }
  else{
    return false;
  }
}
	



//Function to set a State to a non final state
bool GNFA::resetAcceptState(int i){
  if(i < this->noOfStates){
    acceptStates[i] = 0;
    return true;
  }
  else {
    cout<<"State out of range. States are from State 0 to State "<<noOfStates-1<<endl;
    return false;
  }
}
	


//Function to set the Alphabet
bool GNFA::setAlphabet(char* temp){
  sigma.setAlphaSymbols(temp);
  return true;
}


bool GNFA::setAlphabet(alphabet my_alphabet){
  sigma = my_alphabet;
  return true;
}


alphabet GNFA::getAlphabet(){
  return this->sigma;
}



//This function does not do much apart from print number from 0 to n-1, n being the total number of states
void GNFA::displayStates() {
  cout<<"# States: ";
  for(int i=0; i< noOfStates; i++){
    cout<<i<<", ";
  }
  cout<<endl;
}



//Since the Start State is always State 0 this method only prints that starndard state
void GNFA::displayStartState(){
  cout<<"Start State: 0"<<endl;
}



//This function prints the list of all the accept states of the GNFA
void GNFA::displayAcceptStates(){
  cout<<"Accept States: ";
  for(int i=0; i < noOfStates; i++){
    if(acceptStates[i]){
      cout<<i<<", "; //states are numbered from 0
    }
  }
  cout<<endl;
}




//The following function displays the Alphabet
void GNFA::displayAlphabet(){
  cout<<"Alphabet: ";
  cout<<sigma<<endl;
}




//The follwoing function displays the Transition function. It gives the Start State, End State and prints the transition function. This does not display the NULL transition functions 
void GNFA::displayTransitionFunction(){
  cout<<"This is the transition function:"<<endl;
  for (int i = 0 ; i < this->noOfStates; i++){
    for (int j = 0 ; j < this->noOfStates; j++){
      if(!transFunction[i][j]->isNULL()){
        cout<< "	Start State :"<<i<<endl;
        cout<< "	End State :"<<j<<endl;
        cout<< "	Regular Expresssion :"<<transFunction[i][j]<<endl<<endl<<endl;
      }
    }
  }
}


//This function is a not very neat way to displaying the Transition Function. It shows also the NULL sets
void GNFA::forceDisplayTransitionFunction(){
  for (int i =0; i< noOfStates; i++){
    for (int j =0 ; j < noOfStates; j++){
            cout<<i<<j<<" "<<transFunction[i][j]<<endl;
    }
  }
}



//This function is used to display the complete GNFA. ie it prints the 5 attributes that define it 
void GNFA::display(){
  displayStates();
  displayStartState();	
  displayAcceptStates();
  displayAlphabet();
  displayTransitionFunction();	
}


//This function checks if the GNFA is nondeterministc. Using theory we found out that if any of the transitions is not a union tree, then it is not non-deterministic. That means it is also not deterministic
bool GNFA::isNonDeterministic(){
  for (int i = 0 ; i < this->noOfStates; i++){
    for (int j = 0 ; i < this->noOfStates; i++){
      if(!transFunction[i][j]->isUnionTree()){
        return false;
      }
    }
  }
  return true;
}


//This function checks to see if the GNFA is indeed deterministic. It does so by first checking if it is non-deterministic and if it is indeed non deterministic then it applies other rules. 
bool GNFA::isDeterministic(){
  if (this->isNonDeterministic()){
    for (int i = 0 ; i < this->noOfStates; i++){
      multiSet temp;

      for (int j = 0 ; i < this->noOfStates; i++){
        temp = temp + transFunction[i][j]->getLeaves();
      }
      
      if (temp[128]!=0){//128 is the place for epsilon. If there is an epslion, then it is not deterministic
        return false; 
      }
      
      multiSet temp1;
      temp1 = temp1 + sigma;
      
      if (not(temp1 == temp)){
              return false;
      }
      //check if all 
    }
    return true;
  }
  else {
    return false;
  }
	
}


regexNode * GNFA::toRegexp(){
  cout<<"A"<<endl;
  GNFA* fooGNFA = new GNFA(this->noOfStates + 2);
  cout<<"B"<<endl;
  fooGNFA->setAcceptState(this->noOfStates + 1);
  cout<<"C"<<endl;
  fooGNFA->setAlphabet(this->getAlphabet());
  cout<<"D"<<endl;
  fooGNFA->setTransition(0, 1, new leafNode(EPSILON));
  cout<<"E"<<endl;
  
  for(int i=0; i<noOfStates; i++){
    for(int j=0; j<noOfStates;j++){
      fooGNFA->setTransition(i+1, j+1, this->transFunction[i][j]);
    }
    if(this->isAcceptState(i)){
      fooGNFA->setTransition(i, noOfStates+1, new leafNode(EPSILON));
    }
  }

  cout<<"F"<<endl;
  cout<<"G"<<endl;
  cout<<*fooGNFA<<endl; //Used to dipsly what the GNFA looks like at the end of this. 
  cout<<"H"<<endl;

  //The Floyd Warshall algorithm begins from here 
  regexNode * result = fooGNFA->transFunction[0][noOfStates+1];
  cout<<"I"<<endl;
  result->simplify();
  cout<<"J"<<endl;
  cout<<"and result is :"<<result<<endl;
  for(int k =1; k < noOfStates + 1; k++){
    result = *result + *(*fooGNFA->transFunction[0][k] - *(*((*fooGNFA->transFunction[k][k])++) - *fooGNFA->transFunction[k][noOfStates +1]));
    cout<<"k is :"<<k<<"and result is :"<<result<<endl;
    result = result->simplify();
    cout<<"k is :"<<k<<"and result is :"<<result<<endl;
  }
  cout<<"K"<<endl;
  cout<<result<<endl;
  delete fooGNFA;
  // shoudl i do a delete this??
  return result;
	 
	//return result here after deciding if pointer should be returned or object
	
   /* carl sturtivant suggested the following method. argue with him the next time whether it is the best.  
	for(int k = 0; k < noOfStates; k++){ 
	cout<<"came here"<<endl;
		for (int i = 0; i < noOfStates; i++){
			for (int j = 0; k < noOfStates; j++){
				transFunction[i][j] = *transFunction[i][j] + *(*transFunction[i][k] - *(*(new starNode(transFunction[k][k])) - *transFunction[k][j]));
				transFunction[i][j]->simplify();
			}
			 
		}
	}
		regexNode * result = new leafNode(NULLSET);
	
	for(int k = 0; k < noOfStates; k++) {
		if (isAcceptState(k)){
			result = *result + *transFunction[0][k];
		}
				
		result->simplify();
	}
	delete this;			
	return result;
*/
			

}




/*
ostream& operator << (ostream& s, GNFA& a){
  s<<"# States: ";
  for(int i=1; i<=a.noOfStates; i++){
    s<<i<<", ";
  }
  s<<endl;

  s<<"Start State: 1"<<endl;
  s<<"Accept States: ";
  for(int i=0; i < a.noOfStates; i++){
    if(a.acceptStates[i]){
      s<<i<<", ";
    }
  }
  s<<endl;
  s<<a.sigma<<endl;
  return s;
	
}*/

// still to figure out whether i will end up using something like the one below or the one above. 
/*ostream& operator << (ostream& s, GNFA& a){
  s<<a.display();
  return s;
}
 */



/* That the following function works should be an interesting information for you. But it does not work when we want to add an endl
 eg. cout<<a<<endl the code below does though 
void operator << (ostream& s, GNFA& a){
	a.display();
}
*/


/* Another way to write the << function */
ostream& operator << (ostream& s, GNFA& a){
	a.display();
	return s;
}


/*
istream& operator >> (istream& s, GNFA& a){

	return s;
	
}
 */


