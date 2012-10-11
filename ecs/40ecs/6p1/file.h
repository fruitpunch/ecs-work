#pragma once

#include "permissions.h"
#include "Time.h"
#include "linkedlist.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <fstream>


class File{

 private:
  friend ofstream& operator << (ofstream &out, File& file);
  friend ifstream& operator >> (ifstream &in, File& file);
  char *name;
  Permissions *mask;
  Time *time;
  template<class> friend class LinkedList;

 public:
  LinkedList<File> subDir;
  File();
  File(char name[80],int p=111);
  File(File &original);
  virtual ~File();
  bool operator < (File &rhs);
  int checkPermissions();
  void changePermissions(int);
  void chown(const char*);
  void print(int mode=0);//0=ls      1=ls -l
  void rename(const char*);
  char* showName();
  void touch();
  bool operator == (File &rhs);
  virtual ofstream& write(ofstream& out);
  Time& getTime();
  Permissions& getPermissions();
  File* get();
  bool isFile();



};
