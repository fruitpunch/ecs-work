//Hiu Hong Yu && Wen Xi Zhang

#pragma once//=#ifndef then #define

#include "file.h"
//#include "permissions.h"
//#include "Time.h"
//#include "linkedlist.h"


using std :: ostream;
using std :: ifstream;

class Directory:public File
{
    friend ofstream& operator << (ofstream &out, Directory& dir);
    friend ifstream& operator >> (ifstream &in, Directory& dir);

  public:
    void hello();
    Directory *previousDir;// pointer to previous directory
    Directory *temp;
    File *tempFile;
    int subN;//subN = number of sub directory
    Directory(char name1[80]);
    Directory(Directory &original);
    Directory(Directory* currentDir, char name1[80], char user[80]);
    Directory();
    // ~Directory();
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
    ofstream& write(ofstream&);
    void touch(char*, char*);
};//end Directory class


