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
	virtual bool setLeftChild(regexNode* );
	virtual regexNode* getLeftChild();
	virtual bool setRightChild(regexNode*);
	virtual regexNode* getRightChild();
	virtual bool setChildren(regexNode*, regexNode*);
	virtual void display() =0; 
	virtual char getSymbol();
	virtual alphabet getLeaves() =0; //returns the leaves of the tree in the form of a stringstream

	
	virtual regexNode * simplify() =0; // virtual functions call the function to the corresponding object, even though the pointer is declared for the class higher in the hierarchy
  //virtual void delTree()=0;
  virtual ~regexNode();
  virtual bool cascadeDel()=0;
	virtual bool isNULL();
	virtual bool isEmpty();
	regexNode * operator + (regexNode * b);	
	regexNode * operator * ();	
	regexNode * operator - (regexNode * b);
	friend ostream& operator << (ostream& s, regexNode* a);
	friend ostream& operator << (ostream& s, regexNode& a);
	friend istream& operator >> (istream& s, regexNode& a);
};


/*********************** Unary Regex Node **************************/
class unaryRegexNode: public regexNode{
	protected:
	bool cascadeDel();

	regexNode* leftChild;

	public:
	bool setLeftChild(regexNode *);
	regexNode * getLeftChild();
	
	alphabet getLeaves();
    //    void delTree();
};




/*********************** Binary Regex Node **************************/
class binaryRegexNode: public unaryRegexNode{
	protected:
        bool cascadeDel();

        regexNode* rightChild;
    
	public:
	bool setRightChild(regexNode *) ;  
	regexNode * getRightChild();
	bool setChildren(regexNode* , regexNode* );
		
	alphabet getLeaves();
	
};



/*********************** Leaf Node **************************/

class leafNode: public regexNode {

  private:
  char symbol;

  public:
  leafNode();
  leafNode(char );

	bool isLeaf();
	bool isUnionTree();
		
	void display();
  char getSymbol();
	bool cascadeDel();
  alphabet getLeaves();
	regexNode* simplify();
};




/*********************** Star Node **************************/
class starNode: public unaryRegexNode{
  public:
	
  starNode();
  starNode (regexNode *);
  
  
  bool isStar();
void display();	




	regexNode* simplify(); 
 
};



/*********************** Union Node  **************************/
class unionNode: public binaryRegexNode{
  public:

  unionNode();
  unionNode( regexNode * leftChild, regexNode * rightChild);	

	bool isUnion();
	bool isUnionTree();
	
  void display();
 

  regexNode* simplify();
 
};



/*********************** Concatination Node  **************************/
class concatNode: public binaryRegexNode{
  public:

  concatNode();
  concatNode(regexNode * leftChild, regexNode * rightChild);

  bool isConcat();
void display();
  
	regexNode* simplify();
    
  


};



/*********************** Regular Expression  **************************/
/*
class regex{
  private:
  regexNode * root;
	
  public:
	
  regex ();
  regex (regexNode * );	
  regex (const char* s);	
  ~regex();
	bool cascadeDel();
  bool isNULL();
  bool isEmpty();
  bool isLeaf();	
  bool isUnionTree();
  bool setRoot (regexNode * root);	
  bool pureSetRoot(regexNode* root);
	
	
	void display();	
	
  alphabet getLeaves();

	regexNode * getRoot();  void simplify();	

  regex * operator + (regex * b);	
  regex * operator * ();	
  regex * operator - (regex * b);	
	
        
	
	//friend void operator << (ostream& s, regex& a);
	friend ostream& operator << (ostream& s, regex* a);
	friend ostream& operator << (ostream& s, regex& a);
	friend istream& operator >> (istream& s, regex& a);


};
 */




//void operator << (ostream& s, regex& a);
ostream& operator << (ostream& s, regexNode* a);
ostream& operator << (ostream& s, regexNode& a);
istream& operator >> (istream& s, regexNode& a);



