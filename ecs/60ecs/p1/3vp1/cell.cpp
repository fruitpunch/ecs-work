#include "cell.h"

using namespace std;

cell::cell(int init){

  guess=0;
  //cout<<init<<" ";
  for(int i=0;i<9;i++){
    remain[i]=0;
  }
  if(init!=0){
    solved=init;
  }
  else{
    for(int i=0; i<=9;i++){
      remain[i]=i+1;
    }
    solved=0;
  }

}

void cell::copy(cell *original){

  solved=original->solved;

  for(int i=0;i<9;i++)remain[i]=original->remain[i];

}
void cell::removeCell(int d){

  //cout<<solved<<" "<<remain.size()<<endl;

  if(solved) return ;

  //cout<<"removing: "<<d<<endl;
  for(int i=0;i<9;i++){

    if(remain[i]==d){
      remain[i]=0;
      break;
    }
  }
  if(guess!=0) return ;
  int count=0, track;
  for(int i=0;i<9;i++){
    if(remain[i]!=0){
      track=i;
      count++;
      if(count>1)break;
    }
  }
  if(count==1){
    //cout<<remain[track]<<endl;
    solved=remain[track];
    remain[track]=0;
  }
    
}
int cell::find(int f){
  if(solved||f==0) return 0;


  for(int i=0;i<9;i++){

    if(remain[i]==f){
      //cout<<*itr;
      return remain[i];
    }
  }
  return 0;
}
int cell::getRemain(){
  int count=0;
  for(int i=0;i<9;i++){

    if(remain[i]>0)count++;
  }
  return count;
}
void cell::clear(){
  for(int i=0;i<9;i++)remain[i]=0;
}
int cell::front(int f){
  if(!f){
    for(int i=0;i<9;i++){
      if(remain[i]>0)return remain[i];
    }
  }
  else{
    remain[f-1]=0;
  }
  return 0;
}
