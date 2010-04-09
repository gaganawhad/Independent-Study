/*
 *  regex.h
 *  
 *  Created on 14th March 2010 to organize code better. 
 *
 */
 


#define EPSILON -1 // empty string
#define NULLSET -2 // null set
#include "alphabet.h"
using namespace std;

class regexNode{
	
  public:
  virtual bool isLeaf() ;// should these functions be virtual or not?
  virtual bool isStar() ;
  virtual bool isUnion();
  virtual bool isConcat() ;
  virtual bool isUnionTree(); //function that tests if all of the tree has only union nodes or leaf nodes
	virtual regexNode * simplify() =0; // virtual functions call the function to the corresponding object, even though the pointer is declared for the class higher in the hierarchy
  virtual void display() =0; 
	virtual alphabet getLeaves() =0; //returns the leaves of the tree in the form of a stringstream
  virtual char getSymbol();

	virtual regexNode* getLeftChild();
	virtual bool setLeftChild(regexNode* );
	virtual regexNode* getRightChild();
	virtual bool setRightChild(regexNode*);

};



class unaryRegexNode: public regexNode{
	protected:
  regexNode* leftChild;

	public:
	bool setLeftChild(regexNode *);
	regexNode * getLeftChild();
}




class binaryRegexNode: public unaryRegexNode{
	protected:
	regexNode* rightChild;

	public:
	bool setRightChild(regexNode *) ;  
	regexNode * getRightChild();
	
}




class leafNode: public regexNode {

  private:
  char symbol;

  public:
  leafNode();
  leafNode(char symbol);
		
  void display();
	bool isLeaf();
  bool isUnionTree();
	
  regexNode* simplify();
		
  char getSymbol();

         
//  bool setLeftChild(regexNode *); 
//  bool setRightChild(regexNode *);
//  regexNode * getLeftChild();
//  regexNode * getRightChild();

  alphabet getLeaves();
	
};





class starNode: public unaryRegexNode{
  public:
	
  starNode();
  starNode (regexNode *);
  
//  bool setLeftChild(regexNode *leftChild);
  
  void display();	
 // bool isLeaf();
  bool isStar();
  bool isUnionTree();
//  bool setLeftChild(regexNode * );
//  regexNode * getLeftChild();
 regexNode* simplify(); 
  alphabet getLeaves();
};




class unionNode: public regexNode{
  public:

  unionNode();
  unionNode( regexNode * leftChild, regexNode * rightChild);	
//  void setRightChild(regexNode* rightChild);
  regexNode * getRightChild();
  void display();
  bool isStar(); 
  bool isUnion();
  bool isUnionTree();
			
  regexNode* simplify();
  alphabet getLeaves();
};




class concatNode: public regexNode{
  public:

  concatNode();
  concatNode(regexNode * leftChild, regexNode * rightChild);
  regexNode * getRightChild();	
  void setRightChild(regexNode*);
  void display();
  bool isStar(); 
  bool isConcat();
  bool isUnionTree();
  regexNode* simplify();
  alphabet getLeaves();      
  


};




class regex{
  private:
  regexNode * root;
	
  public:
	
  regex ();
  regex (regexNode * );	
  regex (const char* s);	

		
  bool isNULL();
  bool isEmpty();
  bool isLeaf();	
  bool isUnionTree();
  void simplify();	
  void display();	
  void setRoot (regexNode * root);	
  regexNode * getRoot();	
  alphabet getLeaves();
	
  regex * operator + (regex * b);	
  regex * operator * ();	
  regex * operator - (regex * b);	
	
        
	
	//friend void operator << (ostream& s, regex& a);
	friend ostream& operator << (ostream& s, regex* a);
	friend ostream& operator << (ostream& s, regex& a);
	friend istream& operator >> (istream& s, regex& a);


};




//void operator << (ostream& s, regex& a);
ostream& operator << (ostream& s, regex* a);
ostream& operator << (ostream& s, regex& a);
istream& operator >> (istream& s, regex& a);



