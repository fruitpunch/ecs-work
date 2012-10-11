#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <stack>
#include <cstdlib>
#include<cstring>
#include "puzzle.h"


using namespace std;

list<puzzle*> aStack;
stack<puzzle*> pStack;
stack<puzzle*> save;

bool win(puzzle *p){
  p->updatePuzzle();
  if(p->valid()){
    for(int i=0; i<9;i++){

     
    if(!p->bx[i]->solved==1) return false;
    if(!p->rw[i]->solved==1) return false;
    if(!p->clmn[i]->solved==1) return false;
    }
  }
  else return false;

  aStack.push_back(p);
  save.push(p);

  return true;
}


bool solve(){
  int t=0;
  int array[81];
  bool run=true, valid=true, winn=false;

  while(run){


    puzzle* tmp;
    puzzle* del;

    
    if(!pStack.empty()){
      tmp=pStack.top();
      if(!tmp->valid()){
	valid = false;
	t=2;
      }
    }
    else{
      if(!winn) return false;
      else return true;
    }

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
	if(!pStack.empty()){
	  del=pStack.top();
	  pStack.pop();
	  if(!del)delete(del);
	}
	else return true;
	winn=valid=true;
	t=2;
	  
      }
      else t=2;
      break;
    
    case 2:
      int a;
      
      if(valid){
	if(winn){
	  
	  while(tmp->subCell[tmp->guess]->getRemain()==0){
	    //delete(pStack.top());
	    //pStack.pop();
	    del=pStack.top();
	    pStack.pop();
	    if(!del)delete(del);

	    if(!pStack.empty())tmp=pStack.top();
	    else return true;
	  }
	}
	tmp->getArray(array);
	puzzle* pzzl=new puzzle(array);
	pzzl->copy(tmp);
	a=(*pzzl).getNum(tmp);
	pStack.push(pzzl);
	t=0;
      }
      else{
	if(!pStack.empty()){
	  //delete(pStack.top());
	  //pStack.pop();
	  del=pStack.top();
	  pStack.pop();
	  if(!del)delete(del);
	  valid=true;
	}
	if(a==-1){
	  if(!pStack.empty()){
	    //delete(pStack.top());
	    //pStack.pop();
	    del=pStack.top();
	    pStack.pop();
	    if(!del)delete(del);
	    valid=true;
	  }
	}
      }
      break;
    }
  }
  return run;
}




int main(){
  
  char input[82];

  int p[81];
  int* ptr=p;
  cin.getline(input, 82);

  if(input[81]=='\n')cout<<input[82]<<endl;

  for(int i=0;i<81;i++){

    if(input[i]=='.'||(input[i]>'0'&&input[i]<='9')){
      p[i]=(input[i]=='.') ? 0 : input[i]-'0';
    }
    else{

      if(i<81)cout<<"ERROR: expected <value> got "<<input[i]<<endl;
    }
  }
 for(int i=0;i<81;i++){
   cout<<ptr[i];
 }
 cout<<endl;


    
  

  puzzle* mainPuzzle=new puzzle(ptr);
  pStack.push(mainPuzzle);
  if(solve()){
  
    while(!save.empty()){
      puzzle *out=save.top();

      for(int i=0;i<81;i++){
	cout<<out->subCell[i]->solved;
      
      }
      cout<<endl;
      save.pop();

    }
  }
  else cout<<"No solution!"<<endl;

  return 0;
}
