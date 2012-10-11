#include "tree.h"


using namespace std;

unsigned int character[256];


void compress(){

  string input;
  int count=0;

  getline(cin, input);

  for(unsigned int i=0;i<input.size();i++){

    character[input[i]]++;
  }

  for(int i=0;i<256;i++){

    if(character[i]>0){
      count++;
    }
  }

  heap minHeap(count);
  node *ptr[count];

  for(int i=0;i<256;i++){

    ptr[i]=new node(i, character[i]);

    if(character[i]>0){
      minHeap.push(ptr[i]);
    }
  }
  for(int i=0;i<count; i++) ptr[i]->print();



}

void decompress(){}


int main(int argc, char *argv[]){

  for(int i=0;i<256;i++)character[i]=0;


  if(argc==2 && strcmp(argv[1], "-d")==0){


  }
  else compress();


  return 0;
}
