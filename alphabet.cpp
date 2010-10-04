/*
 * This is alphabet.cpp
 *  
 *
 *  
 */



#include "alphabet.h"
#include <iostream>




alphabet :: alphabet(){
	alphaSymbols.reset();
	}

alphabet::alphabet (char * temp){
		for(int i = 0; temp[i]!= '\0'; i++){ 
		alphaSymbols.set(int(temp[i]));
		}
	}

bool alphabet::setAlphaSymbols (char * temp){
		for(int i = 0; temp[i]!= '\0'; i++){ 
			alphaSymbols.set(int(temp[i]));
		}
	return true;
	}	

bool alphabet::setAlphaSymbol (int my_index){
	alphaSymbols.set(my_index);
	return true;
}	

alphabet alphabet::operator * (alphabet beta){ 
		alphabet temp; 
		temp.alphaSymbols = alphaSymbols &= beta.alphaSymbols;
		return temp;
	}

alphabet alphabet:: operator + (alphabet beta){
		alphabet temp;
		temp.alphaSymbols = alphaSymbols |= beta.alphaSymbols;
		return temp;
	}


alphabet alphabet:: operator - (alphabet beta){
		alphabet temp;
		temp.alphaSymbols = alphaSymbols ^= beta.alphaSymbols;
		temp.disp();
		return temp;
	}
	
bool alphabet::isMember(int i){
	if (alphaSymbols[i])
	return true;
	else
	return false;
	}
	
bool alphabet::isMember(char i){
	if (alphaSymbols[int(i)])
	return true;
	else
	return false;
	}
	
	
void alphabet::disp () {
	for (int i = 0 ; i < alphaSymbols.size(); i++)
		cout<<alphaSymbols[i];
		cout<<endl;
	}



ostream& operator << (ostream& s, alphabet& a){
	for(int i = 0 ; i < a.alphaSymbols.size(); i++){
	if ( a.alphaSymbols[i])
	s << char(i);
	}
	return s;

}


istream& operator >> (istream& s, alphabet& a){
	
	s >> a.alphaSymbols;
	return s;

}

