#include <stdio.h>
#include <stdlib.h>

void pass_func(int level, int m, int n, int* array);

long int count = 0, finalCount = 0;
int repeats = 0;

int main(int argc, char **argv)
{
    //FILE *inp;
    //inp = fopen("~/A-large-practice.in", "r");

    int m = 15, n = 15, i = 0;

    int *array = calloc(n, sizeof(int));

    pass_func(0, m, n, array);
    for(i = 0; i < n; i++){
        finalCount = (finalCount + count) % 1000000007L;
    }
    printf("m:%d, n:%d, count: %ld\n", m, n, finalCount);

    return 0;
}

void pass_func(int level, int m, int n, int*array)
{
    if(level == 0){ //Only do 1/nth of the tree.
        array[0]++;
        pass_func(level + 1, m, n, array);
    }

    if (level == m){
        count = (count + 1) % 1000000007L;
    }else{
        int i;
        for(i = 0; i < n; i++){
            if(repeats < m-n){
                if (array[i] != 0) repeats++; //If the # is repeat
                array[i]++;
                pass_func(level+1, m, n, array);
                array[i]--;
                if (array[i] != 0) repeats--; //If the # was a repeat
            }else{
                if(array[i] == 0){
                    array[i]++;
                    pass_func(level+1, m, n, array);
                    array[i]--;
                }
            }
        }
    }
}
