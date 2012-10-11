//Wen Xi Zhang && Hiu Hong Yu

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

//struct that hold the umask value
class Permission
{
  public:
    int perm;
    //ofstream outfile;
    Permission();
    friend ofstream& operator<< (ofstream &out,const Permission& pe);
    friend ifstream& operator>> (ifstream &in, Permission &pe);
    void printUmask();
    void set(int i);
    int get();
};//end class permission
