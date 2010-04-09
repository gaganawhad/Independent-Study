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

	bool isUnionTree(){
		return false;
	}
	
	char regexNode::getSymbol(){
		return 'O';
	}

	regexNode* getLeftChild(){
		return 0;
	}

	bool setLeftChild(regexNode*){
		return 0;
	}
	
	bool getRightChild(){
		return 0;
	}

	bool setRightChild(regex *){
		return 0;
	}







  regexNode * unaryRegexNode::getLeftChild(){
    return this->leftChild;
  }

	bool unaryRegexNode::setLeftChild(regexNode* newLeftChild){
		leftChild = newLeftChild;
		return true;
	}
	






  regexNode * binaryRegexNode::getRightChild(){
    return this->rightChild;
  }

	bool binaryRegexNode::	setRightChild(regexNode* newRightChild){
		rightChild = newRightChild;
		return true;
	}







  leafNode::leafNode(){
		this->symbol = NULL;
  }

  leafNode::leafNode(char symbol){
    this->symbol = symbol;
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
  
  bool leafNode::isLeaf(){
    return true;
  }

	
  bool leafNode::isUnionTree(){
    return true;
  }
		
/*	
	void leafNode::simplify(regexNode *p, char child){
		return;
	}
	
	virtual void leafNode::simplify( regex * p) {}*/
	
	
	
  regexNode* leafNode::simplify(){ //leaf nodes cannot be simplified more.
    return this;
  }
		
  char leafNode::getSymbol(){
    return symbol;
  }
	
	/* still to look into this section to figure why i did the following in this class */
  /*virtual void leafNode::setLeftChild(regexNode *) {}
  virtual void leafNode::setRightChild(regexNode *) {}
  virtual regexNode * leafNode::getLeftChild() {}
  virtual regexNode * leafNode::getRightChild() {}*/
/*
  bool leafNode::setLeftChild(regexNode *) {
    return false;
  }
  bool leafNode::setRightChild(regexNode *){
    return false;
  }
 
 */
/*
  regexNode * leafNode::getLeftChild(){
    return this->leftChild;
  }
  regexNode * leafNode::getRightChild(){
    return this->rightChild;
  }
*/
  
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
	


  starNode::starNode(){}
	
  starNode::starNode (regexNode *leftChild){
    this->leftChild = leftChild;
  }
	
/*  bool starNode::setLeftChild(regexNode *leftChild){
    this->leftChild = leftChild;
    return true;
  }
*/
	
  regexNode * starNode::getLeftChild(){
    return leftChild;
  }
	
  void starNode::display(){
    cout<<"(";
    leftChild->display();
    cout<<")*";
  }

/*
  bool starNode::isLeaf(){
    return false;
  }
 */
  
  bool starNode::isUnionTree(){
    return false;
  }

	
  bool starNode::isStar(){
    return true;
  }
	


	
/*	void starNode::simplify(regexNode *p, char whichChild){
		return;
	}
	
	virtual void starNode::simplify( regex * p) {}
*/
/*
bool starNode::setRightChild(regexNode * rightChild){
  this->rightChild = NULL;
  return false;

}
*/	
  regexNode* starNode::simplify(){ // still not worked on simplification rules on start node. 
    return this;
  }

  alphabet starNode::getLeaves(){
    return leftChild->getLeaves();
  }




  unionNode::unionNode(){}
	
  unionNode::unionNode( regexNode * leftChild, regexNode * rightChild){
    this->leftChild = leftChild;
    this->rightChild = rightChild;
  }
	
/*	
  bool unionNode::setRightChild(regexNode* rightChild){
    this->rightChild = rightChild;
  }
*/

  regexNode * unionNode::getRightChild(){
    return rightChild;
  }
	

  void unionNode::display(){
    cout<<"(";
    leftChild->display();
    cout<<"U";
    rightChild->display();
    cout<<")";
  }
	
	
	// is leaf is not required because it is inherited. 
	
/*	
  bool unionNode::isStar(){ 
    return false;
  }
*/
  bool unionNode::isUnion(){
    return true;
  }
	
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
	
			
  regexNode* unionNode::simplify(){
    leftChild = leftChild->simplify();
    rightChild = rightChild->simplify();
      if(leftChild->isLeaf() && rightChild->isLeaf()){
        if (leftChild->getSymbol() == NULLSET){ // due to this the parent of this node gets the right child as its node, and left child and this node itslef is deleted. 
          regexNode* temp = rightChild;
          delete leftChild;
          delete this;
          return temp;
        }
		// other rules will come in here.  Think about possible datastrcuture like a look up table to be used here to make simplification easy. 
      }
		

   }
	
/*	 This is the older version of the simplify function which was not as graceful


void unionNode::simplify(regexNode * p){
  leftChild->simplify(this, 'l');
  rightChild->simplify(this, 'r');
  if(leftChild->isLeaf() && rightChild->isLeaf()){
    if (leftChild->getSymbol() == NULLSET){
      regexNode* temp;
      temp = p;
      p =rightChild;
      delete leftChild;
      delete temp;
      
    }	
  }
}

*/

  alphabet unionNode::getLeaves(){
    return leftChild->getLeaves() + rightChild->getLeaves();
  }




  concatNode::concatNode(){}
	
  concatNode::concatNode(regexNode * leftChild, regexNode * rightChild){// constructor for opNode
    this->leftChild = leftChild;
    this->rightChild = rightChild;
  }
	
  void concatNode::setRightChild(regexNode* rightChild){
    this->rightChild = rightChild;
  }

  regexNode * concatNode::getRightChild(){
    return rightChild;
  }
	

  void concatNode::display(){
    cout<<"(";
    leftChild->display();
    cout<<".";
    rightChild->display();
    cout<<")";
  }
	
/*	
  bool concatNode::isStar(){ 
    return false;
  }
*/	
  bool concatNode::isConcat(){
    return true;
  }
	
  bool concatNode::isUnionTree(){
    return false;
  }
	
/*	

void simplify(regexNode * p, char whichChild ){
  leftChild->simplify(this, 'l');
  rightChild->simplify(this, 'r');
  if(leftChild->isLeaf() && rightChild->isLeaf()){
    if (leftChild->getSymbol() == NULLSET){
      regexNode* temp;
      if (whichChild =='l'){
        temp = p->getLeftChild();
        p->setLeftChild(rightChild);
        delete leftChild;
        delete temp;
      }
    }
  }
}
virtual void simplify( regex * p) {}

*/


  regexNode* concatNode::simplify(){  //not worked on simplification rules of this yet. 
    return this;
  }
        

  alphabet concatNode::getLeaves(){
    return leftChild->getLeaves() + rightChild->getLeaves();
  }








  regex::regex (){
    this->root = NULL;
  }
 
  regex::regex (regexNode * root){	
    this->root = root;
  }

  regex::regex (const char* s){	// This is the simplest version of the parser. It NEEDs input to be given in brackets... even the outermost level
    regexStack opeStack;
    regexStack treePtrs;
      for(int i=0; s[i]!='\0'; i++){
			
/*
switch (s[i]) {
  case ' ':
          break;
  case '(':
          break;
  case 'r': //Still to add the functionality for it to check whether it is a valid alphabet. 
          treePtrs.push(new leafNode(s[i])); 
          break;
  case 'U':
          opeStack.push(new unionNode());
          break;
  case '.':
          opeStack.push(new concatNode());
          break;
  case '*':
          opeStack.push(new starNode());
          break;
  case ')':
          regexNode* temp = opeStack.pop(); 
          if (!temp->isStar()){
                  temp->setRightChild(treePtrs.pop());
                  temp->setLeftChild(treePtrs.pop());
          }
          else if (temp->isStar()){
                  temp->setLeftChild(treePtrs.pop());
          }
          treePtrs.push(temp);
          break;
  default:
          cout<<"there is some error"<<endl;
          break;
}
*/
			
      if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')) {
        treePtrs.push(new leafNode(s[i])); 
	break;
      }
      else{
        switch (s[i]) {
          case ' ':
            break;
          case '(':
            break;
          case 'U':
            opeStack.push(new unionNode());
            break;
          case '.':
            opeStack.push(new concatNode());
            break;
          case '*':
            opeStack.push(new starNode());
            break;
          case ')':
            regexNode* temp = opeStack.pop(); 
            
            if (!temp->isStar()){
              temp->setRightChild(treePtrs.pop());
              temp->setLeftChild(treePtrs.pop());
            }
            
            else if (temp->isStar()){
              temp->setLeftChild(treePtrs.pop());
            }
            treePtrs.push(temp);
            break;
          default:
            cout<<"there is some error"<<endl;
            break;
         }
        }
       }
       root = treePtrs.pop(); //this is because this will be the child of a higher level 
      }
		

  bool regex::isNULL(){
    if (root->isLeaf() && root->getSymbol() == NULLSET){
      return true;
  }
  else {
    return false;
  }
 }
	
  bool regex::isEmpty(){
    if (root->isLeaf() && root->getSymbol() == EPSILON){
      return true;
    }
    else {
      return false;
    }
  }
	
	
  bool regex::isLeaf(){
    if (root->isLeaf() ){
      return true;
    }
    else {
      return false;
   }
  }
	
  bool regex::isUnionTree(){
    return root->isUnionTree();
  }

  void regex::simplify(){
    root = root->simplify();//
  }
	
  void regex::display(){
    root->display();
  }
	
  void regex::setRoot (regexNode * root){
    this->root = root;
  }
	
  regexNode * regex::getRoot(){
    return this->root;
  }
	
  alphabet regex::getLeaves(){
    return root->getLeaves();
  }
  
  regex * regex::operator + (regex * b){
    regexNode * temp1 = new unionNode (this->root, b->root);
    regex * temp = new regex(temp1);
    return temp;
  }
	
  regex * regex::operator * (){
    regexNode * temp1 = new starNode(this->root);
    regex * temp = new regex (temp1);
    return temp;
  }
	
  regex * regex::operator - (regex * b){
    regexNode * temp1 = new concatNode (this->root, b->root);
    regex * temp = new regex (temp1);
    return temp;
  }
	
	

//friend istream& operator >> (istream& s, regex& a);


/*

  void simplify(){};

  void display(){};

  void setRoot (regexNode * root){};



*/







ostream& operator << (ostream& s, regex* a){
	a->display();
	return s;
}

ostream& operator << (ostream& s, regex& a){
	a.display();
	return s;
}

/*
istream& operator >> (istream& s, regex& a){
	
  s >> a.alpha;
  return s;

}
 */





