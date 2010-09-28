/*
 *  regex.cpp
 *  
 *
 *  Created by Gagan Awhad on 4/6/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 *
 * 4th July, added the elementary parser
 * 31st august, converting the parser form case statement to an ifelse type statement. 
 * 20 nov, added the no argument constructor to regex because it is being used as a vector in GNFA
 * 17 feb added code for unionTree
 *
 */
 
/* this version basically is different from the earlier in that
the classes inherit from each other rather than all inheriting from
a regex node

The display() function has been modified to display more asthetically
The simplify() function in this version is a much better design.  
all simplify functions lower starting from the root will return a pointer to a tree that is simplifed from the node it is called at
it tires to implement the simple rule,  null set U 'r' = r
*/



#include <iostream>
#include <sstream>
#include <string>
#include "regex.h"
#include "stack.h"


bool regexNode::isLeaf(){
  return false;
}

bool regexNode::isStar(){
  return false;
}

bool regexNode::isUnion(){
  return false;
}

bool regexNode::isConcat(){
  return false;
}

bool regexNode::isUnionTree(){
  return false;
}
      
bool regexNode::isNULL(){
  if (this->isLeaf() && this->getSymbol() == NULLSET){
    return true;
  }
  else {
    return false;
  }
}
      
bool regexNode::isEmpty(){
  if (this->isLeaf() && this->getSymbol() == EPSILON){
    return true;
  }
  else {
    return false;
  }
}

bool regexNode::setLeftChild(regexNode*){
  return 0;
}

regexNode* regexNode::getLeftChild(){
  return 0;
}


bool regexNode::setRightChild(regexNode*){
  return 0;
}

regexNode* regexNode::getRightChild(){
  return 0;
}

bool regexNode::setChildren(regexNode* , regexNode*){
  return 0;
}

char regexNode::getSymbol(){
  return '0';
}


void regexNode::type(){
  cout<<"Type is: regexNode"<<endl;
}


regexNode * regexNode::operator + (regexNode&  b){
  regexNode * temp = new unionNode (this, &b);
  return temp;
}
      
regexNode* regexNode::operator ++ (int){
  regexNode * temp = new starNode(this);
  return temp;
}
      
regexNode * regexNode::operator - (regexNode& b){
  regexNode * temp = new concatNode (this, &b);
  return temp;
}

regexNode::~regexNode(){
  cout<<"destructor of regexNode called"<<endl;
}









/*********************** Unary Regex-Node **************************/
bool unaryRegexNode::setLeftChild(regexNode* newLeftChild){
  delete leftChild;
  leftChild = newLeftChild;
  return true;
}

regexNode * unaryRegexNode::getLeftChild(){
  return this->leftChild;
}

alphabet unaryRegexNode::getLeaves(){
  return leftChild->getLeaves();
}


void unaryRegexNode::type(){
  cout<<"Type is: unaryRegexNode"<<endl;
}

unaryRegexNode::~unaryRegexNode(){
  delete leftChild;
}



// void unaryRegexNode::delTree(){
//   leftChild->delTree();
// }







/*********************** Binary Regex-Node **************************/

bool binaryRegexNode::setRightChild(regexNode* newRightChild){
  delete rightChild;
  rightChild = newRightChild;
  return true;
}

regexNode * binaryRegexNode::getRightChild(){
  return this->rightChild;
}

bool binaryRegexNode::setChildren(regexNode* newLeftChild, regexNode* newRightChild){
  delete leftChild;
  this->leftChild = newLeftChild;
  delete rightChild;
  this->rightChild = newRightChild;
  return true;
}

alphabet binaryRegexNode::getLeaves(){
  return leftChild->getLeaves() + rightChild->getLeaves();
}


void binaryRegexNode::type(){
  cout<<"Type is: binaryRegexNode"<<endl;
}


binaryRegexNode::~binaryRegexNode(){
  delete leftChild;
  delete rightChild;
}

/*********************** Leaf Node **************************/
leafNode::leafNode(){
  this->symbol = '0';
}

leafNode::leafNode(char symbol){
  this->symbol = symbol;
}
        
bool leafNode::isLeaf(){
  return true;
}

bool leafNode::isUnionTree(){
  return true;
}


char leafNode::getSymbol(){
  return symbol;
}

//does not do anything in the case that it is a NULLSET as of now. 
alphabet leafNode::getLeaves() {
  alphabet leaf;
  if(symbol == EPSILON){
    leaf.setAlphaSymbol(128);// this corresponds to 
  }
  else {
    leaf.setAlphaSymbols(&symbol);  
  }

  return leaf;
}	

void leafNode::display(){
  if (symbol == NULLSET){
    cout<<" NullSet ";
  }
  else if (symbol == EPSILON){
    cout<<" Epsilon ";
  }
  else{
    cout<<" "<<symbol<<" ";
  }

}

void leafNode::type(){
  cout<<"Type is: leafNode"<<endl;
}


regexNode* leafNode::simplify(){ //leaf nodes cannot be simplified more.
//  this->type();
  return this;
}




      
      

/*********************** Star Node **************************/
starNode::starNode(){
  this->leftChild = new leafNode(NULLSET);
}

starNode::starNode(regexNode *newleftChild){
}


bool starNode::isStar(){
  return true;
}

void starNode::display(){
  cout<<" (";
  leftChild->display();
  cout<<")* ";
}

      
void starNode::type(){
  cout<<"Type is: starRegexNode"<<endl;
}
      
      


regexNode* starNode::simplify(){
//  this->type();
  leftChild = leftChild->simplify();
  if(leftChild->isLeaf()){
  /* NULLSET * = {EPSILON} */
    if (leftChild->getSymbol() == NULLSET){  
      regexNode* temp = new leafNode(EPSILON);
      delete this;
      return temp;
    }
  }
  return this;
}



/*********************** Union Node **************************/
unionNode::unionNode(){
    cout<<"I am in unionRegexNode first constructor"<<endl;
  this->leftChild = new leafNode(NULLSET);
  this->rightChild = new leafNode(NULLSET);
}

unionNode::unionNode( regexNode * leftChild, regexNode * rightChild){
  cout<<"I am in unionRegexNode second constructor"<<endl;
  this->leftChild = leftChild;
  this->rightChild = rightChild;
}

bool unionNode::isUnion(){
  return true;
}


/*simplify this, you wil need only one if condition */
bool unionNode::isUnionTree(){
  if(this->isUnion()){
    if (leftChild->isUnionTree()){
      if (rightChild->isUnionTree()){
        return true;
      }
    }
  }
  else{
    return false;
  }
}

void unionNode::display(){
  cout<<" (";
  leftChild->display();
  cout<<"U";
  rightChild->display();
  cout<<") ";
}


void unionNode::type(){
  cout<<"Type is: unionNode"<<endl;
}

regexNode* unionNode::simplify(){
//  this->type();
  leftChild = leftChild->simplify();
  rightChild = rightChild->simplify();
    /* NULLSET U R = R  */
    if (leftChild->isLeaf()) {
      if(leftChild->getSymbol() == NULLSET){ 
        regexNode* temp = rightChild;//becaue rightChild will no longer exist after deleting this
        rightChild = 0;
        delete this;
        return temp;
      }
    }
    /* R U NULLSET = R  */  
    if (rightChild=>isleaf()){
      if (rightChild->getSymbol() == NULLSET){ 
        regexNode* temp = leftChild;
        leftChild = 0;
        delete this;
        return temp;
      }
    }
                
  
  return this;

}
      





/*********************** Concatination Node **************************/

concatNode::concatNode(){
  this->leftChild = new leafNode(NULLSET);
  this->rightChild = new leafNode(NULLSET);
}

concatNode::concatNode(regexNode * leftChild, regexNode * rightChild){
  this->leftChild = leftChild;
  this->rightChild = rightChild;
}

bool concatNode::isConcat(){
  return true;
}


void concatNode::display(){
  cout<<" (";
  leftChild->display();
  cout<<".";
  rightChild->display();
  cout<<") ";
}
      

void concatNode::type(){
  cout<<"Type is: concatNode"<<endl;
}

regexNode* concatNode::simplify(){   
//  this->type();
  leftChild = leftChild->simplify();
  rightChild = rightChild->simplify();
    /*NULLSET . R = NULLSET  */
    if (leftChild->getSymbol() == NULLSET){  
      regexNode* temp = leftChild;
      leftChild = new leafNode(NULLSET);
      delete this;
      return temp;
    }
                
    /* R . NULLSET = NULLSET */
    else if (rightChild->getSymbol() == NULLSET){ 
      regexNode* temp = rightChild;
      rightChild = new leafNode(NULLSET);
      delete this;
      return temp;
    }
                
    /* EPSILON . R = R */
    else if (leftChild->getSymbol() == EPSILON){
      regexNode* temp = rightChild;
      rightChild = new leafNode(NULLSET);
      delete this;
      return temp;
    }
                
    /* R . EPSLION = R */
    else if (rightChild->getSymbol() == EPSILON){  
      regexNode* temp = leftChild;
      leftChild = new leafNode(NULLSET);
      delete this;
      return temp;
    }
  
  return this;
}
      

ostream& operator << (ostream& s, regexNode* a){
  a->display();
  return s;
}

ostream& operator << (ostream& s, regexNode& a){
  a.display();
  return s;
}

/*
istream& operator >> (istream& s, regex& a){
      
s >> a.alpha;
return s;

}
*/





