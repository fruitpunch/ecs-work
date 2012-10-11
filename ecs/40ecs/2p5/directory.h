//Hiu Hong Yu && Wen Xi Zhang
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "permission.h"
#include "Time.h"

#pragma once

using std::ostream;
using std::ifstream;

class linkedlist;
class Directory
{
    friend class linkedlist;
    friend ofstream& operator<< (ofstream &out, const Directory& dir);
    friend ifstream& operator >> (ifstream &in, Directory& dir);

  public:
    Directory *previousDir;// pointer to previous directory
    Directory *subDir[];// pointer to all sub directory
    Directory *temp;
    char *name;// name of directory char array
    Time *time;
    linkedlist *link;
    int subN;//subN = number of sub directory
    Permission *mask;// permission
    Directory(char name1[80]);
    Directory(Directory* original, Directory* prev);
    Directory(Directory* currentDir, char name1[80], int umask);
    Directory();
    ~Directory();
    bool operator < (const Directory &rhs);
    bool operator == (const Directory &rhs);
    void reconstructor(ifstream &in);
    bool validPermission(char command1[80], int mode=0);
    void changePermission(char name1[80], int new_permission);
    Directory* validChange(char name1[80]);
    bool validCreate(char name1[80], int mode=0);
    void list(char name1[80]);
    Directory* get();
    void copy(char name1[80], char name2[80]);
};//end Directory class


