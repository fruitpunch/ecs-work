#pragma once

#include <list>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;
class cell{

 public:
  list<int> remain;
  int solved, left, guess;
  cell(int);
  
  cell(cell &original);
  void removeCell(int);
  int find(int);
  friend ofstream& operator << (ofstream &out, cell &c);
};
