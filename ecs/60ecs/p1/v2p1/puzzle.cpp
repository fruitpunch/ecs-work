#include "puzzle.h"

using namespace std;

puzzle::puzzle(int *in){

  cell *b[9], *r[9], *c[9];

  for(int i=0;i<9;i++){   //set row

    for(int j=0;j<9;j++){

      subCell[i*9+j]=new cell(in[i*9+j]);
      r[j]=subCell[i*9+j];
      //cout<<subCell[i*9+j]->solved<<" ";
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
    updatePuzzle();
    rw[i]->remove();
    updatePuzzle();
    clmn[i]->remove();
    updatePuzzle();
    
  }
  int t=total;
  total = 0;
  for(int i=0;i<9;i++){
    total+=bx[i]->getContain();
  }
  return ((total-t)==0)?0:1;

}

int puzzle::fill(){

  int t=total;
  total=0;

  for(int i=0;i<9;i++){

    bx[i]->fill();
    updatePuzzle();
    rw[i]->fill();
    updatePuzzle();
    clmn[i]->fill();
    updatePuzzle();
  }
  for(int i=0;i<9;i++){
    total+=bx[i]->getContain();
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
  for(int j=1;j<10;j++){
    for(int i=0;i<81;i++){
      //cout<<subCell[i]->remain.size()<<" "<<i<<" "<<j<<endl;
      if(subCell[i]->getRemain()==j){
	subCell[i]->solved=subCell[i]->guess=subCell[i]->front();
	p->subCell[i]->guess=1;
	if(!subCell[i]->getRemain()==0){
	  subCell[i]->front(subCell[i]->solved);
	  //cout<<"solved:"<<subCell[i]->solved<<endl;
	  p->subCell[i]->removeCell(subCell[i]->solved);
	}
	updatePuzzle();

	if(p->subCell[i]->getRemain()==0) return -1;
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
  //cout<<"get array"<<endl;
  for(int i=0;i<81;i++){

    in[i]=subCell[i]->solved;
    //cout<<in[i]<<" ";
  }
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
  updatePuzzle();
  for(int i=0;i<9;i++){

    for(int j=0;j<9;j++){

      cout<<subCell[i*9+j]->solved<<" ";
    }
    cout<<endl;
  }

  cout<<endl;


  for(int i=0;i<9;i++){

    for(int j=0;j<9;j++){

      cout<<subCell[i*9+j]->getRemain()<<" ";
    }
    cout<<endl;
  }
  cout<<endl;

  for(int i=0;i<3;i++){

    for(int j=0;j<3;j++){

      cout<<bx[i*3+j]->getContain()<<" ";
    }
    cout<<endl;
  }
  cout<<endl;

}
int getSize(int in[9]){
  int count=0;
  for(int i=0;i<9;i++){
    if(in[9]>0)count++;
  }
  return count;
}
