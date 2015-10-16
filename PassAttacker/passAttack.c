#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Struct definitions**********************************************************/

typedef struct NodeList{
    struct Node *head;
    int count;
} nodelist;

typedef struct Node{
    int level;
    char *pattern;
    int exhausted;
    struct Node *next;
} node;


/*Function declarations*******************************************************/

void create_children(int m, int n, int level, nodelist *parents, nodelist *children);
void add_node(int level, char *pattern, int exhausted, nodelist *list);
int check_exhausted(int m, int n, char *pattern);
int find_num_possible(int m, int n);
//int free_level(struct NodeList *list);


/*Main*************************************************************************/

int main(int argc, char **argv)
{
    //Read input list
    //Call find_num_possible for every input pair
    //print formated output for each test case

    find_num_possible(5, 3);

    return 0;
}


/*Node functions****************************************************************/

int find_num_possible(int m, int n)
{
    int i; 
    //Create the list of tree levels
    nodelist *nodetree = malloc( m * sizeof(nodelist) );

    //Initialize the first level (this is only 1/Nth of the actual tree!)
    nodetree->head = malloc( sizeof(node) );
    nodetree->head->level = 1;
    nodetree->head->pattern = "1";
    nodetree->head->exhausted = 0;
    nodetree->head->next = NULL;
    nodetree->count = 1;

    for(i = 1; i < m; i++){
        nodetree[i].head = malloc( sizeof(node) );
        nodetree[i].head = NULL;
        nodetree[i].count = 0;
    }

    //Loop for each level in the tree
    for(i = 0; i < m; i++){
        //create_children(nodetree[i], nodetree[i+1]);
        //printf("Level %d has %d nodes in it\n", i+1, nodetree[i].count);
    }

    create_children(m, n, 1, nodetree, nodetree+1);
    printf("parents has %d node(s), children has %d node(s)\n", nodetree[0].count, nodetree[1].count);

    return 0;
}



void create_children(int m, int n, int level, nodelist *parents, nodelist *children)
{
    //If node isn't exhausted, add N children to children list
    node *current;
    int i;
    char *childpattern;
    for(current = parents->head; current->next != NULL; current = current->next){
        if(!current->exhausted){
            //Generation children for each of N
            for(i = 0; i < n; i++){
                //Each child gets a new pattern with i at the end, and exhausted is checked
                childpattern = make_pattern(pattern, i);
                add_node(level, childpattern, check_exhausted(m, n, childpattern), children);
            }
        }else{
            for(i = 0; i < (n - (level - rindex)); i++){
                //Each child gets n - (level - rindex) children
                add_node(level, NULL, 1, children);
            }
        }
    }
}



void add_node(int level, char *pattern, int exhausted, nodelist *list)
{
    //Add a node to the beginning of the list of nodes for this level
    node *prevhead = list->head;

    node *newnode = malloc( sizeof(node) );
    newnode->level = level;
    newnode->pattern = pattern;
    newnode->exhausted = exhausted;
    newnode->next = (struct Node*)prevhead;

    list->head = (struct Node*)newnode;
    list->count++;
}


/**
 **Function: check_exhausted
 **Input: m, the length of the password; n, the # of unique values; pattern, seen so far
 **Description:
 **	This counts the number of repeats in the pattern seen so far, if that count is
 **	equal to rindex-1, then the branch is exhausted
 **Return: 0 if branch is not exhausted, 1 if branch is exhausted
 **/
int check_exhausted(int m, int n, char *pattern)
{
    int rindex = m - n + 1;
    int *array = calloc(sizeof(int), m);
    int rcount = 0;
    char c;
    int i;

    //Count the number each value appears
    for(i = 0, c = pattern[i]; c != '\0'; c = pattern[++i]){
        array[atoi(&c)]++; //increment for each value in pattern
    }

    printf("pattern: %s\n",pattern);
    //Count number of repeats for those values that show up at least once
    for(i = 0; i < m; i++ ){
        if(array[i] != 0) rcount += (array[i]-1);
       // printf("Array[%d] = %d, rcount = %d\n", i, array[i], rcount);
    }

    //rindex is the number of times a single value may repeat, rcount is the number
    //of repeats total (not first occurence).
    return rcount == (rindex - 1);
}
