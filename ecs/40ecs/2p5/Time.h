#pragma once
#include "Time.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

class Time
{
  private:
    time_t time_set;
    struct tm* tm;
    
  public:
   Time();
   Time(int i, int u);
   Time(Time& new_time);
   friend ofstream& operator<< (ofstream &out, const Time& ti);
   friend ifstream& operator>> (ifstream &in, Time& ti);
   const char* getMonth()const;
   void printTime();
   void updateTime();
   int month, day, hour, minute, second;
};
