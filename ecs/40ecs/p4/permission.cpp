//Hiu Hong Yu && Wen Xi Zhang
#include "permission.h"
using namespace std;

Permission :: Permission()
{

}//end Permission()

//overloading operator <<
ofstream& operator << (ofstream& out,const Permission &pe)
{ 
  out << pe.perm << " ";
  return out;
}//end << operator

//overloading operator >>
ifstream& operator >> (ifstream &in, Permission &pe)
{
  in >> pe.perm;
  return in;
}//end >> operator

void Permission::printUmask()
{
  const char* const octal[] = {"rwx", "rw-", "r-x", "r--", "-wx", "-w-",
                               "--x", "---"};// premission list
  //convert umask value with enter value
  int o = perm % 10;
  int g = ((perm - o) / 10) % 10;
  int u = ((perm - (g * 10) - o) / 100) % 10;
  cout << octal[u] << octal[g] << octal[o] << " ";
}//end printUmask()

void Permission :: set(int i)
{
  perm = i;
}//end set()

int Permission :: get()
{
  return perm;
}//end get()
