#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define A_LENGTH 6

void findMaxSub(int* A, int length, int* retval);


int main(int argc, char** argv)
{
    //initialize random seed
    srand(time(NULL)) ;

    int A[A_LENGTH];
    int index;
    for(index = 0; index < A_LENGTH; index++){
        //Assign a random number
        A[index] = (rand() - (RAND_MAX / 2)) % 50;
        printf("%d ", A[index]);
    }
    printf("\n");

    int values[3];

    findMaxSub(A, A_LENGTH, values);

    printf("The max subarray is: A[%d..%d], sum: %d\n", values[0], values[1], values[2]);

    return 0;

}


void findMaxSub(int* A, int length, int* retval)
{
    int max_left = 0, max_right = 0, max_left_here = 0;
    int max_sum = A[0], max_ending_here = A[0];
    int index;

    for(index = 1; index < length; index++){
        if( A[index] < max_ending_here + A[index] ){
            max_ending_here = max_ending_here + A[index];
        }else{
            max_left_here = index;
            max_ending_here = A[index];
        }
     
        if( max_ending_here < max_sum ){
            //Do nothing
        }else{
            max_sum = max_ending_here;
            max_left = max_left_here;
            max_right = index;
        }
    }
    retval[0] = max_left;
    retval[1] = max_right;
    retval[2] = max_sum;
}
