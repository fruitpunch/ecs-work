#include <cstdlib>

#pragma once

class Directory;
class linkedlist{

  Directory *head;

 public:
  linkedlist();
  ~linkedlist();
  void operator += (Directory &rhs);
  const Directory* operator [](int index)const;
  
};
