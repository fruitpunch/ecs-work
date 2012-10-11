//#define NDEBUG
//#define DEBUG
//#ifndef NDEBUG
//#define NDEBUG


#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cassert>

#pragma once
using namespace std;



class Whoops:public exception
{

 private:
  char* err;

 public:

  Whoops(string in){
    err=new char[in.size()+1];
    strcpy(err, in.c_str());
  }
    
  virtual const char* what() const throw(){

    return err;
  }
};

template<class T>
class SVector{

 private:
  typedef map<string, int> StringMap;
  StringMap strMap;
  vector<string> *strVec;
  int range;

 public:
  SVector(int);
  void push_back(const string in, const int value);
  T operator[](const string in);
  void pop_back();


};
#include "SVector.cpp"
