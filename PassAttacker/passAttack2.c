#include <stdio.h>
#include <stdlib.h>

void pass_func(int level, int m, int n, int* array);

int count = 0;

int main(int argc, char **argv)
{
    int m = 7, n = 4;
    int *array = calloc(n, sizeof(int));
    
    pass_func(1, m, n, array);
    printf("m:%d, n:%d, count: %d\n", m, n, count);

    return 0;
}

void pass_func(int level, int m, int n, int*array)
{
    if (level >= m){
        count+=1;
    }else{
        int i;
        for(i = 0; i < n; i++){
            if(array[i] < m-n+1){
                array[i]++;
                pass_func(level+1, m, n, array);
                array[i]--;
            }
        }
    }
}
