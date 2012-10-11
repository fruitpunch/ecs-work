//Hiu Hong Yu && Wen Xi Zhang
#include "permissions.h"
using namespace std;

Permission :: Permission()
{
  perm=Permission::umask;
  u = perm % 10;
  g = ((perm - u) / 10) % 10;
  o = ((perm - (g * 10) - u) / 100) % 10;
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

void Permission :: setUmask(char command1[80], char extra[80])
{
  //check for extra input
  if(strlen(extra) > 0 || strlen(command1) == 0)
  {   
    cout << "usage: umask octal\n";
    return ;
  }//end if
  
  //check if number range is valid
  if(validPermission(command1, 1))
  {
    Permission::umask = atoi(command1);		
  }//end if
}//end umask

bool Permission :: validPermission(char command1[80], int mode)
{
  unsigned int i;
  int track = 0;
  //check to c if the number of input value is correct
  for(i = 0; i < strlen(command1); i++)
  {
    if(isdigit(command1[i]))//if entered is digit not something else
    {
      if(command1[i] == '9' || command1[i] == '8' )
      {
        track = 1;
      }//end if
    }//end if
    else//if not print out error
    {
      if(mode == 1)
      {
        cout << "usage: umask octal" << endl;
      }//end if
      else
      {
        cout << "chmod: invalid mode string: '" << command1 << "'" << endl;
      }//end else

      return false;
    }//end if
  }//end for
   
  //if the number are between 0 to 7, then it correct
  if(atoi(command1) <= 777 && track == 0)
  {
    return true;
  }//end if
  else//else error message
  { 
    if(mode == 1)
    {
      cout << "usage: umask octal" << endl;
    }//end if    
    else
    {
      cout << "chmod: invalid mode string: '" << command1 << "'" << endl;
    }//end else

    return false;
  }//end else
}//end Valid Umask

void Permission::printPermission()
{
  const char* const octal[] = {"rwx", "rw-", "r-x", "r--", "-wx", "-w-",
                               "--x", "---"};// premission list
  cout << octal[o] << octal[g] << octal[u] << " ";
}//end printUmask()

void Permission :: update()
{
  u = perm % 10;
  g = ((perm - u) / 10) % 10;
  o = ((perm - (g * 10) - u) / 100) % 10;
}//end get()
int Permission::umask=22;
