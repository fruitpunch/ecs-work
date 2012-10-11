//Hiu Hong Yu && Wen Xi Zhang
#include "permissions.h"
using namespace std;

Permissions :: Permissions()
{
  perm = Permissions :: umask;
  owner = new char[80];
  u = perm % 10;
  g = ((perm - u) / 10) % 10;
  o = ((perm - (g * 10) - u) / 100) % 10;
}//end Permission()

//overloading operator <<
ofstream& operator << (ofstream& out,const Permissions &pe)
{ 
  out << pe.perm << " ";
  out << pe.owner <<" ";
  return out;
}//end << operator

//overloading operator >>
ifstream& operator >> (ifstream &in, Permissions &pe)
{
  in >> pe.perm;
  in >> pe.owner;
  return in;
}//end >> operator

void Permissions :: setUmask(char command1[80], char extra[80])
{
  //check for extra input
  if(strlen(extra) > 0 || strlen(command1) == 0)
  {   
    cout << "usage: umask octal" << endl;
    return ;
  }//end if
  
  //check if number range is valid
  if(validPermissions(command1, 1))
  {
    Permissions :: umask = atoi(command1);		
  }//end if
}//end umask

bool Permissions :: validPermissions(char command1[80], int mode)
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

void Permissions :: printPermissions()
{
  const char* const octal[] = {"rwx", "rw-", "r-x", "r--", "-wx", "-w-",
                               "--x", "---"};// premission list
  cout << octal[o] << octal[g] << octal[u] << " ";
}//end printUmask()

void Permissions :: update()
{
  u = perm % 10;
  g = ((perm - u) / 10) % 10;
  o = ((perm - (g * 10) - u) / 100) % 10;
}//end get()
int Permissions :: umask = 22;
