#include "file.h"

using namespace std;

File::File(){
  name=new char[80];
  mask=new Permissions();
  time=new Time();
}

File::File(char name1[80], int p){
  name=new char[80];
  mask=new Permissions();
  time=new Time();
  if(name1==NULL){
    strcpy(name, "/");
    return ;
  }
  strcpy(name, name1);
  (*mask).perm=p;
  
  
}
File::File(File &original){
  name=new char[80];
  mask=new Permissions();
  time=new Time();
  strcpy(name, original.name);
  (*mask).perm =(*original.mask).perm;
  (*mask).t = (*original.mask).t;
  (*mask).owner =(*original.mask).owner;  
}
File::~File(){

  if(mask) delete mask;
  if(time) delete time;
  if(name) delete name;
}
ofstream& operator << (ofstream &out, File& file){

  return file.write(out);
}
ifstream& operator >>(ifstream &in, File& file){
  in>>file.name;
  in>>(*file.mask);
  in>>(*file.time);
  return in;
}
bool File :: operator < (File &rhs)
{
  //return the opposite result of if name and rhs.name is = or not
  return !(strcmp(name, rhs.name) > 0);
}//end operator <
bool File :: operator == (File &rhs){

  return strcmp(name, rhs.name)==0?true:false;
}
int File :: checkPermissions(){

  return (*mask).perm;
}
void File :: changePermissions(int p){

  (*mask).perm=p;
}
void File :: chown(const char* newOwner){

  if(!newOwner){
    strcpy((*mask).owner, "root");
    return ;
  }
  strcpy((*mask).owner, newOwner);
}
void File :: print(int mode){

  if(mode==0) cout << name<<" ";
  else{
    (*mask).printPermissions();
    cout<< " ";
    (*time).printTime();
    cout<< " "<< name << endl;
  }
}
void File :: rename(const char* newName){
  strcpy(name, newName);
}
char* File :: showName(){
  return name;
}
void File :: touch(){

  (*time).updateTime();
}
ofstream& File :: write(ofstream& out){

  out<<"1 ";
  out<<name<<" ";
  out<<(*mask);
  out<<(*time);
  return out;
}
Time& File ::getTime(){
  return *time;
}
Permissions& File :: getPermissions(){
  return *mask;
}
File* File:: get(){
  return this;
}
bool File:: isFile(){

  return (*mask).t==0?true:false;
  
}
