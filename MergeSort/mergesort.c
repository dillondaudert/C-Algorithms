#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SENTINEL 2147483647 //Maximum value for a 32 bit integer as a sentinel value

void merge_sort(int **A, int p, int r);
void merge(int **A, int p, int q, int r);

int main(int argc, char **argv)
{
  int a_length = argc-1; //1 less as argc includes the name of function
  int *array = malloc(a_length * sizeof *array); 
  int i = 0;
  for(i; i < a_length; i++){
    array[i] = atoi(argv[i+1]);
  }
  
  merge_sort(&array,0,a_length-1); //send the length-1 as r needs to be the last index
  i = 0;
  for(i; i < a_length; i++){
    printf("%d, ",array[i]);
  }
  printf("\n");
  return 0;
}


/**
* merge_sort takes an array of integers and splits it in half recursively. Each half is
* sorted by the merge function. p and r should both be index values found within the array
*/
void merge_sort(int ** A, int p, int r)
{
  int q;
  if (p < r){
    q = (p + r) / 2; //Rounds down
    merge_sort(A, p, q);
    merge_sort(A, q+1, r);
    merge(A, p, q, r);
  }
}

void merge(int ** A, int p, int q, int r)
{
  //Get the lengths of both halves of the array
  int n_one = q - p+1;
  int n_two = r - q;
  
  //Create two new arrays of these lengths to copy into, size+1 for sentinel value
  int * L = malloc(n_one+1 * sizeof *L); 
  int * R = malloc(n_two+1 * sizeof *R);
  
  //Copy array halves into new arrays, add sentinels at ends
  int i = 0, j = 0;
  for(i; i < n_one; i++){
    L[i] = *((*A)+p+i);
  }
  for(j; j < n_two; j++){
    R[j] = *((*A)+q+j+1);
  }
  L[n_one] = SENTINEL;
  R[n_two] = SENTINEL;
  
  i = j = 0; //reset to 0
  
  int k = p;
  
  //Now sort left and right sides back into original array (A)
  for(k; k < r + 1; k++){ //< r + 1 because r is the index of the last element
    if(L[i] <= R[j]){
      *((*A)+k) = L[i];
      i++;
    }else{
      *((*A)+k) = R[j];
      j++;
    }
  }
  
  free(L);
  free(R);
}
