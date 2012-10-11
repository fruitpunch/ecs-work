//Wen Xi Zhang && Hiu Hong Yu
#include <cstdlib>
#include <iostream>
#include "funix.h"
using namespace std;

int main()
{
  //set funix pointer
  Funix* funix = new Funix();
  (*funix).run();// start running get command
  //free memory
  delete funix;
 
  return 0;
}//end main
