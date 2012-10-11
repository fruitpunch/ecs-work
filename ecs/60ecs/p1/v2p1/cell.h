#pragma once

#include <list>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;
class cell{

 public:
  int remain[9];
  int solved, left, guess;
  cell(int);
  
  cell(cell &original);
  void removeCell(int);
  int find(int);
  int getRemain();
  void clear();
  int front(int r=0);
};
