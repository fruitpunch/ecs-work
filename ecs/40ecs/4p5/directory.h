//Hiu Hong Yu && Wen Xi Zhang

#pragma once//=#ifndef then #define

#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "permissions.h"
#include "Time.h"
#include "linkedlist.h"


using std :: ostream;
using std :: ifstream;

//class Node;
class Directory
{
    friend ofstream& operator << (ofstream &out, Directory& dir);
    friend ifstream& operator >> (ifstream &in, Directory& dir);
    friend class LinkedList;

  public:
    void hello();
    bool operator < (Directory &rhs);
    Directory *previousDir;// pointer to previous directory
    LinkedList subDir;// pointer to all sub directory
    Directory *temp;
    char *name;// name of directory char array
    Time *time;
    int subN;//subN = number of sub directory
    Permissions *mask;// permission
    Directory(char name1[80]);
    Directory(Directory &original);
    Directory(Directory* currentDir, char name1[80], char user[80]);
    Directory();
    ~Directory();
    bool operator == (const Directory &rhs);
    void reconstructor(ifstream &in);
    void changePermissions(char name1[80], char user[80], int new_permission);
    Directory* validChange(char name1[80], char user[80]);
    bool validCreate(char name1[80], char user[80], int mode = 0);
    void list(char name1[80], char user[80]);
    Directory* get();
    void copy(char name1[80], char name2[80], char user[80]);
    void changeOwner(char newOwner[80], char dir[80]);
    bool validExecution(char user[80], int mode);
};//end Directory class


