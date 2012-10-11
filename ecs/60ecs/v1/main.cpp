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
  int array[81];
  bool run=true, valid=true, winn=false;
  puzzle* tmp;
  puzzle* pzzl;
  puzzle* del;

  while(run){

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
	  
	  while(tmp->guess!=-1 && tmp->subCell[tmp->guess]->getRemain()==0){
	    del=pStack.top();
	    pStack.pop();
	    if(!del)delete(del);
	    if(!pStack.empty())tmp=pStack.top();
	    else return true;
	  }
	}
	tmp->getArray(array);
	pzzl=new puzzle(array);
	pzzl->copy(tmp);
	a=(*pzzl).getNum(tmp);
	pStack.push(pzzl);
	t=0;
      }
      else{
	if(!pStack.empty()){
	  del=pStack.top();
	  pStack.pop();
	  if(!del)delete(del);
	  valid=true;
	}
	if(a==-1){
	  if(!pStack.empty()){
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
					<<input<<endl;
      
      else if(i<81&&input=='\n') cout<<"ERROR: expected <value> got \\n"
				     <<endl;

      else{

	if((int)input<=15) cout<<"ERROR: expected <value> got \\x0"
			       <<hex<<(int)input<<endl;
	else cout<<"ERROR: expected <value> got \\x"
		 <<hex<<(int)input<<endl;
      }

      return 0;
    }

  }
  input=cin.get();
  if(input!='\n'){
    if(isprint(input)) 
      cout<<"ERROR: expected \\n got "<<input<<endl;

    else if((int)input>=0 && (int)input <=127)
      cout<<"ERROR: expected \\n got \\x"<<hex<<(int)input<<endl;

    else
      cout<<"ERROR: expected \\n got <eof>" << endl;

    return 0;
  }
  input=cin.peek();
  if(input && !cin.eof()){
    if(isprint(input)) 
      cout<<"ERROR: expected <eof> got "<<input<<endl;

    else if(input=='\n')
      cout<<"ERROR: expected <eof> got \\n"<<endl;

    else{
      
      if((int)input<=15) cout<<"ERROR: expected <value> got \\x0"
			     <<hex<<(int)input<<endl;
      else cout<<"ERROR: expected <value> got \\x"
	       <<hex<<(int)input<<endl;
    }


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
  else cout<<"No solution!"<<endl;

  return 0;
}
