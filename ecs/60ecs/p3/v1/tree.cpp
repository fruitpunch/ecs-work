#include "tree.h"

using namespace std;

node::node(int character, int frequency){

  key=smallest=character;
  freq=frequency;
  l=r=NULL;
  leaf=true;

}
node::node(node *one, node *two){

  if(one->cmp(two)){
    l=one;
    r=two;
  }
  else{
    l=two;
    r=one;
  }
  freq=l->freq +  r->freq;
  leaf=false;
  smallest=l->smallest;

}

bool node::cmp(node *in){

  if(freq < in->freq) return true;
  else if(freq > in->freq) return false;
  else{
    if(smallest < in->smallest) return true;
  }
  return false;
}
  

void node::print(){

  cout<<key<<" "<<key-0<<" "<<freq<<endl;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

heap::heap(int s){
  cout<<s<<endl;
  size=0;
  node *ptr[s+1];
  nodes=ptr;
}

void heap::push(node *in){
  cout<<"push"<<endl;
  int currentNode= ++size;
  while(currentNode!=1 && nodes[currentNode/2]->cmp(in)){

    nodes[currentNode]=nodes[currentNode/2];
    currentNode/=2;
  }
  nodes[currentNode]=in;
}
