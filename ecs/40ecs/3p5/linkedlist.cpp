#include "linkedlist.h"
#include "directory.h"
#include <iostream>
using namespace std;

Node::Node(Directory *inDir, Node *inNode):dir(inDir),next(inNode){
}
Node::~Node(){
  delete dir;
}

LinkedList::LinkedList():head(NULL){}
LinkedList::~LinkedList(){

  Node *ptr;
  for(ptr=head;head;ptr=head){
    head=head->next;
    delete ptr;
  }
}

LinkedList& LinkedList :: operator += (Directory *rhs)
{
  Node *ptr, *prev=NULL;
  ptr=head;
  //rhs->hello();
  while(ptr && (*ptr->dir) < (*rhs)){

    prev=ptr;
    ptr=ptr->next;
  }
  if(!prev) head = new Node(rhs, ptr);
  else prev->next = new Node(rhs, ptr);
  return *this;
}
Directory* LinkedList::operator [] (int index){
  
  Node* ptr;
  ptr=head;
  for(int i=0;i<index;i++){
    if(ptr->next)
      ptr=ptr->next;
    else break;
  }
  return ptr->dir;
}
LinkedList& LinkedList :: operator = (LinkedList &rhs)
{
  // Node *ptr=rhs;
  for(Node *ptr=rhs.head ;ptr;ptr=ptr->next){
    Directory *d = new Directory(*(ptr->dir));
    *this+=d;
  }
  return *this;
}
