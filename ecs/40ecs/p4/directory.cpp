//Wen Xi Zhang && Hiu Hong Yu
#include "directory.h"
using namespace std;

Directory :: Directory(char name1[80])
{
  //Directory constructor
  name = new char[80];
  strcpy(name, name1);
  subN=0;
  temp=NULL;
}//end Directory()

//overloading constructor for read in data from directory.txt
//creating all the pervious directory that were created during last run
//use recurrsion
Directory :: Directory(Directory* original, Directory* prev)
{
  //overloading directory constructor
  name = new char[80];// name = new name
  mask = new Permission();//new umask
  time = new Time();// new time
  temp=NULL;
  strcpy(name, (*original).name);
  subN = (*original).subN;
  mask = (*original).mask;
  previousDir = prev;// perviousDirectry = new directory
  //scan for sub directory within the directory
  for(int i = 0; i < subN; i++)
  {
    subDir[i] = new Directory((*original).subDir[i], this);
  }//end for
}//end Directory(overloading constructor)

//overloading constructor for currectory directory
//creating root
Directory :: Directory(Directory* currentDir, char name1[80], int umask1)
{
  mask = new Permission();// new mask value
  time = new Time();// time
  temp=NULL;
  if(currentDir == NULL)
  {
    currentDir = this;
    name = new char[2];
    strcpy(name, "/");
    subN = 0;
    (*mask).set(22);
    return ;
  }//end if

  //creating new memory for directory and permission
  name = new char[strlen(name1) + 1];
  (*mask).set(umask1);//call the set function to set the umask value
  (*currentDir).subDir[(*currentDir).subN] = this;
  strcpy(name,name1);//copy the name from name1 to class variable
  previousDir = currentDir;// set perviousdirectory to current
  subN = 0;//number of subdirectory = 0
  (*currentDir).subN++;//number of current directory + 1
}//end Directory()

//overloaded constructor for only allocating memory
Directory :: Directory()
{
  
  name = new char[80];
  mask = new Permission();
  time = new Time(1, 2);
  temp=NULL;
}//end Directory(default constructor)

//use recurrsion
Directory :: ~Directory()
{
  //delete memory that were created for sub directory
  for(int i = 0; i < subN; i++)
  {
    if(subDir[i] != NULL)//if there are sub directory exist
    {
      delete subDir[i];//delete the memory of sub directory
    }//end if
  }//end for
  //delete memory of temp that were used to compare
  if(temp != NULL)//if temp exit
  {
    delete temp;//delete
  }//end if
  //delete the memory of name
  delete[] name;
}//end destructor ~Directory

//overloading operator for print
//use recurrsion
ofstream& operator << (ofstream &out, const Directory& dir)
{
  out << (*dir.name) << " ";
  out << dir.subN << " ";
  out << (*dir.mask);
  out << (*dir.time);
  out << endl;

  for(int i = 0; i < dir.subN; i++)
  {
    out << (*dir.subDir[i]);
  }//end for

  return out;
}//end << operator

//overloading operator << scan in
ifstream& operator >>(ifstream &in, Directory& dir)
{
  in >> dir.name;
  in >> dir.subN;
  in >> (*dir.mask);
  in >> (*dir.time);
  
  return in;
}//end overloading >> operator

//overloading == operator
bool Directory :: operator == (const Directory &rhs)
{
  return (strcmp(name, rhs.name) == 0);
}//end == operator

//read in data from directory.txt
void Directory :: reconstructor(ifstream &in)
{
  while(!in.eof())//while not end of file, keep scanning
  {
    for(int track = 0; track < subN; track++)
    {
      subDir[track] = new Directory();
      in >> (*subDir[track]);
      (*subDir[track]).previousDir = this;
      (*subDir[track]).reconstructor(in);
    }//end for
    break;
  }//end while
}//end reconstructor

//check if valid permission were entered
//default paramater to tell if being called from umask or chmod
bool Directory :: validPermission(char command1[80], int mode)
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

void Directory :: changePermission(char name1[80], int new_permission)
{
  //create new memory
  temp = new Directory(name1);
  //scan tho the directory
  for(int i = 0; i < subN; i++)
  {
    if((*temp) == (*subDir[i]))//found match
    {
      //change the new permission to the directory
      (*subDir[i]->mask).perm = new_permission;
      (*subDir[i]->time).updateTime();//apply new time
      return ;
    }//end if
  }//end for
  cout << "chmod: failed to get attributes of '" << name1
       << "': No such file or directory" << endl;
}//end change permission

Directory* Directory :: validChange(char name1[80])
{
  temp = new Directory(name1);
  //if cd with ..
  if(strcmp("..", name1) == 0)
  {
    if(previousDir == NULL)//if no previous directory
    {
      return this;
    }//end if
    else//else return the pervious directory
    {
      return (*previousDir).get();
    }//end else
  }//end if
  else if(subN == 0)//if trying to cd into a directory that DNE
  {
    cout << name1 << ": no such file or directory" << endl;
    return this;
  }//end else if
  else//look through the directory list, c if there any match
  {
    for(int i = 0; i < subN; i++)
    {
      if((*temp) == (*subDir[i]))//if found match
      {
        return (*subDir[i]).get();
        break;
      }//end if
      else//
      { 
      	if(i == subN - 1)//if no match directory, error message
      	{
         cout << name1 << ": no such file or directory." << endl;
         return this;
      	}//end if
      }//end else
    }//end for
  }//else
  return this;
}//end validchange()

bool Directory :: validCreate(char name1[80], int mode)
{
  temp = new Directory(name1);
  if(subN < 3)//if number of directory < 3
  {
    for(int i = 0; i < subN; i++)
    {
      if((*temp) == (*subDir[i]))
      {
        if(mode == 1)
        {
          cout << "cp: omitting directory '" << name1 << "'" << endl;
        }//end if
        else
        {
          cout << "mkdir: cannot create directory '" << name1
               << "': File exists" << endl;
        }//end else
        return false;
      }//end if
    }//end for 
    return true;
  }//end else if
  else// if the directory have already 3 sub directory, error message
  {
    if(mode == 1)
    {
      cout << "cp: ";
    }//end if
    else
    {
      cout << "mkdir: ";
    }//end else
    cout << name << " already contains the maximum number of directories"
         << endl;	   
    return false;
  }//end else
  return true;
}//end ValidCreate()

void Directory :: list(char command1[80])
{
  for(int i = 0; i <= subN - 1; i++)
  {
    if(strlen(command1) == 0)//if there no extra list option (-l)
    {
      cout << (*subDir[i]).name << " ";
    }//end if
    else if(strcmp(command1, "-l") == 0)// if -l included
    {//list all permission, time, and name of the representing directory
      (*subDir[i]->mask).printUmask();
      (*subDir[i]->time).printTime();
      cout << " " << (*subDir[i]).name << endl;
    }//end else if
    else//if command entered incorrectly, error message
    { 
      cout << "usage: ls [-l]" << endl << command1;
      return;
    }//end else
  }//end for
  if(subN > 0 && strlen(command1) == 0)// if no sub directory
  {
    cout << endl;
  }//end if
}//end list()

Directory* Directory :: get()
{
  return this;
}//end get()

//copy function recursively in copy constructor
void Directory:: copy(char name1[80], char name2[80])
{
  temp = new Directory(name1);
  for(int i = 0; i < subN; i++)
  {
    if((*temp) == (*subDir[i]))//if found match directory in current
    {
      //create new directory with the name provided
      subDir[subN] = new Directory(subDir[i], this);
      strcpy((*subDir[subN]).name, name2 ); //rename the new directory
      subN++;
      break;
    }//end if
  }//end for
}//end copy()
