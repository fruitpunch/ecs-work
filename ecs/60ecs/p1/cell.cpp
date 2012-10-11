#include "cell.h"

using namespace std;

cell::cell(int init){

  guess=0;

  if(init!=0){
    //remain.push_back(init);
    solved=init;
    left=1;
    return ;
  }
  for(int i=1;i<=9;i++){
    remain.push_back(i);
  }
  solved=init;
  left=remain.size();
}

cell::cell(cell &original){

  solved=original.solved;

  list<int>::iterator itr;
  for(itr=original.remain.begin();itr!=original.remain.end();itr++){
    remain.push_back(*itr);
  }

}
void cell::removeCell(int d){

  //cout<<solved<<" "<<remain.size()<<endl;

  if(solved) return ;

  list<int>::iterator itr;
  //cout<<"removing: "<<d<<endl;
  for(itr=remain.begin();itr!=remain.end();itr++){

    if(*itr==d){
      remain.erase(itr);
      if(remain.size()==1){
	solved=remain.front();
	remain.clear();
      }
      left--;
      break;
    }
  }
}
int cell::find(int f){
  if(solved||f==0) return 0;

  list<int>::iterator itr;

  for(itr=remain.begin();itr!=remain.end();itr++){

    if(*itr==f){
      //cout<<*itr;
      return *itr;
    }
  }
  return 0;
}

ofstream& operator <<(ofstream& out, cell& in){

  list<int>::iterator itr;

  for(itr=(in.remain).begin(); itr!=(in.remain).end();itr++){

    out<<*itr;
  }
  return out;
}
