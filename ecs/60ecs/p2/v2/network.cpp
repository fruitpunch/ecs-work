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
heap::heap(int s){

  node* set[s];

  nodes=set;
  size=0;

}

bool heap::setCheck(road *in){

  if(in->c1==in->c2){
    cout<<"Found self loop."<<endl;
    return false;
  }

  for(int i=0;i<size;i++){

    if(nodes[i]->data->checkDup(in) ){
      cout<<"Found duplicate road."<<endl;
      return false;
    }
  }
  insert(in);

  return true;
}

void heap::insert(road *in){

  int currentNode = ++size;
  while(currentNode !=1 && nodes[currentNode/2]->data->roadCmp(in)){
    nodes[currentNode]=heap[currentNode/2];
    curretNode/=2;
  }
  nodes[currentNode]=in;
}

}

void heap::getAdj(road *in){

  node *ptr;
  ptr=head;

  for(int i=0;i<size;i++){
    
    if(nodes[i]->data->checkAdj(in)){

      in->insertRoad(nodes[i]->data);
      nodes[i]->data->insertRoad(in);
    }

  }
}

void heap::remove(int d){

  node *temp=nodes[size--];
  int currentNode=1;
  int child=2;
  while(child<=size){
    if(child<size && nodes[child]
    
}

bool heap::visit(int prev, int current, road *currentRoad){

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
      
void heap::resetVisit(){

  node *ptr;
  ptr=head;

  while(ptr){
    ptr->data->visited=false;
    ptr->data->common=-1;
    ptr=ptr->next;
  }

}    

road* heap::top(){

  return nodes[1]->data;
}  

void heap::clear(){
  head=NULL;
}

bool heap::empty(){

  return size==0;
}

void heap::removeAll(int id){

  node *ptr;
  ptr=head;

  while(ptr){
  
    ptr->data->adj->remove(id);
    ptr=ptr->next;
  }
}

void heap::printHeap(){

  node *ptr;
  ptr=head;

  while(ptr){

    ptr->data->print();

    ptr=ptr->next;
  }
}
int heap::setRegion(){

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

bool heap::setAdjRegion(int prev, int current, int r,road *currentRoad){

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

void heap::setList(heap *in, int r){

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

bool heap::heapCmp(heap *in){

  if(size < in->size) return true;
  else if(size > in->size) return false;
  else{

    if(top()->c1 < in->top()->c1) return true;
    else return false;
  }
}
