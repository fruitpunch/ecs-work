//Hiu Hong Yu && Wen Xi Zhang
#pragma once

#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include "directory.h"

//struct for current directory

class Funix
{
  private:
    Directory* currentDir;
    char *user;
    void cd(char name1[80], char extra[80]);
    int eXit(char extra[80]);
    void writePrompt();
    void getCommand(char command1[80], char command2[80],
		    char command3[80], char command4[80]);
    void ls(char command1[80], char extra[80]);
    void mkdir(char name1[80], char extra[80]);
    // void setUmask(char command1[80], char extra[80]);
    void chmod(char command1[80], char command2[80], char extra[80]);
    void cp(char command1[80], char command2[80], char extra[80]);
    void su(char name1[80], char extra[80]);
    void chown(char name1[80], char dir[80], char extra[80]);
    int processCommand(char command1[80]);
 
  public:
    Funix();
    ~Funix();
    void run();
    friend ofstream& operator << (ofstream& out, const Funix& fn);
    friend ifstream& operator >> (ifstream& in, Funix& fn);
};//end Funix class
