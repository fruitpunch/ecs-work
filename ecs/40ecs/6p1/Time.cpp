//Hiu Hong Yu && Wen Xi Zhang
#include "Time.h"
using namespace std;

//Time default constructor
Time :: Time()
{
  //set time, month, day, hour, minute, and second
  //with current local computer time, and date
  //then setting the time with local computer time
  time_set = time(0);
  tm = localtime(&time_set);
  month = tm->tm_mon;
  day = tm->tm_mday;
  hour = tm->tm_hour;
  minute = tm->tm_min;
  second = tm->tm_sec;
 
}//end Time()

//constructor overload, useless int value to distinguish between =.=
Time :: Time(int i, int u)
{
}//end Time()

//constructor overload
Time :: Time(Time& new_time) : month(new_time.month), day(new_time.day),
                               hour(new_time.hour), minute(new_time.minute),
                               second(new_time.second)
{
}//end Time()

//operator overload
ofstream& operator << (ofstream &out, const Time &tim)
{
  out << tim.month << " "
      << tim.day << " "
      << tim.hour << " "
      << tim.minute << " "
      << tim.second <<endl;
  return out;
}//end << operator

//operator overload
ifstream& operator >> (ifstream &in, Time &ti)
{
  in >> ti.month;
  in >> ti.day;
  in >> ti.hour;
  in >> ti.minute;
  in >> ti.second;
  return in;
}//end >> operator

//update the current time to the file time
void Time :: updateTime()
{
  //set the time with local computer time
  time_set = time(0);
  tm = localtime(&time_set);
  month = tm->tm_mon;
  day = tm->tm_mday;
  hour = tm->tm_hour;
  minute = tm->tm_min;
  second = tm->tm_sec;
}//end updateTime()

// print out the time of the directory/file when use ls -l
void Time :: printTime()
{
  cout << setfill('0');
  cout << getMonth()
       << " " << setw(2) << day
       << " " << setw(2) << hour
       << ":" << setw(2) << minute
       << ":" << setw(2) << second;

}//end printTime()

//convert the number to month from directory.txt
const char* Time :: getMonth() const
{
  const char* const mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  return mon[month]; 
}//end getMonth()
