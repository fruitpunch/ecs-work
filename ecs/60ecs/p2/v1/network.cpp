#include "network.h"

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
node::node(road *inData, node *inNode){

  data=inData;
  next=inNode;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
road::road(int i1, int i2, int d, int i){

  if(i1<i2){
    c1=i1;
    c2=i2;
  }
  else{
    c1=i2;
    c2=i1;
  }
  distance=d;
  id=i;
  region=common=-1;
  adj=new llist();
}

int road::commonNode(road *in){
  
  if(in->c1==c1)return c1;
  else if(in->c1==c2)return c2;
  else if(in->c2==c1)return c1;
  else return c2;
}

bool road::checkDup(road *in){

  return ((in->c1==c1 && in->c2==c2)||(in->c1==c2 && in->c2==c1)) &&
    distance==in->distance;

}

bool road::checkAdj(road *in){

  return (in->c1==c1)||(in->c1==c2)||(in->c2==c1)||(in->c2==c2);
}

void road::print(){

  cout<<"<road>"<<c1<<" "<<c2<<" "<<distance<<"</road>"<<endl;
}

void road::insertRoad(road *in){

  adj->insert(in);
}

bool road::checkCycle(int prev){

  visited=true;

  if(adj->empty()) return true;

  return adj->visit(prev, id, this);


}

bool road::setRegion(int prev, int r){

  visited=true;
  region=r;
  if(adj->empty()) return true;

  return adj->setAdjRegion(prev, id, region, this);


}

void road::removeSelf(){

  adj->removeAll(id);

}

bool road::roadCmp(road *in){

  if(distance < in->distance) return true;
  else if(distance > in->distance) return false;
  else{
    if(c1 < in->c1) return true;
    else if(c1 > in->c1) return false;
    else{
      if(c2 < in->c2) return true;
      else return false;
    }
  }
}

  

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
llist::llist(){

  head=NULL;
  size=0;

}

bool llist::setCheck(road *in){

  if(in->c1==in->c2){
    cout<<"Found self loop."<<endl;
    return false;
  }


  node *ptr;
  ptr=head;

  while(ptr){

    if( ptr->data->checkDup(in) ){
      cout<<"Found duplicate road."<<endl;
      return false;
    }
    ptr=ptr->next;
  }

  insert(in);

  return true;
}

void llist::insert(road *in){

  node *ptr, *prev=NULL;
  ptr=head;

  while(ptr && ptr->data->roadCmp(in)){

    prev=ptr;
    ptr=ptr->next;
  }
  size++;
  if(!prev)head=new node(in, ptr);
  else prev->next=new node(in, ptr);


}

void llist::getAdj(road *in){

  node *ptr;
  ptr=head;

  while(ptr){
    
    if(ptr->data->checkAdj(in)){

      in->insertRoad(ptr->data);
      ptr->data->insertRoad(in);
    }

    ptr=ptr->next;
  }
}

void llist::remove(int d){

  node *ptr=head, *prev=NULL;
  bool found=false;


  if(d==-1){
    head=ptr->next;
    return ;
  }

  while(ptr){

    if(ptr->data->id==d){
      found=true;
      break;
    }
    prev=ptr;
    ptr=ptr->next;
  }
  if(!found)cout<<"wtf?"<<endl;
  else{

    if(!prev){
      head=ptr->next;
    }
    else{
      prev->next=ptr->next;
    }
    size--;
  }
}

bool llist::visit(int prev, int current, road *currentRoad){

  node *ptr;
  bool valid=true;
  ptr=head;
  while(valid&&ptr){

    if(ptr->data->id==prev){}
    else{

      currentRoad->common=currentRoad->commonNode(ptr->data);
      if((ptr->data->visited) && (currentRoad->common!=ptr->data->common))
	return false;
      if(currentRoad->common!=ptr->data->common)
	valid = ptr->data->checkCycle(current);
    }
    ptr=ptr->next;
  }

  return valid;
}
      
void llist::resetVisit(){

  node *ptr;
  ptr=head;

  while(ptr){
    ptr->data->visited=false;
    ptr->data->common=-1;
    ptr=ptr->next;
  }

}    

road* llist::top(){

  return head->data;
}  

void llist::clear(){
  head=NULL;
}

bool llist::empty(){

  return head==NULL;
}

void llist::removeAll(int id){

  node *ptr;
  ptr=head;

  while(ptr){
  
    ptr->data->adj->remove(id);
    ptr=ptr->next;
  }
}

void llist::printList(){

  node *ptr;
  ptr=head;

  while(ptr){

    ptr->data->print();

    ptr=ptr->next;
  }
}
int llist::setRegion(){

  node *ptr;
  ptr=head;
  int i=0;
  while(ptr){

    if(ptr->data->region == -1){
      ptr->data->setRegion(ptr->data->id ,i);
      i++;
    }
    ptr=ptr->next;
  }
  return i;
}

bool llist::setAdjRegion(int prev, int current, int r,road *currentRoad){

  node *ptr;
  bool valid=true;
  ptr=head;
  while(valid&&ptr){

    if(ptr->data->id==prev){}
    else{

      currentRoad->common=currentRoad->commonNode(ptr->data);

      if(currentRoad->common!=ptr->data->common)
	valid = ptr->data->setRegion(current, r);
    }
    ptr=ptr->next;
  }
  return valid;
}

void llist::setList(llist *in, int r){

  node *ptr;
  ptr=head;
  while(ptr){
    if(ptr->data->region==r){
      in->insert(ptr->data);
      remove(ptr->data->id);
    }
    ptr=ptr->next;
  }
}

bool llist::llistCmp(llist *in){

  if(size < in->size) return true;
  else if(size > in->size) return false;
  else{

    if(top()->c1 < in->top()->c1) return true;
    else return false;
  }
}
