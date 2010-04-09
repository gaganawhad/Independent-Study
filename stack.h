
class regexNode;// forward declaration of class regexNode.
//It says only that such a class exists. 
//There are only limited things you can do with it. 


using namespace std;


class regexStack{
  public:
  regexNode* a[100];
  int top; 

  regexStack();
  bool isEmpty();	
  bool isFull();
  void push(regexNode* i);
  regexNode* pop();
};

