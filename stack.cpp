#include "stack.h"
#include <iostream>


  regexStack::regexStack(){
    top = 0; 
  }

  bool regexStack::isEmpty(){
    return (top==0?true:false);
  }
	
  bool regexStack::isFull(){
    return (top==99?true:false);
  }

  void regexStack::push(regexNode* i){
    if(!isFull()){
		a[top]=i;
		top++;
    }
	
    else{
      printf("Stack overflow error !Possible Data Loss ! \n");
    }
  }

  regexNode* regexStack::pop(){
    if(!isEmpty()){
      a[top] = NULL;
      return(a[--top]);
    }
    else{
      printf("Empty Stack");
      return NULL;
    }
	
  }


