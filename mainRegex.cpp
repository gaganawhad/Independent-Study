#include <iostream>
#include "GNFA.h"

using namespace std;


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