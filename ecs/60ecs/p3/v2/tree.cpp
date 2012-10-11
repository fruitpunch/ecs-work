#include "tree.h"

using namespace std;

tNode::tNode(int character, int frequency){

  key=smallest=character;
  freq=frequency;
  l=r=p=NULL;
  leaf=true;
  //side=false;

}
tNode::tNode(tNode *one, tNode *two){

  if(!one->cmp(two)){
    l=one;
    r=two;
    one->side=0;
    two->side=1;
  }
  else{
    l=two;
    r=one;
    one->side=1;
    two->side=0;
  }
  freq=l->freq +  r->freq;
  leaf=false;
  p=NULL;
  key='\0';
  if(one->smallest < two->smallest) smallest= one->smallest;
  else smallest= two->smallest;

}

bool tNode::cmp(tNode *in){

  if(freq < in->freq) return true;
  else if(freq > in->freq) return false;
  else{
    if(smallest < in->smallest) return true;
  }
  return false;
}

void tNode::findCode(){

  tNode *ptr;
  string add;
  ptr=this;

  while(ptr){
    if(ptr->side)add='1';
    else add='0';
    if(ptr->p){
      add=add+code;
      code=add;
    }
    ptr=ptr->p;
  } 
}


  

void tNode::print(){
  
  
  cout<<(unsigned char)(freq%256);
  cout<<(unsigned char)((freq>>8)%256);
  cout<<(unsigned char)((freq>>16)%256);
  cout<<(unsigned char)((freq>>24)%256);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

lNode::lNode(tNode *inData, lNode *inNode){

  data=inData;
  next=inNode;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

llist::llist(){

  head=NULL;
  size=0;

}

void llist::push(tNode *in){

  lNode *ptr, *prev=NULL;
  ptr=head;

  while(ptr && ptr->data->cmp(in)){

    prev=ptr;
    ptr=ptr->next;
  }
  size++;
  if(!prev)head=new lNode(in, ptr);
  else prev->next=new lNode(in, ptr);

}

void llist::pop(){

  if(size>0){
    head=head->next;
    size--;
  }
}

tNode* llist::top(){

  return head->data;
}

void llist::print(){

  lNode *ptr;
  ptr=head;

  while(ptr){
    ptr->data->print();
    ptr=ptr->next;
  }
}

void llist::merge(){

  tNode *one, *two, *newNode;

  while(size>1){

    one=top();
    pop();
    two=top();
    pop();
    newNode=new tNode(one, two);
    one->p=newNode;
    two->p=newNode;
    push(newNode);
  }
}
      

    


