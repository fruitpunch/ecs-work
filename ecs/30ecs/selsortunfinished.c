#include <stdio.h> 
#include <math.h>

#define NSIZE 20 

//

typedef struct {
  double real, imag;
} complex_t;
 
void swap_largest(complex_t *array[], int n, int max_index); 
void select_sort_rec(complex_t *array[], int n); 
int find_biggest(complex_t *array[], int n, int start, int curmax);

double abs_complex(complex_t c);  // Make this by modifying the book version
int scan_complex(FILE *fp,complex_t *c); //From the book (included) 
void print_complex(complex_t c); //From the book (included) 

int
main()
{
  complex_t *array[NSIZE];
  int size,  i;
  complex_t entry[NSIZE];
  complex_t cno;
  FILE *fp; 
  
  fp = fopen("cdata.txt", "r");
  size = 0;

  while(scan_complex(fp, &cno) == 1) {
    array[size]=malloc(sizeof(complex_t));
    array[size]->real=cno.real;
    array[size]->imag=cno.imag;
    size++;
  }
 
  printf("array before sorting  = \n"); 
    
  for(i=0;i<size;i++){
    print_complex(*array[i]);
  }

  printf("***end of array****\n");
 
  select_sort_rec(array, size); 

  printf("\narray after sorting   = \n"); 
 
 for(i=0;i<size;i++){
    print_complex(*array[i]);
  }  
  printf("***end of array****\n");
  fclose(fp); 
  return 0;
}


/* select_sort_rec
 *  Sorts n elements of an array of complex_numbers
 *  Pre:  n > 0 and first n elements of array are defined
 *  Post: array elements are in ascending order
 *  This function is RECURSIVE!!
 */
void select_sort_rec(complex_t *array[], int n)
{   
  int themax = 0; 

  if(n>=0){

    select_sort_rec(array, n-1);
  }
  return;
  // Hint: There are two intuitive ways of solving this problem: (1) Finding
  // the smallest number in the array, placing it at the front (via a swap), and 
  // then recursing on the remainder of the array; or (2), finding the largest 
  // element in the array, placing it at the back of the array (via a swap), 
  // and then recursing on the remainder of the array. This skeleton code assumes
  // a solution that uses the second approach!
}


/* swap_largest
 *  Before:  n > 0 and first n elements of array are defined
 *          the largest element (by abs value) is pointed to 
 *           by array[max_index]
 *  After: array[n-1] contains pointer to largest value, which
 *  is at position max_index. The value that used to be pointed
 * at Array[n-1] is now at Array[max_index]. 
 */
void swap_largest(complex_t *array[], int n,int max_index)
{
  // HINT: Got temp? 

  // This is a simple swap routine, and there is no need for recursion here!

  // FINISH THIS!!
}

int find_biggest(complex_t *array[], int n, int start, int curmax) {  

  if(start<n){
    if(abs_complex(*array[start])>abs_complex(*array[curmax])){
      curmax=start;
    }
    curmax=find_biggest(array, n, start+1, curmax);
  }
  return curmax;
}

int scan_complex(FILE *input, complex_t *c) 
{

  int status;

  status = fscanf(input,"%lf%lf", &c->real, &c->imag);
                  
  if (status == 2)
    status = 1;
  else if (status != EOF)
    status = 0;

  return (status);
}

void print_complex(complex_t c) /* input - complex number to display   */
{
  double a, b;
  char sign;

  a = c.real;
  b = c.imag;

  printf("(");

  if (fabs(a) < .005  &&  fabs(b) < .005) {
    printf("%.2f", 0.0);
  } else if (fabs(b) < .005) {
    printf("%.2f", a);
  } else if (fabs(a) < .005) {
    printf("%.2fi", b);
  } else {
    if (b < 0)
      sign = '-';
    else
      sign = '+';
    printf("%.2f %c %.2fi", a, sign, fabs(b));
  }

  printf(")\n");
}

double abs_complex(complex_t c)
{
  return sqrt(c.real * c.real + c.imag * c.imag);
}

