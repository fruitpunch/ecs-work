#include "tree.h"


using namespace std;

int character[256];
tNode *ptr[256];
llist l;

void decompress();
void compress();
void pack(char*, int);
string split(unsigned char);

void pack(char *in, int s){

  unsigned char out;
  int multiple;
  for(unsigned int i=0;i<s;){

    out=(unsigned char)0;
    multiple=1;

    for(int j=0;j<8 && i<s;j++){

      if(in[i]=='1'){
	out=out+multiple;
      }
      i++;
      multiple*=2;
    }
    cout.put(out);
  }

}
string split(unsigned char in){


  string out;
  int num=(int)in;

  for(int i=0;i<8;i++){
    
    if(num%2 == 1)out=out+'1';
    else out=out+'0';

    num/=2;
  }
  return out;

}



void compress(){

  string output;
  unsigned char in;
  char readIn;
  unsigned long int s=0, pos=0;
  
  while(!cin.eof() && cin.good()){
    in=cin.get();
    if(in!=255)character[(int)in]++;
  }

  for(int i=0;i<256;i++){

    ptr[i]=new tNode(i, character[i]);

    if(character[i]>0){
      l.push(ptr[i]);
    }
  }

  l.merge();

  string huf="HUFFMA1\0";
  cout<<huf;
  cout.put('\0');

  for(int i=0;i<256;i++){
    if(ptr[i]->freq>0){
      ptr[i]->findCode();
      s=s + ptr[i]->freq * ptr[i]->code.size();
    }
    ptr[i]->print();
  }
  char *o=new char[s];


  cin.clear();
  cin.seekg(0, ios::beg);
  int i=0;
  while(i<l.top()->freq){
    in=cin.get();
    if((int)in>-1) strcat(o, ptr[(int)in]->c);
    i++;
  }
  pack(o, s);
}

void decompress(){

  unsigned char in;
  tNode *tmp, *prev;
  string output;
  int sum, count=0;

  cin.ignore(9, '\0');

  for(int i=0;i<256;i++){
    sum=0;
    for(int j=0;j<4;j++){
      in=cin.get();
      sum+=in<<8*j;
    }
    character[i]=sum; 
  }
  for(int i=0;i<256;i++){
    
    ptr[i]=new tNode(i, character[i]);
    if(ptr[i]->freq > 0){
      l.push(ptr[i]);
    }
  }

  l.merge();
  for(int i=0;i<256;i++){
    if(ptr[i]->freq>0){
      ptr[i]->findCode();
      //cout<<i<<" "<<ptr[i]->freq<<endl;
    }
  }

  while(!cin.eof() && cin.good()){

    in = cin.get();
    output = output + split(in);
  }
  //cout<<output.size()<<endl;
  int size=output.size(), f=l.top()->freq;
  for(unsigned int i=0; size;){
    tmp=l.top();
    prev=NULL;
    while(tmp){
      prev=tmp;
      if(output[i]=='0')tmp=tmp->l;
      else tmp=tmp->r;

      i++;
    }
    i--;
    cout<<prev->key;
    count++;
    if(count==f)break;
  }
  


}


int main(int argc, char *argv[]){

  for(int i=0;i<256;i++)character[i]=0;


  if(argc!=2){
    compress();

  }
  else{
    if(strcmp(argv[1], "-d")==0) decompress();
    else cout<<"huffman: invalid option --'"<<argv[1][1]<<"'"<<endl
	     <<"Usage: huffman [-d]"<<endl;

  }
  return 0;
}
