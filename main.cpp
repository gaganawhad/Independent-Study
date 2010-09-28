#include "GNFA.h"
#include "iostream"

using namespace std;

regexNode* newTest(){
	regexNode* l = new leafNode('c');
	regexNode* r = new leafNode('2');
	regexNode* u ;
	u = *l + *r;
	return u;
}

regexNode* test(){
	regexNode* l = new leafNode(NULLSET);
	regexNode* r = new leafNode('r');
	
	regexNode* u; 
	regexNode* c;
	regexNode* s; 
	u = *l + *r ;
	s = new starNode(u);
	return s;
	 
}


int testRegex(){
	regexNode * r = new leafNode(NULLSET);
	regexNode * s = new leafNode('s');
	regexNode * t = new leafNode('t');
	regexNode *q;
	cout<<"this is r :"<<r<<endl;
	cout<<"this is s :"<<s<<endl;
	q = *r + *s;
	cout<<"this is q :"<<q<<endl;
	q = *q + *t;
	cout<<"this is q :"<<q<<endl;
	q->simplify();
	cout<<"this is q after simiplify"<<q<<endl;
	q = (*q)++;
	cout<<"this is q after star"<<q<<endl;
	return 0;
}

int testGNFA(){
	GNFA a(4);
	for (int i =0; i< 4; i++){
		for (int j =0 ; j < 4; j++){
			cout<<i<<j<<" "<<a.transFunction[i][j]<<endl;
		}
	}
	//for (int i =0; i< 4; i++){
	//	for (int j =0 ; j < 4; j++){
	//		cout<<i<<j<<endl;
/*cantuse deleteTRansition anymore			a.deleteTransition(0,4); */
	//	}
	//}
	
	//for (int i =0; i< 4; i++){
	//	for (int j =0 ; j < 4; j++){
			a.setTransition(0, 4, newTest());
	//	}
	//}
	
	a.setAcceptState(1);
	
	
	cout<<a<<endl;
	
	for (int i =0; i< 4; i++){
		for (int j =0 ; j < 4; j++){
			cout<<i<<j<<" "<<a.transFunction[i][j]<<endl;
		}
	}
	regexNode* r = a.toRegexp();
	cout<<"This is r:"<<r<<endl;
	return 0;
}

int codeJamTest(){
  regexNode * l = new leafNode(NULLSET);
  regexNode* s = new starNode(l); 
  cout<<s<<endl;
  s->simplify();
  cout<<s<<endl;
  delete s;
  return 1;
}




//--------------------------------------------------
// int main (){
// //  return testGNFA();
//   return codeJamTest();
// 
// }
//-------------------------------------------------- 

