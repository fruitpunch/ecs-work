#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <stack>
#include <cstdlib>
#include "puzzle.h"


using namespace std;

stack<puzzle*> pStack;
puzzle* mainPuzzle;
puzzle* working;
int depth=0;

bool win(puzzle *p){
  int d;
  (*p).updatePuzzle();
  if(p->valid()){
    //p->print();
    for(int i=0; i<9;i++){
    
      // cout<<p->bx[i]->solved<<" "<<p->rw[i]->solved
      //  <<" "<<p->clmn[i]->solved<<" "<<i<<endl;
     
    if(!p->bx[i]->solved==1) return false;
    if(!p->rw[i]->solved==1) return false;
    if(!p->clmn[i]->solved==1) return false;
    }
  }
  else return false;
  // cin>>d;
  p->print();
  cout<<"win"<<endl;
  exit (1);
  return true;
}


bool solve(){
  depth++;
  int t=0;
  int array[81];
  bool run=true;
  puzzle* tmp=pStack.top();
  tmp->getArray(array);
  puzzle* pzzl=new puzzle(array);
  pzzl=tmp;
  cout<<"push d:"<<depth<<endl;
  pStack.push(pzzl);
  int u;
  while(run){

    pzzl->print();
    
    cin>>u;

    switch(t){

    case 0:
      t=(pzzl->eliminate()==1)?0:1;
      
      if(!pzzl->valid()){
	cout<<"invalid"<<endl;
	pStack.pop();
	run=false;
      }
      break;

    case 1:
      t=(pzzl->fill()==1)?0:2;
      if(!pzzl->valid()){
	cout<<"invalid"<<endl;
	pStack.pop();
	run=false;
      }
      break;

    case 2:
      cout<<"test"<<endl;
      pzzl->print();
      if(win(pzzl)){
	run=false;
      }
      else t=3;
      pStack.pop();
      break;
    
    case 3:
      cout<<"before"<<endl;
      tmp->print();
      int a=(*pzzl).getNum(tmp);
      cout<<"after"<<endl;
      tmp->print();
      //pStack.push(pzzl);
      cout<<"push"<<endl;
      //pzzl->print();
      bool b=solve();
      cout<<"A:"<<a<<" B:"<<b<<endl;
      if(b==0){

	if(a==-1){
	  cout<<"end reached"<<endl;
	  pStack.pop();
	  run=false;
	}
	else{
	  pzzl=tmp;
	  pStack.push(pzzl);
	  t=3;
	}
	
      }

      //cout<<run<<endl;
      break;
    }
    //cout<<run<<endl;
  }
  depth--;
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

  mainPuzzle=new puzzle(ptr);
  pStack.push(mainPuzzle);
  try{
    solve();
  }
  catch(...){

    working->print();
  }
    

  return 0;
}
