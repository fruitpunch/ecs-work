#pragma once
#include "holder.h"

class puzzle{

 public:

  box *bx[9], *rw[9], *clmn[9] ;
  cell* subCell[81];

  int total, guess;
  bool validPuzzle;

  puzzle(int in[81]);
  void copy(puzzle *original);
  void print();
  int eliminate();
  int fill();
  int getNum(puzzle*);
  void getArray(int in[81]);
  void getbox(int, cell* in[9], cell* p[81]);
  bool valid();
  void updatePuzzle();
  int getSize(int in[9]);
 

};
