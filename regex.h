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
  //Virtual functions call the function to the corresponding object, even though the pointer is declared for the class higher in the hierarchy
  //Test functions
  virtual bool isLeaf();
  virtual bool isStar();
  virtual bool isUnion();
  virtual bool isConcat() ;
  virtual bool isUnionTree();//Checks the tree starting from this node is UnionTree. UnionTree is one in which if there is any operation each is a Union 
  virtual bool isNULL();
  virtual bool isEmpty();

  //Getters and Setters for Children and others
  virtual bool setLeftChild(regexNode* );
  virtual regexNode* getLeftChild();
  virtual bool setRightChild(regexNode*);
  virtual regexNode* getRightChild();
  virtual bool setChildren(regexNode*, regexNode*);
  virtual char getSymbol();
  virtual alphabet getLeaves() =0; //Returns the leaves of the tree in the form of a stringstream

  //Display
  virtual void display() =0; 
  virtual void type();


  //Operators
  virtual regexNode * simplify() = 0; 
  virtual regexNode * replicate() =0;
  regexNode * operator + (regexNode&  );	
  regexNode * operator ++ (int);//The int is used to indicate that the operator is postfix.
  regexNode * operator - (regexNode&  );
  friend ostream& operator << (ostream& , regexNode* );
  friend ostream& operator << (ostream& , regexNode& );
  friend istream& operator >> (istream& , regexNode& );


  //Delete functions 
  virtual ~regexNode();
  //virtual void delTree()=0;
};


/*********************** Unary Regex Node **************************/
class unaryRegexNode: public regexNode{
  protected:

  regexNode* leftChild;
  
  public:

  bool setLeftChild(regexNode *);
  regexNode * getLeftChild();

  alphabet getLeaves();
  void type();

  virtual ~unaryRegexNode();
//void delTree();
};




/*********************** Binary Regex Node **************************/
class binaryRegexNode: public unaryRegexNode{
  protected:
  regexNode* rightChild;

  public:
  bool setRightChild(regexNode *) ;  
  regexNode * getRightChild();
  bool setChildren(regexNode* , regexNode* );
          
  alphabet getLeaves();
  void type();

  virtual ~binaryRegexNode();
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
		
  char getSymbol();
  alphabet getLeaves();
  
  void display();
  void type();

  regexNode * simplify();
  regexNode * replicate();
  ~leafNode();

};




/*********************** Star Node **************************/
class starNode: public unaryRegexNode{
  public:
	
  starNode();
  starNode (regexNode *);
  
  bool isStar();
  
  void display();	
  void type();

  regexNode * simplify();
  regexNode * replicate();
  ~starNode();
 
};



/*********************** Union Node  **************************/
class unionNode: public binaryRegexNode{

  public:

  unionNode();
  unionNode( regexNode * , regexNode * );	

  bool isUnion();
  bool isUnionTree();
	
  void display();
  void type();
 

  regexNode * simplify();
  regexNode * replicate();
  ~unionNode();
};



/*********************** Concatination Node  **************************/
class concatNode: public binaryRegexNode{

  public:

  concatNode();
  concatNode(regexNode * , regexNode * );

  bool isConcat();
  
  void display();
  void type();

  regexNode * simplify();
  regexNode * replicate();
  ~concatNode();
    
};


//void operator << (ostream& s, regex& a);
ostream& operator << (ostream& , regexNode* );
ostream& operator << (ostream& , regexNode& );
istream& operator >> (istream& , regexNode& );

