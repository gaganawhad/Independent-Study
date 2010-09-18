#include <iostream>
#include "GNFA.h"


/*
int mainAlpha (){

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



int mainRegex(){
	//This program basically creates two identical trees, first manually and second by using the newly added parser. both displays are identical. 
	multiSet bhariMultiset, laiBhariMultiset;
	
	regexNode * l = new leafNode('a'); 
	regexNode * r = new leafNode('b');
	regexNode * y = new leafNode('y');
	regexNode * z = new leafNode('z');
	regexNode * p = new unionNode();
	regexNode *	q = new unionNode();
	regexNode *	s = new unionNode();
        alphabet hello;

	if (!p->isUnion())
		cout<<"yes!!!"<<endl;
	else
		cout<<"blah"<<endl;
	
	p->setLeftChild(l);
	p->setRightChild(r);
	q->setLeftChild(y);
	q->setRightChild(z);
	s->setLeftChild(p);
	s->setRightChild(q);

	
	cout<<"This is bhari"<<endl<<bhariMultiset<<endl;
	regex * reg = new regex(s);
        cout<<"this is reg: ";
	cout<<reg<<endl;
	cout<<"This is reg display:";
	reg->display();
        hello = reg->getLeaves();
        cout<<"these are the leaves in reg:"<<hello<<endl;
	cout<<endl;
	
	bhariMultiset = bhariMultiset + hello;
	cout<<endl<<"this is bhari"<<endl<<bhariMultiset<<endl;
	laiBhariMultiset = bhariMultiset + hello;
	cout<<endl<<"this is lai bhari"<<endl<<laiBhariMultiset<<endl;
	laiBhariMultiset = bhariMultiset + laiBhariMultiset;
	cout<<endl<<"this is lai bhari"<<endl<<laiBhariMultiset<<endl;
	if (reg->isUnionTree())
		cout<<"got it"<<endl;
	else
		cout<<"nope"<<endl;
	
	regex * reg1 = new regex("(c U 2)");
        cout<<"this is reg1 :";
	cout<<reg1<<endl;
        cout<<endl;
	regex * reg2 = new regex(new leafNode('7'));
        cout<<"This is reg2 :";
        cout<<reg2<<endl;
        hello = reg2->getLeaves();
        cout<<"these are the leaves in reg2:"<<hello<<endl;
	laiBhariMultiset = laiBhariMultiset + hello;
	cout<<endl<<"this is lai bhari"<<endl<<laiBhariMultiset<<endl;
	regex * reg3;
	reg3 = *reg1 + reg2;
        cout<<"this is reg3 :";
	cout<<reg3<<endl;
        hello = reg3->getLeaves();
        cout<<"these are the leaves in reg3:"<<hello<<endl;
	cout<<endl;
	laiBhariMultiset = laiBhariMultiset + hello;
	cout<<endl<<"this is lai bhari"<<endl<<laiBhariMultiset<<endl;
	reg3 = *reg1 - reg2;
        cout<<"this is reg3 :";
	cout<<reg3<<endl;
        hello = reg3->getLeaves();
        cout<<"these are the leaves in reg3:"<<hello<<endl;
	cout<<endl;
	reg3 = *(*reg1);
        cout<<"this is reg3 :";
	cout<<reg3<<endl;
      
        hello = reg3->getLeaves();
	
        cout<<"these are the leaves in reg3:"<<hello<<endl;
    laiBhariMultiset = laiBhariMultiset + hello;
	cout<<endl<<"this is lai bhari"<<endl<<laiBhariMultiset<<endl;    
	hello = reg1->getLeaves();
        cout<<"these are the leaves in reg1:"<<hello<<endl;
        cout<<hello<<endl;
	laiBhariMultiset = laiBhariMultiset + hello;
	cout<<endl<<"this is lai bhari"<<endl<<laiBhariMultiset<<endl;
	
	
	regexNode * yahoo = new leafNode(EPSILON); 
	regex * test = new regex(yahoo);
	if(test->isEmpty()){
		cout<<"yay"<<endl;
	}
	if(reg->isEmpty()){
		cout<<"yay"<<endl;
	}
	else{
		cout<<"boo"<<endl;
	}
	hello =  test->getLeaves();
	cout<<"this is it"<<hello<<endl;
	multiSet nextlaibhari;
	
	nextlaibhari = nextlaibhari + hello;
	cout<<nextlaibhari<<endl;
	
	bitset<4> mybits;
	
	cout << mybits.set() << endl;       // 1111
	cout << mybits.set(2,0) << endl;    // 1011
	cout << mybits.set(2) << endl;      // 1111
	cout << mybits.set(3,0) << endl;	// 
	
	return 0;
}



int simplifyRegex(){
	regexNode* l = new leafNode(NULLSET);
	regexNode* r = new leafNode( 'r');
	regexNode* u = new unionNode;
	regexNode* c = new concatNode;
	regexNode* s = new starNode;
	

	u->setChildren(r,l);
	u->setChildren(l,r);

	regex* reg = new regex(u);
	
	cout<<reg<<endl;

	reg->simplify();
	
	cout<<reg<<endl;
	delete reg;


	regex* reg = new regex(s);
	c->setChildren(l,r);
	s->setLeftChild(c);
	cout<<reg<<endl;
	
	
	
	delete s;
	reg->setRoot(c);
	reg->display();
	delete reg;
	
	reg = new regex ();
	l = new leafNode(NULLSET);
	r = new leafNode( 'r');
	u->setChildren(l,r);
	reg->setRoot(u);
	cout<<reg<<endl;
	reg->simplify();
	cout<<reg<<endl;
       delete reg;
	u->setChildren(l,r);
	reg->setRoot(u);
	cout<<reg<<endl;
*
	return 0;

};

int deleteRegex(){

  
  return 0;

}


int testSetRoot(){
	vector<regexNode*> funkyStack;
	regexNode *reg1 = new leafNode(NULLSET), *reg2 = new leafNode(NULLSET), *reg3 = new leafNode(NULLSET), *reg4 = new leafNode(NULLSET), *reg5 = new leafNode(NULLSET);
	//regexNode* l = new leafNode(NULLSET);
	//reg.setRoot(l);
	reg1->display();
	funkyStack.push_back(reg1);
	cout<<funkyStack.size()<<endl;
	//regexNode* r = new leafNode(NULLSET);
	//reg.setRoot(r);
	reg2->display();
	funkyStack.push_back(reg2);
	cout<<funkyStack.size()<<endl;
	//regexNode* s = new leafNode(NULLSET);
	//reg.setRoot(s);
	reg3->display();
	funkyStack.push_back(reg3);
	//regexNode* t = new leafNode(NULLSET);
	//reg.setRoot(t);
	reg4->display();
	funkyStack.push_back(reg4);
	//regexNode* u = new leafNode(NULLSET);
	//reg.setRoot(u);
	reg5->display();
	funkyStack.push_back(reg5);
	
	
	return 0;
}

int testVector(){
	vector <int> intVec;
	int i;
	for(int j =0 ; j<10; j++){
		i=2;
		intVec.push_back(i);
	
	}
	for(int j =0 ; j<10; j++){
		cout<<intVec[j]<<endl;
		
	}
	
}
*/

regexNode* newTest(){
  regexNode* l = new leafNode('c');
  regexNode* r = new leafNode('2');
  regexNode* u = new unionNode(l,r);
  regex* reg1 = new regex(u);
  return reg1->getRoot();
}

regexNode* test(){
  regexNode* l = new leafNode(NULLSET);
  regexNode* r = new leafNode('r');
  regexNode* u = new unionNode;
  regexNode* c = new concatNode;
  regexNode* s = new starNode;
  u->setChildren(l,r);
  s->setLeftChild(u);
  regex* reg = new regex(s);
  return reg->getRoot();
}

int mainGNFA(){
  GNFA a(5);
  alphabet alpha ("pqrst1234");
  
  a.setAlphabet(alpha);
  a.setAcceptState(2);
  a.setAcceptState(4);
  a.display(); 
 /* 
  for(int i = 0; i < 5; i++){ 
    for(int j = 0; j < 5; j++) {
      a.setTransition(i, j, newTest()->getRoot());
      cout<<"am here"<<endl;
      a.display();
    }
  }
*/
 
//  a.clearTransition(0,4);
  a.setTransition(0, 0, newTest());
//  a.display();
//  a.setTransition(0, 1, newTest());
  a.display();
  return 0;
}

int main (){
   return mainGNFA();
}
