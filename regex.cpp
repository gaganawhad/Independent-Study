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
	
	char regexNode::getSymbol(){
		return '0';
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
	bool regexNode::cascadeDel(){
		return false;
	}
	
	void regexNode::type(){
		cout<<"Type is: regexNode"<<endl;
	}

        regexNode::~regexNode(){}




	/*********************** Unary Regex-Node **************************/
	bool unaryRegexNode::setLeftChild(regexNode* newLeftChild){
		leftChild->cascadeDel();
		leftChild = newLeftChild;
		return true;
	}

	regexNode * unaryRegexNode::getLeftChild(){
		return this->leftChild;
	}

	alphabet unaryRegexNode::getLeaves(){
		return leftChild->getLeaves();
	}

       // void unaryRegexNode::delTree(){
       //   leftChild->delTree();
       // }

        bool unaryRegexNode::cascadeDel(){
          if( leftChild != 0){
				delete leftChild;
			}
			delete this;
			return true;
        }

	void unaryRegexNode::type(){
		cout<<"Type is: unaryRegexNode"<<endl;
	}

	/*********************** Binary Regex-Node **************************/
  
	bool binaryRegexNode::setRightChild(regexNode* newRightChild){
		rightChild->cascadeDel();
		rightChild = newRightChild;
		return true;
	}
	
	regexNode * binaryRegexNode::getRightChild(){
		return this->rightChild;
	}

	alphabet binaryRegexNode::getLeaves(){
		return leftChild->getLeaves() + rightChild->getLeaves();
	}

	bool binaryRegexNode::setChildren(regexNode* newLeftChild, regexNode* newRightChild){
		leftChild->cascadeDel();
		rightChild->cascadeDel();
		this->leftChild = newLeftChild;
		this->rightChild = newRightChild;
		return true;
	}

	bool binaryRegexNode::cascadeDel(){
		if (rightChild != 0){
			delete rightChild;
		}
		if (leftChild != 0){
			delete leftChild;
		}	
		delete this;
		return true;
	}

	void binaryRegexNode::type(){
		cout<<"Type is: binaryRegexNode"<<endl;
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


	regexNode* leafNode::simplify(){ //leaf nodes cannot be simplified more.
		this->type();
		return this;

	}
	
	bool leafNode::cascadeDel(){
		delete this;
		return true;
	}

	void leafNode::type(){
		cout<<"Type is: leafNode"<<endl;
	}
 

	
	

	/*********************** Star Node **************************/
	starNode::starNode(){
		this->leftChild = new leafNode(NULLSET);
	}
	
	starNode::starNode (regexNode *newleftChild){
		this->leftChild = newleftChild;
	}
	
	
	bool starNode::isStar(){
		return true;
	}

	void starNode::display(){
		cout<<" (";
		leftChild->display();
		cout<<")* ";
	}

	
	
	


  regexNode* starNode::simplify(){
	  this->type();
	  leftChild = leftChild->simplify();
	  if(leftChild->isLeaf()){
		  
		  /* NULLSET * = {EPSILON} */
		  if (leftChild->getSymbol() == NULLSET){  
			  regexNode* temp = new leafNode(EPSILON);
			  delete leftChild; //not required because deleting this (on next line) will delete rightchild
			  delete this;
			  return temp;
		  }
	  }
	  return this;
  }

	void starNode::type(){
		cout<<"Type is: starRegexNode"<<endl;
	}


	/*********************** Union Node **************************/
	unionNode::unionNode(){
		this->leftChild = new leafNode(NULLSET);
		this->rightChild = new leafNode(NULLSET);;	
	}
	
	unionNode::unionNode( regexNode * leftChild, regexNode * rightChild){
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




	
	
	
	
			
  regexNode* unionNode::simplify(){
	  this->type();
    leftChild = leftChild->simplify();
    rightChild = rightChild->simplify();
      if(leftChild->isLeaf() && rightChild->isLeaf()){
		  
		  /* NULLSET U R = R  */
        if (leftChild->getSymbol() == NULLSET){ 
          regexNode* temp = rightChild;//becaue rightChild will no longer exist after deleting this
          delete leftChild; //not required because deleting this (on next line) will delete rightchild
          delete this;
          return temp;
        }
		  
		/* R U NULLSET = R  */  
		else if (rightChild->getSymbol() == NULLSET){ 
			  regexNode* temp = leftChild;
			  delete rightChild;//not required because deleting this (on next line) will delete rightchild
			  delete this;
			  return temp;
		  }
		  
      }
	  return this;	

   }
	

	void unionNode::type(){
		cout<<"Type is: unionNode"<<endl;
	}




	/*********************** Concatination Node **************************/

	concatNode::concatNode(){
		this->leftChild = new leafNode(NULLSET);;
		this->rightChild = new leafNode(NULLSET);;
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
	


  regexNode* concatNode::simplify(){   
	  this->type();
	  leftChild = leftChild->simplify();
	  rightChild = rightChild->simplify();
      if(leftChild->isLeaf() && rightChild->isLeaf()){
		  
		  /*NULLSET . R = NULLSET  */
		  if (leftChild->getSymbol() == NULLSET){  
			  regexNode* temp = leftChild;
			  delete rightChild; //not required because deleting this (on next line) will delete rightchild
			  delete this;
			  return temp;
		  }
		  
		  /* R . NULLSET = NULLSET */
		  else if (rightChild->getSymbol() == NULLSET){ 
			  regexNode* temp = rightChild;
			  delete leftChild; //not required because deleting this (on next line) will delete rightchild
			  delete this;
			  return temp;
		  }
		  
		  /* EPSILON . R = R */
		  else if (leftChild->getSymbol() == EPSILON){
			  regexNode* temp = rightChild;
			  delete leftChild; //not required because deleting this (on next line) will delete rightchild
			  delete this;
			  return temp;
		  }
		  
		  /* R . EPSLION = R */
		  else if (rightChild->getSymbol() == EPSILON){  
			  regexNode* temp = leftChild;
			  delete rightChild; //not required because deleting this (on next line) will delete rightchild
			  delete this;
			  return temp;
		  }
      }
	  
	  return this;
  }
        




	void concatNode::type(){
		cout<<"Type is: concatNode"<<endl;
	}





/*********************** Regular Expression  **************************/
 

/*
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
/this is where the nested comments ended dont forget to comment it again
 
 the following used to work sometime. think about using it
		  
		  
		  
			
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

*/   

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
	
	
 
	



/* these may not be required any more
	bool regex::setRoot (regexNode * root){
		root->cascadeDel();
		this->root = root;
		return true;
	}
	
	bool regex::pureSetRoot(regexNode* root){
		this->root = root;
		return true;
	}
	

	regexNode * regex::getRoot(){
		return this->root;
	}

 */

	



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





