#include <stdio.h>

int main(void){
  int a,b,c;
  scanf("%d %d %d", &a,&b,&c);

  if(((a>=b)&&(c>=a))||((a>=c)&&(b>=a)))printf("a\n");

  return 0;
}
