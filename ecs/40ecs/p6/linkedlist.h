//Hiu Hong Yu && Wen Xi Zhang
#include <cstdlib>
#pragma once

class Directory;
class Node
{  
  Directory *dir;
  Node *next;
  
  public:
    Node(Directory*, Node*);
    ~Node();
    friend class LinkedList;
};//end class Node

class LinkedList
{
  Node *head;
  friend class Directory;
  
  public:
    LinkedList();
    ~LinkedList();
    LinkedList& operator += (Directory *rhs);
    Directory* operator [](int index);
   LinkedList& operator = (LinkedList &rhs); 
};//end LinkedList
