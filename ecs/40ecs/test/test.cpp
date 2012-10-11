#include <cstring>
#include <iostream>
#include "ln.h"

using namespace std;

int main(){

  char a[80]="\0", b[80]="\0";
  cout<<"1:"<<endl;
  cin>>a;
  cout<<"2:"<<endl;
  cin>>b;
  cout<<strcmp(a,b)<<endl;
  return 0;
}
