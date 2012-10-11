#include "holder.h"
using namespace std;

box::box(cell* in[9]){

  total=0;
  solved=1;
  for(int i=0;i<9;i++){

    subCell[i]=in[i];
    if(!subCell[i]->solved) solved = 0;
    if(subCell[i]->solved){
      contain[subCell[i]->solved -1]=subCell[i]->solved;
      total+=subCell[i]->solved;
    }
    
  }
  if(total==45) solved=1;
}


void box::remove(int d){

  if(solved) return;

  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(contain[i]!=0)subCell[j]->removeCell(contain[i]);
    }
  }
  
}

void box::update(){

  if(solved) return ;
  for(int i=0;i<9;i++){
    contain[i]=0;
  }
  int total=0;
  for(int i=0;i<9;i++){
    if(subCell[i]->solved){
      contain[subCell[i]->solved -1]=subCell[i]->solved;
      total+=subCell[i]->solved;
    }
  }

  if(total==45) solved = 1;

}

bool box::valid(){

  int check[]={0,0,0,0,0,0,0,0,0};


  for(int i=0;i<9;i++){
    if(subCell[i]->solved){
      check[subCell[i]->solved -1]++;
    }
  }

  for(int i=0;i<9;i++){

    if(check[i]>1) return false;
  }
   
  return true;
}
int box::getContain(){
  int count=0;
  for(int i=0;i<9;i++){
    if(contain[i]!=0)count++;
  }
  return count;
}
