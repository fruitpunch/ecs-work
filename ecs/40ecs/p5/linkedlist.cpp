#include "linkedlist.h"
#include "directory.h"
#include <iostream>
using namespace std;

//Node constructor
Node :: Node(Directory *inDir, Node *inNode) : dir(inDir), next(inNode)
{
}//end Node()

//Node destructor
Node :: ~Node()
{
  delete dir;//delete memory
}//end ~Node

//LinkedList constructor
LinkedList :: LinkedList() : head(NULL)
{
}//end LinkedList()

//LinkedList destructor
LinkedList :: ~LinkedList()
{
  Node *ptr;
  for(ptr = head; head ; ptr = head)
  {
    head = head->next;
    delete ptr;//delete memory
  }//end for
}//end ~LinkedList()

//add new directory to linklist
LinkedList& LinkedList :: operator += (Directory *rhs)
{
  Node *ptr, *prev = NULL;
  ptr = head;

  //add rhs to linkedlist
  while(ptr && (*ptr->dir) < (*rhs))
  {
    prev = ptr;
    ptr = ptr->next;
  }//end while
  if(!prev)//if its the head
    head = new Node(rhs, ptr);
  else 
    prev->next = new Node(rhs, ptr);
  return *this;
}//end LinkedList

//scan tho all sub directory
Directory* LinkedList :: operator [] (int index)
{  
  Node* ptr;
  ptr = head;
  for(int i = 0; i < index; i++)
  {
    if(ptr->next)
      ptr = ptr->next;
    else
      break;
  }//end for
  return ptr->dir;
}//end operator []

//set directory to = to another directory with linklist
LinkedList& LinkedList :: operator = (LinkedList &rhs)
{
  //set directory = directory
  for(Node *ptr = rhs.head; ptr; ptr = ptr->next)
  {
    //create new directory
    Directory *d = new Directory(*(ptr->dir));
    //add to linklist
    *this += d;
  }//end for
  return *this;
}//end operator =
