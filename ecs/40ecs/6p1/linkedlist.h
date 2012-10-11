//Hiu Hong Yu && Wen Xi Zhang
#include <cstdlib>
#pragma once

template<typename T>
class Node
{    
 public:
  Node(T*, Node*);
  ~Node();
  template<class> friend class LinkedList;
 private:
  T *data;
  Node *next;
};//end class Node

template<typename T>
class LinkedList
{
  Node<T> *head;
  friend class File;
  
  public:
    LinkedList();
    ~LinkedList();
    LinkedList& operator += (T *rhs);
    T* operator [](int index);
    const LinkedList& operator = (const LinkedList &rhs); 

};//end LinkedList
#include "linkedlist.cpp"
