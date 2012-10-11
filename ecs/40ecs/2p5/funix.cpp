//Hiu Hong Yu && Wen Xi Zhang
#include "funix.h"
#include "permission.h"
#include "directory.h"
#include "Time.h"
using namespace std;

//funix root constructor
//when funix() was called, default root directory will be created
Funix :: Funix() : currentDir(new Directory(NULL, NULL, 755))
{
  umask = 0;//default mask value
  //open up directories.txt if it exist
  ifstream infile("a.txt", ios::in);
  infile >> (*this);//read in the file to this, current directory
  //recreate the directory/file that were created during last run recursivly,
  //if directories.txt is empty, nothing will be create
  (*currentDir).reconstructor(infile);
  infile.close();//close file
}//end funix()

Funix::~Funix()
{
  if(currentDir != NULL)//if current directory exist
  {
    delete currentDir;// delete the memory of current directory
  }//end if
}//end destructor ~Funix()

//overloading << operator
ofstream& operator << (ofstream& out, const Funix& fn)
{
  out << (*fn.currentDir);//calls directory overloaded operator
  return out;
}//end << operator

//overloading >> operator
ifstream& operator >> (ifstream& in, Funix& fn)
{
  in >> (*fn.currentDir);//calls directory overloaded operator
  return in;
}//end >> operator

void Funix :: cd(char name1[80], char extra[80])
{
  //check for extra input(directory name)
  if(strlen(extra) > 0 || strlen(name1) == 0)
  {
    cout << "usage: cd directoryName\n";
    return;
  }//end if
  //set current directory to the directory going to
  currentDir = (*currentDir).validChange(name1);
}//end cd()

int Funix :: eXit(char extra[80])
{
  //check for extra input
  if(strlen(extra) > 0)
  {  
    cout << "usage: exit\n";
    return 0;
  }//end if	
  return 1;
}//end exit

void Funix :: writePrompt()
{
  int i = 0, j;
  char path[100][80];
  Directory *temp = currentDir;
  strcpy(path[1], "");

  //print out the address of the directory
  while(1)
  {
    strcpy(path[i], (*temp).name);
    //if the perviousdir not = null, save name to array
    if((*temp).previousDir != NULL)
    {
      temp = (*temp).previousDir;
    }//end if
    else break;
    i++;
  }//end while

  for(j = i; j >= 0; j--)
  {
    if(j == i)
    {
      cout << "/";
    }//end if
    else 
      cout << path[j] << "/";
  }//end for
  cout << " # ";
}//end writeprompt
 
void Funix :: getCommand(char command1[80], char command2[80], 
                         char command3[80], char command4[80])
{
  unsigned int i, c1 = 0, t = 0;
  char input[80], commandF1[80] = "\0", commandF2[80] = "\0", 
    commandF3[80] = "\0", commandF4[80]="\0";
  //command1 = function being call, command2 = name of things being call for function, 
  //command3 = anything extra
		
  cin.getline(input, 79); //store input command into array

  //sort out user input command
  for(i = 0; i < strlen(input); i++)
  {
    if(input[i] == ' ')
    {  
      c1++;
      t = i + 1;
      if(input[i-1] == ' ' || i == 0)
      {
        c1--;
      }//end if
    }//end if
    if(input[i] == '\0')
    {
      break;
    }//end if
    
    if(input[i] != ' ' && c1 == 0)
    {  
      commandF1[i-t] = input[i];
    }//end if
    
    if(input[i] != ' ' && c1 == 1)
    {    
      commandF2[i-t] = input[i];
    }//end if
    
    if(input[i] != ' ' && c1 == 2)
    {  
      commandF3[i-t] = input[i];
    }//end if
    if(input[i] != ' ' && c1 == 3)
    {
      commandF4[i-t] = input[i];
    }
  }//end for
  //copy back to array and return to run()
  strcpy(command1, commandF1);
  strcpy(command2, commandF2);
  strcpy(command3, commandF3);
  strcpy(command4, commandF4);
}//end getcommand

void Funix :: ls(char command1[80], char extra[80])
{
  if(strlen(extra) > 0 || (strcmp(command1,"-l") != 0 && strlen(command1) > 0))
    {
      cout << "usage: ls [-l]\n";
      return ;
    }//end if
  (*currentDir).list(command1);
}//end ls

void Funix :: mkdir(char name1[80], char extra[80])
{   
  //check for extra input
  if(strlen(extra) > 0 || strlen(name1) == 0)
  {  
    cout << "usage: mkdir directory_name\n";
    return ;
  }//end if
  //check if the input correct, if correct make dir, else print out error
  //if file already exist, print out error message
  if((*currentDir).validCreate(name1))
  {
    (*currentDir->time).updateTime();
    new Directory(currentDir, name1, umask);
  }//end if
}//end mkdir

void Funix :: setUmask(char command1[80], char extra[80])
{
  //check for extra input
  if(strlen(extra) > 0 || strlen(command1) == 0)
  {   
    cout << "usage: umask octal\n";
    return ;
  }//end if
  
  //check if number range is valid
  if((*currentDir).validPermission(command1, 1))
  {
    umask = atoi(command1);		
  }//end if
}//end umask

void Funix :: chmod(char p[80], char name1[80], char extra[80])
{
  if(strlen(extra) > 0 || strlen(p) == 0 || strlen(name1) == 0)
  {   
    if(strlen(extra) > 0)
    {
      cout << "chmod: failed to get atrributes of '" << extra 
           << ": No such file or directory" << endl;
      return ;
    }//end if
    else
    {
      cout<<"chmod: too few arguements"<<endl;
    }//end else
    return ;
  }//end if

  if((*currentDir).validPermission(p))//if enter valid mask value
  {
    //change the file/directory mask vaule to new one
    (*currentDir).changePermission(name1, 777 - atoi(p));
  }//end if
}//end chmod()

//copy function
void Funix :: cp(char name1[80], char name2[80], char extra[80])
{
  if(strlen(extra) > 0)
  {
      cout << " cp: too many arguements" << endl;
      return ;
  }//end if
  if(strlen(name2) == 0)
  {
    cout << "cp: missing destination file" << endl;
    return ;
  }//end if
  if(strlen(name1) == 0)
  {
    cout << "cp: missing file arguements" << endl;
    return ;
  }//end if
  if(strcmp(name1, name2) == 0)
  {
      cout << "cp: '" << name1 << "' and '" << name2 
           << "' are the same file" << endl;
      return ;
  }//end if
  //if enter all command correctly
  if((*currentDir).validCreate(name2, 1))
  {
    (*currentDir).copy(name1, name2);
  }//end if
}//end cp()

int Funix :: processCommand(char command1[80])
{
  int i;
  //all command choice
  char const *commands[] = {"cd", "exit", "ls", "mkdir",
                            "umask","chmod","cp", "unknownInput"};
  for(i = 0; i <= 7; i++)
  {
    if(strcmp(command1, commands[i]) == 0)
    {
      break;
    }//end if
  }//end for
  return i;
}//end processCommand

void Funix :: run()
{
  // declear command array && variable
  //
  int exit = 0;
  char command1[80] = "\0", command2[80] = "\0",
       command3[80] = "\0", command4[80]="\0";
 
  //while loop, run program until the word exit was entered
  //
  while(1)
  {  
    writePrompt();// print out current directory address
    getCommand(command1, command2, command3, command4);//get command that user want to do    
    //process command that were entered
    //
    switch(processCommand(command1))
    {  
      case 0:
        cd(command2, command3);// change directory
        break;
      case 1:
        if(eXit(command2))
        {
          exit = 1;// exit
        }//end if
        break;
      case 2:
        ls(command2, command3);// list all file in the directory
        break;
      case 3:
        mkdir(command2, command3);// make directory
        break;
      case 4:
        setUmask(command2, command3);// umask
        break;
      case 5:
        chmod(command2, command3, command4);
      	break;
      case 6:
        cp(command2, command3, command4);
        break;
      default:// anything else
        if(strcmp(command1,"") == 0)
        {
        }//end if
   	 else
        {					
          cout << command1 << ": Command not found.\n";
        }//end else
        break;
    }//end switch
    if(exit ==  1)
    {
      //while exit command, print all data to directory.txt
      while((*currentDir).previousDir != NULL)//goes back to root 1st.
      {
        currentDir = (*currentDir).previousDir;
      }//end while
      ofstream outfile("a.txt", ios :: out);//open directory.txt
      outfile << (*this);//write everything thing to it recursively
      outfile.close();//close it
      break;
    }//end if
  }// end while
}//end run
