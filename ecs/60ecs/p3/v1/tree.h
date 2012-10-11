#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>

#pragma once

using namespace std;


class node{
 public:

  char key, smallest;
  int freq;
  bool leaf;
  string code;

  node *l, *r;
  node();
  node(int, int);
  node(node*, node*);
  void print();
  bool cmp(node*);
  
};

class heap{

 public:

  node **nodes;
  int size;

  heap(int);
  void push(node*);
  void pop();



};
