#include <iostream>
#include <sstream>
#include <string>
#include "multiset.h"

  // basic constructor

multiSet::multiSet(){
    for(int i = 0; i < 129; i++){
      count_array[i] = 0;
    }
  }
  

  //constructor that uses a string
  multiSet::multiSet(char *str){
    for( int i = 0; str[i]!= '\0'; i++){
      count_array[int(str[i])]++;
    }
  }

  multiSet::multiSet(alphabet * my_alphabet){
    for( int i = 0; i< 129 ; i++){
      if(my_alphabet->isMember(i)){
          count_array[i]++;
      }
    }

  }

	bool multiSet::reset(){
		for(int i = 0; i < 129; i++){
			count_array[i] =0;
		}
		return true;
	}
	
	void multiSet::display(){
		for( int i = 0; i < 129; i++){
			cout<<count_array[i];
		}
	}

  int& multiSet::operator [](char c){ // int& so that it returns a reference and does not create a new int. 
    return count_array[int(c)];
  }

  multiSet multiSet:: operator + (alphabet my_alphabet){
		multiSet temp;
	  for( int i = 0; i < 129 ; i++){
		  if(my_alphabet.isMember(i)){
			  temp.count_array[i] = this->count_array[i] + 1 ;
			 // cout << temp.count_array[i]<<endl;
		  }
		  else{
			  temp.count_array[i] =  this->count_array[i];
			  // cout<< temp.count_array[i]<<endl;
		  }
	  }
	return temp;
  }
  
  multiSet multiSet:: operator + (multiSet my_multiSet){
	multiSet temp;
	for( int i = 0; i < 129 ; i++){
		temp.count_array[i] = this->count_array[i] + my_multiSet.count_array[i] ;
	}
	return temp;
}
	
bool multiSet:: operator == (multiSet my_multiSet){
	for( int i = 0; i < 129 ; i++){
		if(this->count_array[i] != my_multiSet.count_array[i]){
			return false;
		}
	}
	return true;
	
}



ostream& operator << (ostream& s, multiSet& a){
	for(int i = 0 ; i < 129; i++){
			s << a.count_array[i];
	}
	s<<endl;
	return s;
	
}

/* Still to confirm the useage of this function. Currently it is not being used, becuase of some confusion on my part
 with regards to its appropriate usages. 
istream& operator >> (istream& s, multiSet& a){
//	for (int i =0; i < 128; i++){
	s >> a.count_array[i];
//	}
	return s;// does this return s or a? plese to be checking and confirming. 
	
}

*/