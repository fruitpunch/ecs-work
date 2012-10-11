#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <stack>
#include <cstdlib>
#include "puzzle.h"


using namespace std;

stack<puzzle*> aStack;
stack<puzzle*> pStack;
list<puzzle*> save;

bool win(puzzle *p){
  char d;
  p->updatePuzzle();
  if(p->valid()){
    for(int i=0; i<9;i++){

     
    if(!p->bx[i]->solved==1) return false;
    if(!p->rw[i]->solved==1) return false;
    if(!p->clmn[i]->solved==1) return false;
    }
  }
  else return false;

  //int array[81];
  //p->getArray(array);
  aStack.push(p);

  cout<<"win"<<endl;
  save.clear();
  p->print();
  while(!pStack.empty()){
    save.push_front(pStack.top());
    //save.front()->print();
    pStack.pop();
  }
  cout<<save.size()<<endl;    
  cin>>d;  
  return true;
}


bool solve(){
  int t=0;
  int array[81];
  bool run=true, valid=true, winn=false;

  int u;
  while(run){


    puzzle* tmp;
    if(!pStack.empty()){
      tmp=pStack.top();
      if(!tmp->valid()){
	valid = false;
	t=2;
      }
    }
    else{
      if(!winn)return false;
      else{
	if(save.empty()) return true;
	else{
	  tmp=save.front();
	  pStack.push(tmp);
	  save.pop_front();
	  valid=true;
	  t=2;
	}
      }	  
    }
    //cin>>u;
    //tmp->print();

    switch(t){

    case 0:
      t=((*tmp).eliminate()==1)?0:1;
      
      if(!tmp->valid()){
	valid=false;
	t=2;
      }
      else valid=true;
      break;


    case 1:
      if(win(tmp)){
	winn=valid=true;
	tmp=save.front();
	pStack.push(tmp);
	t=2;
	  
      }
      else t=2;
      break;
    
    case 2:
      int a;
      
      if(valid){
	tmp->getArray(array);
	puzzle* pzzl=new puzzle(array);
	pzzl->copy(tmp);
	a=(*pzzl).getNum(tmp);
	pStack.push(pzzl);
	t=0;
      }
      else{
	if(!pStack.empty()){
	  pStack.pop();
	  valid=true;
	}
	if(a==-1){
	  if(!pStack.empty()){
	    pStack.pop();
	    valid=true;
	  }
	  else run=false;
	}
      }
      break;
    }
  }
  return run;
}


int main(){
  
  char getF[20];

  char input[82];

  int p[81];
  int* ptr=p;
  cin.getline(getF, 82);

  ifstream infile(getF, ios::in); 
  infile.getline(input, 82);
  for(int i=0;i<81;i++){

    if(input[i]!='.'&&(input[i]<'1'||input[i]>'9')){
      cout<<"error"<<endl;
      return 0;
    }
    p[i]=(input[i]=='.') ? 0 : input[i]-'0';
    
  }

  puzzle* mainPuzzle=new puzzle(ptr);
  pStack.push(mainPuzzle);
  if(!solve())cout<<"no solution"<<endl;
  while(!aStack.empty()){
    puzzle *out=aStack.top();

    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
	cout<<out->subCell[i*9+j]->solved<<" ";
      }
      cout<<endl;
    }
    aStack.pop();
  }

  return 0;
}
