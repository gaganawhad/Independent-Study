
int main(){
	//This program basically creates two identical trees, first manually and second by using the newly added parser. both displays are identical. 
	
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


	regex * reg = new regex(s);
        cout<<"this is reg: ";
	reg->display();
        hello = reg->getLeaves();
        cout<<"these are the leaves in reg:"<<hello<<endl;
	cout<<endl;
	if (reg->isUnionTree())
		cout<<"got it"<<endl;
	else
		cout<<"nope"<<endl;
	
	regex * reg1 = new regex("(c U 2)");
        cout<<"this is reg1 :";
	reg1->display();
        cout<<endl;
	regex * reg2 = new regex(new leafNode('7'));
        cout<<"This is reg2 :";
        reg2->display();
        hello = reg2->getLeaves();
        cout<<"these are the leaves in reg2:"<<hello<<endl;
	regex * reg3;
	reg3 = *reg1 + reg2;
        cout<<"this is reg3 :";
	reg3->display();
        hello = reg3->getLeaves();
        cout<<"these are the leaves in reg3:"<<hello<<endl;
	cout<<endl;
	reg3 = *reg1 - reg2;
        cout<<"this is reg3 :";
	reg3->display();
        hello = reg3->getLeaves();
        cout<<"these are the leaves in reg3:"<<hello<<endl;
	cout<<endl;
	reg3 = *(*reg1);
        cout<<"this is reg3 :";
	reg3->display();
      
        hello = reg3->getLeaves();
        cout<<"these are the leaves in reg3:"<<hello<<endl;
        hello = reg1->getLeaves();
        cout<<"these are the leaves in reg1:"<<hello<<endl;
        cout<<hello<<endl;
	
	
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
	return 0;
}
