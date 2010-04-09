#include "alphabet.h"
#include <iostream.h>

using namespace std;

int main (){

	alphabet a("123dex"), b("abcdef215"), c;

	cout<<a<<endl;
	a.disp();
	cout<<a<<endl;
	a.disp();
	cout<<b<<endl;
	b.disp();
	c = a - b;
	cout<<c<<endl;
	c.disp();

	if (c.isMember('a'))
	cout<< "true"<<endl;
	else
	cout<<"false"<<endl;
	
	c = a + b;
	cout<<c<<endl;
	c.disp();
	c = a * b;
	cout<<c<<endl;
	c.disp();
	
	
	// bitset<8> m, n,o;
	//m.set(1);
	//n.set(3);
	//o = m ^=n;
	//for (int i = 0 ; i < o.size(); i++)
	//	cout<<o[i];
	//	cout<<endl;
	
	return 0;
}

