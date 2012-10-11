#include "holder.h"
using namespace std;

box::box(cell* in[9]){

  total=0;
  solved=1;
  for(int i=0;i<9;i++) missing[i]=i+1;
  for(int i=0;i<9;i++){

    subCell[i]=in[i];
    //cout<<subCell[i]->solved<<" ";

    if(!subCell[i]->solved) solved = 0;
    if(subCell[i]->solved){
      contain[subCell[i]->solved -1]=subCell[i]->solved;
      missing[subCell[i]->solved -1]=0;
      total+=subCell[i]->solved;
    }
    
  }
  //cout<<endl;
  if(total==45) solved=1;
}

void box::remove(int d){

  //if(solved) return ;

  if(d!=0){

    for(int i=0; i<9; i++){
      if(contain[i]>0) subCell[d]->removeCell(contain[i]);
    }
    return ;
  }
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(contain[i]!=0)subCell[j]->removeCell(contain[i]);
    }
  }
  update();
  
}

void box::update(){

  //if(solved) return ;

  for(int i=0;i<9;i++){
    missing[i]=i+1;
    contain[i]=0;
  }
  int total=0;
  //cout<<"wtf? ";
  for(int i=0;i<9;i++){
    if(subCell[i]->solved){
      contain[subCell[i]->solved -1]=subCell[i]->solved;
      missing[subCell[i]->solved -1]=0;
      total+=subCell[i]->solved;
    }
  }
  //for(int i=0;i<9;i++)cout<<missing[i]<<" ";
  //cout<<endl;

  if(total==45) solved = 1;
  //cout<<"last thing"<<endl;

}

void box::fill(){

  //if(solved) return ;
  update();
  list<cell*> track;
  total=0;
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){      

      if(subCell[j]->find(missing[i])){
	track.push_back(subCell[j]);
	if(track.size()>1) break;
      } 
    }
    if(track.size()==1){
      track.front()->solved=i+1;
      update();
    }
    track.clear();
  }

  update();

  if(getContain()==8){
    for(int i=0; i<9;i++){
      if(subCell[i]->solved==0){

	for(int j=0;j<9;j++){
	  if(missing[j]>0)subCell[i]->solved=missing[j];
	  missing[j]=0;
	  contain[missing[j]]=0;
	}
	subCell[i]->clear();
	break;
      }
    }
  }
  update();
}

bool box::valid(){

  int check[]={0,0,0,0,0,0,0,0,0};

  update();

  for(int i=0;i<9;i++){
    if(subCell[i]->solved){
      check[subCell[i]->solved -1]++;
    }
  }
  //cout<<"check:";
  for(int i=0;i<9;i++){
    //cout<<check[i]<<" ";
    if(check[i]>1){
      cout<<"problem invalid"<<endl;
      return false;
    }
  }
  //cout<<endl;
   
  return true;
}
int box::getContain(){
  int count=0;
  for(int i=0;i<9;i++){
    if(contain[i]!=0)count++;
  }
  return count;
}
