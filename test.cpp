/*
 *  test.cpp
 *  
 *	I have created this file to test some issues realted to inheritance and virtual functions 
 *
 *  Created by Gagan Awhad on 4/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>

using namespace std;


class a{
public:
	virtual int geti();
};

class b: public a{
public:
	int geti(){
	return 1;
	}
};

class c: public a{
public:
	virtual int geti() =0;
};

int main(){
	a* j = new b;
	a* k = new c;
	//cout<<k->geti();
	return 0;
}