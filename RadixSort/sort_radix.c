#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 20

void sort_radix(int level, int *bucket, int b_size);

long int input[INPUT_SIZE];
int result_index = 0;
long int result[INPUT_SIZE];

int main(int argc, char **argv)
{
    srand48(8505716009L); //Initialize PRNG
    int i;
    int *bucket_init = malloc(sizeof(int) * INPUT_SIZE);
    //printf("Size of long int: %d\n2^31: %ld\n", (int)sizeof(long int), (long int)1<<31);
    for(i = 0; i < INPUT_SIZE; i++){
        input[i] = lrand48();
        printf("%d: %ld\n", i, input[i]);
        bucket_init[i] = i;
        //int level_offset_val = 1<<(sizeof(long int)*8 - 1 - i);
        //printf("%d\n",  level_offset_val);
    }
    
    sort_radix(0, bucket_init, INPUT_SIZE);

    for(i = 0; i < INPUT_SIZE-1; i++){
        printf("%ld, ", result[i]);
    }
    printf("%ld\n", result[i]);
    free(bucket_init);

    return 0;
}

void sort_radix(int level, int *bucket, int b_size)
{
    int level_offset = 31 - level; //Integers from lrand48 are in the inteveral (0, 2^31)
    if(level_offset < 0) return;

    int *zero_bucket = malloc(sizeof(int) * b_size);
    int *one_bucket = malloc(sizeof(int) * b_size);
    int zero_b_size = 0, one_b_size = 0;
    int i;
    for(i = 0; i < b_size; i++){
        if(input[bucket[i]] & (1 << level_offset)){
            //The ones bucket
            one_bucket[one_b_size] = bucket[i];
            one_b_size += 1;
        }
        else{
            zero_bucket[zero_b_size] = bucket[i];
            zero_b_size += 1;
        }
    }
    
    if(zero_b_size > 1) {
        sort_radix(level+1, zero_bucket, zero_b_size);
    }else if(zero_b_size == 1){
        result[result_index++] = input[zero_bucket[0]];
        printf("Added zero bucket's only value %ld to result index %d\n", input[zero_bucket[0]], result_index-1);
    }
    if(one_b_size > 1){
        sort_radix(level+1, one_bucket, one_b_size);
    }else if(one_b_size == 1){
        result[result_index++] = input[one_bucket[0]];
        printf("Added one bucket's only value %ld to result index %d\n", input[one_bucket[0]], result_index-1);
    }
    free(zero_bucket);
    free(one_bucket);
}
