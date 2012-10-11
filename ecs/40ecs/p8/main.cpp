#include "SVector.h"
using namespace std;

int main(int argc, char *argv[]){


  ifstream infile(argv[1], ios::in);
  SVector<int> *sv;
  try{
    int size, index;
    string indicies, input, indexStr;
    stringstream g;
    infile>>size;
    sv=new SVector<int>(size);
    while(getline(infile, input)){
      string :: iterator itr;
      itr=input.begin();
      indicies="";
      indexStr="";
      try{
	if(*itr=='U'){

	  bool track=true;
	  for(itr++; itr!=input.end(); itr++){

	    if(track && *itr==' '){}
	    else if(track && isdigit(*itr)){
	      indexStr=indexStr+*itr;
	    }
	    else{
	      track=false;
	      indicies=indicies+*itr;
	    }
	  
	  }
	  index=atoi(indexStr.c_str());
	  (*sv).push_back(indicies, index);

	  
	}
	if(*itr=='A'){

	  for(itr++; itr!=input.end(); itr++){
	    indicies=indicies+*itr;
	  }

	  cout<<"Access value: "<<(*sv)[indicies]<<endl;
	}
	if(*itr=='O'){
	  (*sv).pop_back();
	}
      }
      catch(exception& e){
	cout<<e.what()<<endl;
      }

    }


  }
  catch(exception& e){

    cout<<e.what()<<endl;

  }

  return 0;
}
