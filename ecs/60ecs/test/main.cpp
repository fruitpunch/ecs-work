#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <stack>
#include <cstdlib>
#include<cstring>
#include "puzzle.h"


using namespace std;

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

  save.push(p);

  return true;
}


bool solve(){
  int t=0;
  char g;
  int array[81];
  bool run=true, valid=true, winn=false;

  while(run){

    puzzle* tmp;

    if(!pStack.empty()){
      tmp=pStack.top();
      tmp->eliminate();
      if(!tmp->valid()){
	valid = false;
	t=2;
      }
      else{
	valid=true;
      }
    }
    else{
      if(!winn) return false;
      else return true;
    }

    switch(t){

    case 0:
      tmp->eliminate();
      t=1;
      break;

    case 1:
      if(win(tmp)){
	if(!pStack.empty())pStack.pop();
	else return true;
	winn=valid=true;	  
      }
      t=2;
      break;
    
    case 2:
      int a;
      
      if(valid){
	if(winn){
	  while(tmp->guess!=-1 && tmp->subCell[tmp->guess]->getRemain()==0){

	    if(!pStack.empty())pStack.pop();
	    else return true;
	    if(!pStack.empty())tmp=pStack.top();
	    else return true;
	  }
	}

	tmp->getArray(array);
	puzzle* pzzl=new puzzle(array);
	pzzl->copy(tmp);
	a=(*pzzl).getNum(tmp);
	//cin>>g;
	pStack.push(pzzl);
	//t=0;
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
	}
      }
      t=0;
      break;
    }
  }
  return run;
}

int main(){
  
  char input;
  int p[81];
  int* ptr=p;

  for(int i=0;i<81;i++){

    input=cin.get();
    if(input=='.'||(input>'0'&&input<='9')){
      p[i]=(input=='.') ? 0 : input-'0';
    }
    else{

      if(cin.eof())cout<<"ERROR: expected <value> got <eof>\n";

      else if(isprint(input)&&i<81) cout<<"ERROR: expected <value> got "
				      <<input<<"\n";
      
      else if(i<81&&input=='\n') cout<<"ERROR: expected <value> got \\n"
					<<"\n";

      else{

	if((int)input<=9) cout<<"ERROR: expected <value> got \\x0"
				 <<hex<<(int)input<<"\n";
	else cout<<"ERROR: expected <value> got \\x"
		 <<hex<<(int)input<<"\n";
      }

      return 0;
    }

  }
  input=cin.get();
  if(input!='\n'){
    if(isprint(input)) 
      cout<<"ERROR: expected \\n got "<<input<<"\n";

    else if((int)input>=0 && (int)input <=127)
      cout<<"ERROR: expected <value> got \\x"<<hex<<(int)input<<"\n";

    else
      cout<<"ERROR: expected \\n got <eof>" << "\n";

    return 0;
  }

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
  else cout<<"No solution!\n";

  return 0;
}
