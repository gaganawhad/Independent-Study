#include "GNFA.h"
#include "iostream"

using namespace std;

regexNode * simpleRegex(){
  return new unionNode(new leafNode('c'), new leafNode('2'));
}

regexNode * unionTree(){
  regexNode * l = new leafNode('a'); 
  regexNode * r = new leafNode('b');
  regexNode * y = new leafNode('y');
  regexNode * z = new leafNode('z');
  regexNode * p = new unionNode();
  regexNode * q = new unionNode();
  regexNode * s = new unionNode();
  p->setLeftChild(l);
  p->setRightChild(r);
  q->setLeftChild(y);
  q->setRightChild(z);
  s->setLeftChild(p);
  s->setRightChild(q);
  return s;

}
void test_alphabet (){
  cout<<"**********************   Testing the Operations on Alphabet  *********************************"<<endl;
  alphabet a("123dex"), b("abcdef215"), c;

  cout<<"This is alphabet a:"<<a<<endl;
  cout<<"This is the bitset for a:";
  a.disp();
  cout<<"This is alphabet b:"<<b<<endl;
  cout<<"This is the bitset for b:";
  b.disp();
  c = a - b;
  cout<<"This is c = a - b :"<<c<<endl;
  cout<<"This is the bitset for c:";
  c.disp();

  cout<<"Is 'a' is a memeber of alpbabet c ?"<<endl;
  if (c.isMember('a'))
    cout<< "true"<<endl;
  else
    cout<<"false"<<endl;
  
  c = a + b;
  cout<<"The result of c = a + b:"<<c<<endl;
  cout<<"This is the bitset for c:";
  c.disp();
  c = a * b;
  cout<<"The result of c = a * b:"<<c<<endl;
  cout<<c<<endl;
  cout<<"This is the bitset for c:";
  c.disp();

}



void test_union_tree(){
  cout<<"**********************   Testing get_leaves, isUnionTree and  and multiSet     *********************************"<<endl;
  multiSet bhariMultiset, laiBhariMultiset;
  regexNode* s = unionTree();
  alphabet leaves;
  

  cout << "This is the regular expression we are testing for a Union Tree:"<<s<<endl;
  cout<<"Testing if it is a union tree"<<endl;

  if(s->isUnionTree())
    cout<<"The regular expression is a union tree"<<endl;
  else
    cout<<"The regular expression is **not** a union tree"<<endl;

  leaves = s->getLeaves();
  cout<<"These are the leaves in the regular expression:"<<leaves<<endl;
  cout<<endl;
  
  regexNode * t = new starNode(s);
  cout << "This is the regular expression we are testing for Union Tree:"<<t<<endl;
  cout<<"Testing if it is a union tree"<<endl;

  if(t->isUnionTree())
    cout<<"The regular expression is a union tree"<<endl;
  else
    cout<<"The regular expression is **not** a union tree"<<endl;
  
  leaves = s->getLeaves();
  cout<<"These are the leaves in the regular expression:"<<leaves<<endl;
  cout<<endl;

  cout<<"This is the Multiset"<<endl<<bhariMultiset<<endl;
  bhariMultiset = bhariMultiset + leaves; 
  cout<<endl<<"This is bhariMultiset = bhariMultiset + leaves"<<endl<<bhariMultiset<<endl; 
  laiBhariMultiset = bhariMultiset + leaves;
  cout<<endl<<"this is laiBhariMultiset = bhariMultiset + leaves"<<endl<<laiBhariMultiset<<endl;
  laiBhariMultiset = bhariMultiset + laiBhariMultiset;
  cout<<endl<<"this is laiBhariMultiset = bhariMultiset + laiBhariMultiset"<<endl<<laiBhariMultiset<<endl;
}


void test_individual_simplify_rules(){
  regexNode * test = new starNode(new leafNode(NULLSET)); 

  cout<< "Testing rule  NULLSET * = {EPSILON} "<<endl;
  cout<< "Regexp before simplification: "<<test<<endl;
  test = test->simplify();
  cout<< "Regexp after simplification: "<<test<<endl;
  delete test;

  test = new unionNode(new leafNode(NULLSET),simpleRegex());
  cout<< "Testing rule  NULLSET U R = R "<<endl;
  cout<< "Regexp before simplification: "<<test<<endl;
  test = test->simplify();
  cout<< "Regexp after simplification: "<<test<<endl;
  delete test;
  
  test = new concatNode(new leafNode(NULLSET),simpleRegex());
  cout<< "Testing rule  NULLSET . R = R "<<endl;
  cout<< "Regexp before simplification: "<<test<<endl;
  test = test->simplify();
  cout<< "Regexp after simplification: "<<test<<endl;
  delete test;
  
  test = new concatNode(new leafNode(EPSILON),simpleRegex());
  cout<< "Testing rule  EPSILON . R = R "<<endl;
  cout<< "Regexp before simplification: "<<test<<endl;
  test = test->simplify();
  cout<< "Regexp after simplification: "<<test<<endl;
  delete test;
  
  test = new concatNode(new leafNode(EPSILON),new leafNode(NULLSET));
  cout<< "Testing rule  EPSILON . NULLSET = NULLSET "<<endl;
  cout<< "Regexp before simplification: "<<test<<endl;
  test = test->simplify();
  cout<< "Regexp after simplification: "<<test<<endl;
  delete test;
  
  
}



void complicated_simplify(){
  cout<<"******   Testing the simplify function for a complicated for a nested simplification    ******"<<endl;
  regexNode * s = new leafNode('s');
  regexNode * t = new leafNode('t');
  regexNode * u = new unionNode(s,t);
  regexNode * n = new leafNode(NULLSET);
  regexNode * c = new concatNode(u, n);
  regexNode * v = new leafNode('v');
  regexNode * u1 = new unionNode(c,v);
  cout << "This is the regexp before simplification:"<<u1 << endl;
  u1 = u1->simplify();
  cout << "This is the regexp after simplification"<<u1 << endl;

}


void test_replicate(){
  cout<<"*************************** Testing the replicate function *********************************"<<endl;
  regexNode * one = new unionNode(new leafNode(NULLSET), new concatNode(new leafNode(NULLSET), new concatNode(new starNode(new leafNode(NULLSET)), new leafNode(NULLSET))));
  regexNode * two = one->replicate();
  cout <<"The first regular expression is"<< one << endl;
  cout <<"The replicated regular expression"<< two << endl;
  one = one->simplify();
  cout <<"First Regular expression after simplification:"<< one << endl;
  cout <<"Second regular expression remains as it is, showing that it is independent:"<< two << endl;
  
}

void GNFA_to_regexp(){
  cout<<"*********************   Testing the conversion of a GNFA to regexp    *************************"<<endl;
  GNFA a(2);
  regexNode* u = simpleRegex(); 
  a.setTransition(0, 1, u);
  a.setAcceptState(1);
  regexNode * b = a.toRegexp();
  cout<<"This is the regular expression result :"<<b<<endl;
}


int main (){
  cout<<"********************************************************************************************"<<endl;
  test_alphabet();
  cout<<"********************************************************************************************"<<endl;
  test_union_tree();
  cout<<"********************************************************************************************"<<endl;
  test_individual_simplify_rules();
  cout<<"********************************************************************************************"<<endl;
  complicated_simplify();
  cout<<"********************************************************************************************"<<endl;
  test_replicate();
  cout<<"********************************************************************************************"<<endl;
  GNFA_to_regexp();
  cout<<"********************************************************************************************"<<endl;
  return 1;

}

