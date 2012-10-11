//Wen Xi Zhang && Hiu Hong Yu
#include "directory.h"
using namespace std;

//constructor with one parameter
//set default temp = NULL
Directory :: Directory(char name1[80]) : temp(NULL)
{
  //Directory constructor
  name = new char[80];
  strcpy(name, name1);
  subN = 0;
}//end Directory()

//overloading constructor for read in data from directory.txt
//creating all the pervious directory that were created during last run
//use recurrsion, set default temp = NULL
Directory :: Directory(Directory &original) : temp(NULL)
{
  //overloading directory constructor
  name = new char[80];// name = new name
  mask = new Permission();//new umask
  time = new Time();// new time
  strcpy(name, original.name);
  subN = original.subN;
  mask = original.mask;
  owner=original.owner;
  previousDir = original.previousDir;// perviousDirectry = new directory
  //scan for sub directory within the directory
  subDir=original.subDir;
}//end Directory(overloading constructor)

//overloading constructor for currectory directory
//creating root, set default temp to NULL
Directory :: Directory(Directory* currentDir, char name1[80], char user[80]) : temp(NULL)
{
  mask = new Permission();// new mask value
  time = new Time();// time
  owner = new char[80];
  name = new char[80];
  if(currentDir == NULL)
  {
    currentDir = this;
    strcpy(name, "/");
    subN = 0;
    return ;
  }//end if

  //creating new memory for directory and permission

  strcpy(owner, user);
  strcpy(name,name1);//copy the name from name1 to class variable
  (*currentDir).subDir += this;
  previousDir = currentDir;// set perviousdirectory to current
  subN = 0;//number of subdirectory = 0
  (*currentDir).subN++;//number of current directory + 1
}//end Directory()

//overloaded constructor for only allocating memory
//set default temp to NULL
Directory :: Directory() : temp(NULL)
{ 
  name = new char[80];
  owner = new char[80];
  mask = new Permission();
  time = new Time(1, 2);
  // subDir = new LinkedList();
}//end Directory(default constructor)

//use recurrsion
Directory :: ~Directory()
{
  //delete memory that were created for sub directory
  //delete the memory of name
  if(name) delete[] name;
  if(owner) delete [] owner;
  if(mask) delete mask;
  if(time) delete time;
}//end destructor ~Directory

//overloading operator for print
//use recurrsion
ofstream& operator << (ofstream &out, Directory& dir)
{
  out << dir.name << " ";
  out << dir.subN << " ";
  out << (*dir.mask);
  out << (*dir.time)<<" ";
  out << dir.owner;
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
  in >> dir.owner;
  
  return in;
}//end overloading >> operator

bool Directory:: operator < (Directory &rhs)
{
  return !(strcmp(name, rhs.name)>0);
}

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
      temp = new Directory();
      in >> *temp;
      (*temp).previousDir = this;
      (*temp).reconstructor(in);
      subDir += temp;
    }//end for
    break;
  }//end while
}//end reconstructor

//check if valid permission were entered
//default paramater to tell if being called from umask or chmod


void Directory :: changePermission(char name1[80], char user[80] ,int new_permission)
{
  //create new memory
  temp = new Directory(name1);
  //scan tho the directory
  if(!(*this).validExecution(user, 0)){
    cout<<"chmod: Permission denied"<<endl;
    return ;
  }
  for(int i = 0; i < subN; i++)
  {
    if((*temp) == (*subDir[i]))//found match
    {
      //change the new permission to the directory
      if(!(*this).validExecution(user, 2)){
	cout<<"chmod: Permission denied"<<endl;
	return ;
      }
      (*subDir[i]->mask).perm =new_permission;
      (*subDir[i]->mask).update();
      (*subDir[i]->time).updateTime();//apply new time
      return ;
    }//end if
  }//end for
  cout << "chmod: failed to get attributes of '" << name1
       << "': No such file or directory" << endl;
}//end change permission

Directory* Directory :: validChange(char name1[80], char user[80])
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
    if(!((*this).validExecution(user, 0))){
      cout<<"cd: Permission denied"<<endl;
      return this;
    }
    for(int i = 0; i < subN; i++)
    {
      if((*temp) == (*subDir[i]))//if found match
      {
	if(!((*subDir[i]).validExecution(user, 1))){
	  cout<<"cd: Permission denied"<<endl;
	  return this;
	}
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

bool Directory :: validCreate(char name1[80], char user[80], int mode)
{
  temp = new Directory(name1);

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
  }//end else if
  if(!(*this).validExecution(user,2)){
    cout<<((mode==1)? "cp: ":"mkdir: ")<<"Permission denied"<<endl;
    return false;
  }
  return true;
}//end ValidCreate()

void Directory :: list(char command1[80], char user[80])
{
  if(!(*this).validExecution(user, 0)){
    cout<<"ls: Permission denied"<<endl;
    return ;
  }
  for(int i = 0; i <= subN - 1; i++)
  {
    if(strlen(command1) == 0)//if there no extra list option (-l)
    {
      cout << subDir[i]->name << " ";
    }//end if
    else if(strcmp(command1, "-l") == 0)// if -l included
    {//list all permission, time, and name of the representing directory
      (*subDir[i]->mask).printPermission();
      cout <<"     "<<subDir[i]->owner<<" ";
      (*(subDir[i])->time).printTime();
      cout << " " << subDir[i]->name << endl;
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
void Directory:: copy(char name1[80], char name2[80], char user[80])
{
  temp = new Directory(name1);
  for(int i = 0; i < subN; i++)
  {
    if((*temp) == (*subDir[i]))//if found match directory in current
    {

      if((*subDir[i]).validExecution(user, 0)){

	//create new directory with the name provided
	temp= new Directory(*subDir[i]);
	strcpy((*temp).name, name2 ); //rename the new directory
	strcpy((*temp).owner, user) ;
	subDir += temp;
	subN++;
	break;
      }
      else cout<<"cp: Permission denied"<<endl;
    }//end if
  }//end for
}//end copy()
void Directory:: changeOwner(char newOwner[80], char dirIn[80])
{
  int track=0;
  char *dir=strtok(dirIn, " ");
  while(dir){
    temp = new Directory(dir);
    for(int i = 0; i < subN && (*subDir[i])<(*temp); i++)
    {
      if((*temp) == (*subDir[i]))//if found match directory in current
      {
	(*subDir[i]->time).updateTime();
	strcpy((*subDir[i]).owner,newOwner);
	track =1;
	break;
      }//end if
    }
    if(track==0){
      cout<<"chown: failed to get attribute of '"<<dir
	  <<"' : No such file or directory"<<endl;
    }
    track = 0;
    dir=strtok(NULL," ");
  }
}

bool Directory:: validExecution(char user[80], int mode)
{
  (*mask).update();
  int p=(strcmp(user, owner)==0) ? (*mask).o : (*mask).u;  
  int track;
  switch(mode){
    case 0:
      track = (p < 4) ? 1:0;
      break;
    case 1:
      track = (p==0 || p==2) ? 1: 0;
      break;
    case 2:
      track = (p < 2) ? 1: 0;
      break;
    default:
      return false;
      break;
  }
  return (track==1)? true:false; 
}

