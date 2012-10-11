//Wen Xi Zhang && Hiu Hong Yu
#include "directory.h"
#include <iomanip>
using namespace std;


//overloading constructor for read in data from directory.txt
//creating all the pervious directory that were created during last run
//use recurrsion, set default temp = NULL
Directory :: Directory(Directory &original) :File(*original.File::get()), temp(NULL)
{

  subN = original.subN;//set sub dir
  previousDir = original.previousDir;// perviousDirectry = new directory
  getPermissions().t=1;
  subDir=original.subDir;
  //scan for sub directory within the directory
}//end Directory(overloading constructor)

//overloading constructor for currectory directory
//creating root, set default temp to NULL
Directory :: Directory(Directory* currentDir, char name1[80],
                       char user[80]) : File(name1), temp(NULL)
{

  //creating new memory for directory and permission
  chown(user);
  subN = 0;//number of subdirectory = 0
  getPermissions().t=1;
  getPermissions().perm=(Permissions::umask<0)?22:Permissions::umask;
  if(currentDir){
    (*currentDir).subN++;//number of current directory + 1
    previousDir = currentDir;// set pervious directory to current
    (*currentDir).subDir += this;
    
  }
}//end Directory()

//overloaded constructor for only allocating memory
//set default temp to NULL
Directory :: Directory() :File(), temp(NULL)
{ 
  getPermissions().t=1;
}//end Directory(default constructor)


ofstream& Directory:: write (ofstream &out)
{


  out <<"0 ";
  out << showName() << " ";
  out << subN << " ";
  out << getPermissions();
  out << getTime();
  for(int i = 0; i < subN; i++)
  {
    out << *subDir[i];
  }//end for
  return out;
}//end << operator

//overloading operator << scan in
ifstream& operator >> (ifstream &in, Directory& dir)
{

  in >> dir.File::showName();
  in >> dir.subN;
  in >> dir.File::getPermissions();
  in >> dir.File::getTime();
  
  return in;
}//end overloading >> operator

//read in data from directory.txt
void Directory :: reconstructor(ifstream &in)
{
  int choice;
  while(!in.eof())//while not end of file, keep scanning
  {
    for(int track = 0; track < subN; track++)
    {
      //creat temp as new directory, it will create all sub directory and
      //directory recursively
      in>>choice;
      if(choice == 0){
	temp = new Directory();
	in >> *temp;
	(*temp).previousDir = this;
	(*temp).reconstructor(in);
	subDir += temp;// add temp to the subdirectory linklist
      }
      else{
	tempFile=new File();
	in>>(*tempFile);
	subDir += tempFile;
      }
    }//end for
    break;
  }//end while
}//end reconstructor

//check if valid permission were entered
//default paramater to tell if being called from umask or chmod
void Directory :: changePermissions(char name1[80], char user[80] ,
                                   int new_permission)
{

  //check if the directory trying to chmod to have to permission for the user
  //to do so, if not permission denied
  if(!(*this).validExecution(user, 0))
  {
    cout << "chmod: Permission denied" << endl;
    return ;
  }//end if
  
  int mode=0;
  char *in=strtok(name1, " ");
  while(in){
    //create new memory
    tempFile = new File(in);
   
    //scan tho the directory
    for(int i = 0; i < subN; i++)
    {
      if((*tempFile) == (*subDir[i]))//found match
      {
	//check valid change permission 
	if(!strcmp(user, (*subDir[i]).getPermissions().owner)==0
	   &&!(*((Directory*)subDir[i])).validExecution(user, 2))
	  {
	    cout << "chmod: Permission denied." << endl;
	    break;
	  }//end if
	//change the new permission to the directory
	(*subDir[i]).getPermissions().perm = new_permission;
	(*subDir[i]).getPermissions().update();
	(*subDir[i]).getTime().updateTime();//apply new time
	mode =1;
      }//end if
    }//end for
    if(mode==0) cout << "chmod: failed to get attributes of '" << in
		     << "': No such file or directory" << endl;
    in=strtok(NULL, " ");
    mode =0;
  }
}//end change permission

Directory* Directory :: validChange(char name1[80], char user[80])
{
  tempFile = new File(name1);
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
    //check valid permission to take action
    if(!((*this).validExecution(user, 0)))
    {
      cout << "cd : Permission denied." << endl;
      return this;
    }//end if
    //scan through the sub directory
    for(int i = 0; i < subN; i++)
    {
      if((*tempFile) == (*subDir[i]))//if found match
      {
        //check valid permission
	if((*subDir[i]).isFile()
	   ||!(*((Directory*)subDir[i])).validExecution(user, 1))
        {//if not
	  cout << "cd : Permission denied" << endl;
	  return this;
	}//end if
        return (*((Directory*)subDir[i])).get();
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
  tempFile = new File(name1);
  
  //scan through sub directory
  for(int i = 0; i < subN; i++)
  {
    if((*tempFile) == (*subDir[i]))
    {
      if(mode == 1)//permission with r-x, no permission to write
      {
        cout << "cp: cannot stat '" << name1 << "': No such file or directory" 
	      << endl;
      }//end if
      else
      {
          cout << "mkdir: cannot create directory '" << name1
               << "': File exists" << endl;
      }//end else
      
      return false;
    }//end if
  }//end else if
  if(!(*this).validExecution(user, 2)&&mode == 0)//error in prof code, change later
  {
    //permission with r-x
    cout << ((mode == 1) ? "cp: " : "mkdir: ") << "Permission denied." << endl;
    return false;
  }//end if
  return true;
}//end ValidCreate()

void Directory :: list(char command1[80], char user[80])
{
  if(!(*this).validExecution(user, 0))
  {
    //permission with r
    cout << "ls: Permission denied" << endl;
    return ;
  }//end if

  if(strlen(command1)>0 && strcmp(command1, "-l")!=0){
    cout<< "usage:ls [-l]"<<endl;
    return ;
  }
  int mode= (strlen(command1)>0)?1:0;
  
  for(int i = 0; i <= subN - 1; i++)
  {
    (*subDir[i]).getPermissions().update();
    (*subDir[i]).print(mode);
    
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
void Directory :: copy(char name1[80], char name2[80], char user[80])
{
  tempFile = new File(name1);
  for(int i = 0; i < subN; i++)
  {
    if((*tempFile) == (*subDir[i]))//if found match directory in current
    {
      if((*((Directory*)subDir[i])).validExecution(user, 0))
      {
	//create new directory with the name provided
	temp = new Directory(*((Directory*)subDir[i]));
	strcpy((*temp).showName(), name2 ); //rename the new directory
	strcpy((*temp).getPermissions().owner, user) ;
	subDir += temp;
	subN++;
	break;
      }//end if
      else 
        cout << "cp : Permission denied." << endl;
    }//end if
  }//end for
}//end copy()

void Directory :: changeOwner(char newOwner[80], char dirIn[80])
{
  int track = 0;
  char *dir = strtok(dirIn, " ");
  while(dir)//while directory set
  {
    tempFile = new File(dir);
    //scan tho all sub directory
    for(int i = 0; i < subN && (*subDir[i])<(*tempFile); i++)
    {
      if((*tempFile) == (*subDir[i]))//if found match directory in current
      {
	(*subDir[i]).getTime().updateTime();
	strcpy((*subDir[i]).getPermissions().owner, newOwner);//change the owner to new owner
	track = 1;//set track to set
	break;
      }//end if
    }//end for
    if(track == 0)//if no file were found
    {
      cout<< "chown: failed to get attribute of '" << dir
	  << "' : No such file or directory" << endl;
    }//end if
    track = 0;//set track back to 0
    dir = strtok(NULL, " ");//scan for next input, if there is/are andy
  }//end while
}//end changeOwner

bool Directory:: validExecution(char user[80], int mode)
{
  getPermissions().update();
  //check if owner and user are =, if true return mask.o, else mask.u
  //o = owner, u = user
  int p = (strcmp(user,getPermissions().owner) == 0) ?
    getPermissions().o : getPermissions().u;  
  int track;
  switch(mode)
  {
    case 0://check if permission with r
      track = (p < 4) ? 1 : 0;
      break;
    case 1://check if permission with r and x
      track = (p == 0 || p == 2) ? 1 : 0;
      break;
    case 2://check if permission with r and w
      track = (p < 2) ? 1 : 0;
      break;
    default://default false, if none of above match
      return false;
      break;
  }//end switch
  return (track == 1)? true : false; //return if track is 1 true
}//end validExecution
void Directory:: touch(char* fileName, char *user){

  int mode=0;
  char* in=strtok(fileName, " ");
  if(!validExecution(user, 2)){
    cout<<"touch: Permissions denied."<<endl;
    return ;
  }
  while(in){
    tempFile=new File(in);
    for(int i=0;i<subN;i++){

      if((*subDir[i])==(*tempFile)){

	(*subDir[i]).touch();
	mode=1;
	break;
      }
    }
    if(mode==0){
      tempFile= new File(in, (Permissions::umask<0)?111:Permissions::umask);
      strcpy((*tempFile).getPermissions().owner, user);
      subDir += tempFile;
      subN++;
    }
    mode=0;
    in=strtok(NULL, " ");
  }
}
    

