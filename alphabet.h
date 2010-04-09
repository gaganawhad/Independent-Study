/*
 *
 *  This is alphabet.h
 *  
 *
 *  
 */

#ifndef ALPHABET_H
#define ALPHABET_H

#include <bitset>
#define ALPHABET_LIMIT = 128

using namespace std;

class alphabet{
	private:  
          bitset<129> alphaSymbols; //there is some sort of an assumption that there will be 128 characters only 
		//the last bitset is reserved for epsilons
		// this display for the bitset is as you would read a binay number. setting 128 will end up setting the msb and will be seen first in the array. 
	public:
	alphabet();
	alphabet (char * );		
	bool setAlphaSymbols (char * );
	bool setAlphaSymbol (int );
	alphabet operator + (alphabet );


	alphabet operator * (alphabet );


	alphabet operator - (alphabet );
	
	bool isMember(int );
	
	bool isMember(char );
	
	
	void disp ();
	
	friend ostream& operator << (ostream& , alphabet& );
	friend istream& operator >> (istream& , alphabet& );


};


ostream& operator << (ostream& , alphabet& );


istream& operator >> (istream& , alphabet& );

#endif
