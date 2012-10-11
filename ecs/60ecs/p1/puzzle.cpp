#include "puzzle.h"

using namespace std;

puzzle::puzzle(int *in){

  cell *b[9], *r[9], *c[9];

  for(int i=0;i<9;i++){   //set row

    for(int j=0;j<9;j++){
      //int t=in[i*9+j];
      //cout<<(int)in[i*9+j]<<" ";
      subCell[i*9+j]=new cell(in[i*9+j]);
      r[j]=subCell[i*9+j];
    }
    //cout<<endl;
    rw[i]=new box(r);
  }
  for(int i=0;i<9;i++){   //set column

    for(int j=0;j<9;j++){

      c[j]=subCell[i+9*j];
    }
    clmn[i]=new box(c);
  }

  for(int i=0;i<3;i++){    //set box
    getbox(0+3*i, b, subCell);
    bx[0+i]=new box(b);

    getbox(27+3*i, b, subCell);
    bx[3+i]=new box(b);

    getbox(54+3*i, b, subCell);
    bx[6+i]=new box(b);
  }
  total=0;

}

puzzle::puzzle(puzzle &original){

  for(int i=0;i<81;i++){
    subCell[i]=original.subCell[i];
  }
  updatePuzzle();

}

int puzzle::eliminate(){

  for(int i=0;i<9;i++){
    bx[i]->remove();
    rw[i]->remove();
    clmn[i]->remove();
  }
  int t=total;
  total = 0;
  for(int i=0;i<9;i++){
    total+=bx[i]->contain.size();
  }
  return ((total-t)==0)?0:1;

}

int puzzle::fill(){

  int t=total;
  total=0;

  for(int i=0;i<9;i++){

    bx[i]->fill();
    rw[i]->fill();
    clmn[i]->fill();
  }
  for(int i=0;i<9;i++){
     total+=bx[i]->contain.size();
  }
  //cout<<total-t<<endl;
  return ((total-t)==0)?0:1;
}

void puzzle::getbox(int n, cell* in[9], cell* p[81]){

  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      in[i*3+j]=p[n+i*9+j];
    }
  }

}

int puzzle::getNum(puzzle* p){
  //int set=0;

  eliminate();
  for(unsigned int j=1;j<10;j++){
    for(int i=0;i<81;i++){
      //cout<<subCell[i]->remain.size()<<" "<<i<<" "<<j<<endl;
      if(subCell[i]->remain.size()==j){
	subCell[i]->solved=subCell[i]->guess=subCell[i]->remain.front();
	if(!subCell[i]->remain.empty()){
	  subCell[i]->remain.pop_front();
	  cout<<"solved:"<<subCell[i]->solved<<endl;
	  p->subCell[i]->removeCell(subCell[i]->solved);
	}
	for(int k=0;k<9;k++){
	  bx[i]->update();
	  rw[i]->update();
	  clmn[i]->update();
	}

	if(p->subCell[i]->remain.empty()) return -1;
	//cout<<"empty:"<<subCell[i]->solved<<" "<<p->subCell[i]->remain.front()<<endl;
	return i;
	  // subCell[i]->remain.empty();
      }
    }
  }
  return false;

}
void puzzle::getArray(int in[81]){

  //int ans[81];

  for(int i=0;i<81;i++){

    in[i]=subCell[i]->solved;
  }
  //return ptr;
}

bool puzzle::valid(){

  updatePuzzle();

  for(int i=0;i<9;i++){

    if(!bx[i]->valid()||(bx[i]->total)>45)return false;
    if(!rw[i]->valid()||(rw[i]->total)>45)return false;
    if(!clmn[i]->valid()||(clmn[i]->total)>45)return false;
  }
  validPuzzle=true;
  return true;



}

void puzzle:: updatePuzzle(){
  
  for(int i=0;i<9;i++){

    bx[i]->update();
    rw[i]->update();
    clmn[i]->update();
    //cout<<bx[i]->solved<<" "<<rw[i]->solved<<" "<<clmn[i]->solved<<" "<<endl;
  }
}








void puzzle::print(){

  cout<<endl;
  for(int i=0;i<9;i++){

    for(int j=0;j<9;j++){

      cout<<subCell[i*9+j]->solved<<" ";
    }
    cout<<endl;
  }

  cout<<endl;


  for(int i=0;i<9;i++){

    for(int j=0;j<9;j++){

      cout<<subCell[i*9+j]->remain.size()<<" ";
    }
    cout<<endl;
  }
  cout<<endl;

  for(int i=0;i<3;i++){

    for(int j=0;j<3;j++){

      cout<<bx[i*3+j]->contain.size()<<" ";
    }
    cout<<endl;
  }
  cout<<endl;

}
