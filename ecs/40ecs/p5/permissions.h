//Wen Xi Zhang && Hiu Hong Yu
#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

//struct that hold the umask value
class Permissions
{
  public:
    int perm;
    int o, g, u;
    char *owner;
    static int umask;
    Permissions();
    friend ofstream& operator<< (ofstream &out, const Permissions& pe);
    friend ifstream& operator>> (ifstream &in, Permissions &pe);
    static ofstream& write(ofstream &out);
    static ifstream& read(ifstream &in);
    static void setUmask(char command1[80], char extra[80]);
    static bool validPermissions(char command1[80], int mode=0);
    void printPermissions();
    void update();
    friend class Funix;
};//end class permission
