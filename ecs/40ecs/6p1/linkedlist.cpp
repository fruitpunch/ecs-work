//Hiu Hong Yu && Wen Xi Zhang
#include <iostream>
using namespace std;

//Node constructor
template<typename T>
Node<T> :: Node(T *in, Node *inNode) : data(in), next(inNode)
{
}//end Node()

//Node destructor
template<typename T>
Node<T> :: ~Node()
{
  delete data;//delete memory
}//end ~Node

//LinkedList constructor
template<typename T>
LinkedList<T> :: LinkedList():head(NULL)
{
}//end LinkedList()

//LinkedList destructor
template<typename T>
LinkedList<T> :: ~LinkedList()
{
  Node<T> *ptr;
  for(ptr = head; head ; ptr = head)
  {
    head = head->next;
    delete ptr;//delete memory
  }//end for
}//end ~LinkedList()

//add new directory to linklist
template<typename T>
LinkedList<T>& LinkedList<T> :: operator += (T *rhs)
{
  Node<T> *ptr, *prev = NULL;
  ptr = head;

  //add rhs to linkedlist
  while(ptr && (*ptr->data) < (*rhs))
  {
    prev = ptr;
    ptr = ptr->next;
  }//end while
  if(!prev)//if its the head
    head = new Node<T>(rhs, ptr);
  else 
    prev->next = new Node<T>(rhs, ptr);
  return *this;
}//end LinkedList

//scan tho all sub directory
template<typename T>
T* LinkedList<T> :: operator [] (int index)
{  
  Node<T> *ptr = head;
  for(int i = 0; i < index; i++)
  {
    if(ptr->next)
      ptr = ptr->next;
    else
      break;
  }//end for
  return ptr->data;
}//end operator []

template<typename T>
const LinkedList<T>& LinkedList<T> :: operator = (const LinkedList &rhs)
{
  Node<T> *ptr;
  for(ptr = rhs.head; ptr; ptr = ptr->next)
  {
    T *obj = new T(*(ptr->data));
    //add to linklist
    *this += obj;
  }//end for
  return *this;
}//end operator =
