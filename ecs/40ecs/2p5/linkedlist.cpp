#include "linkedlist.h"
#include "directory.h"

using namespace std;

linkedlist::linkedlist():head(NULL){}

void linkedlist :: operator += (Directory &rhs)
{
  Directory *ptr, *prev=NULL;
  ptr=head;
  for(ptr=head; ptr&&ptr->name<rhs.name;){
    prev=ptr;
    ptr=ptr->subDir;
  }
  if(!prev)head = &rhs;
  else prev->subDir=&rhs;
}
const Directory* linkedlist::operator [] (int index)const{
  
  Directory* ptr;
  ptr=head;
  for(int i=0;i<index;i++){
    ptr=ptr->subDir;
  }
  return ptr;
}
