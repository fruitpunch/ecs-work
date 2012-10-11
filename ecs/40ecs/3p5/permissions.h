//Wen Xi Zhang && Hiu Hong Yu

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

//struct that hold the umask value
class Permission
{

  public:
    int perm;
    int o, g, u;
    static int umask;
    Permission();
    friend ofstream& operator<< (ofstream &out,const Permission& pe);
    friend ifstream& operator>> (ifstream &in, Permission &pe);
    static void setUmask(char command1[80], char extra[80]);
    static bool validPermission(char command1[80], int mode=0);
    void printPermission();
    void update();
    friend class Funix;
};//end class permission
