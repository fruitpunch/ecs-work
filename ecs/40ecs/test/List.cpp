#include "List.h"
#include "ln.h"
#include <cstdlib>

#pragma once

void List::insert(int d){

  ListNode *ptr, *prev=NULL;
  ptr=head;
  for(ptr=head;ptr&&ptr->data<d;ptr=ptr->next){
    prev=ptr;
  }
  if(!prev){
    head=new ListNode(d, ptr);
  }
  else prev->next=new ListNode(d, ptr);
}
