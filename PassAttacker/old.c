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
    int *pattern;
    int exhausted;
    struct Node *next;
} node;


/*Function declarations*******************************************************/

void create_children(int m, int n, int level, nodelist *parents, nodelist *children);
void add_node(int level, int *pattern, int exhausted, nodelist *list);
int check_exhausted(int m, int n, int *pattern);
int find_num_possible(int m, int n);
//int free_level(struct NodeList *list);


/*Main*************************************************************************/

int main(int argc, char **argv)
{
    //Read input list
    //Call find_num_possible for every input pair
    //print formated output for each test case

//    fopen("~/C-Algorithms/PassAttacker/a_input.in", "r");

    find_num_possible(1,1);
    find_num_possible(4,3);
    find_num_possible(5,5);
    find_num_possible(7,7);
    find_num_possible(7,4);
    find_num_possible(4,4);
    find_num_possible(6,6);
    find_num_possible(7,1);
    find_num_possible(2,1);
    find_num_possible(6,1);
    find_num_possible(4,2);
    find_num_possible(5,1);
    find_num_possible(7,6);
    find_num_possible(5,5);
    find_num_possible(4,3);


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
    nodetree->head->pattern = calloc( n, sizeof(int) ); //n size array of ints
    nodetree->head->pattern[0] = 1;
    nodetree->head->exhausted = (m == n) ? 1 : 0;
    nodetree->head->next = NULL;
    nodetree->count = 1;

    for(i = 1; i < m; i++){
        nodetree[i].head = malloc( sizeof(node) );
        nodetree[i].head = NULL;
        nodetree[i].count = 0;
    }

    //Loop for each level in the tree
    for(i = 0; i < m; i++){
        create_children(m, n, i+1, nodetree+i, nodetree+i+1);
        //printf("Level %d has %d nodes in it\n", i+1, nodetree[i].count*n);
    }
    printf("%d, %d: %d\n", m, n, nodetree[i-1].count*n);

//    create_children(m, n, 1, nodetree, nodetree+1);
//    printf("parents has %d node(s), children has %d node(s)\n", nodetree[0].count, nodetree[1].count);
//    create_children(m, n, 2, nodetree+1, nodetree+2);
//    printf("parents has %d node(s), children has %d node(s)\n", nodetree[1].count, nodetree[2].count);

    return 0;
}


/**
 **Function: create_children
 **Inputs: m, size of input; n, number of values; level, the three depth;
 **	   parents, a list of the parent nodes; children, list of child nodes
 **Description:
 **	create_children generates children for every parent on a certain tree level
 **	for parents that aren't exhausted, it generates N children and sequentially
 **	increments the appropriate location in their pattern
 **	add_node is called to add the node.
 **/
void create_children(int m, int n, int level, nodelist *parents, nodelist *children)
{
    //If node isn't exhausted, add N children to children list
    node *current;
    int i, rindex = m - n + 1;
    int *childpattern;
    int childlevel = level + 1;
    for(current = parents->head; current != NULL; current = current->next){
        if(!current->exhausted){
            //Generation children for each of N
            for(i = 0; i < n; i++){
                //Each child pattern gets alloc'd, incremented properly, exhausted is checked
                childpattern = calloc( n, sizeof(int) );
                memcpy(childpattern, current->pattern, n*sizeof(int));
                childpattern[i]++;
                add_node(childlevel, childpattern, check_exhausted(m, n, childpattern), children);
            }
        }else{
            for(i = 0; i < (n - (childlevel - rindex)); i++){
                //Each child gets n - (theirlevel - rindex) children
                add_node(childlevel, NULL, 1, children);
            }
        }
    }
}


/**
 **Function: add_node
 **Input: level, the tree depth; pattern, the counts of values; 
 **	  exhausted, 0/1 for not exhausted/exhausted; list of nodes
 **Description:
 **	add_node takes the inputs given to it and creates a node on 
 **	the tree list with those values
 **/
void add_node(int level, int *pattern, int exhausted, nodelist *list)
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


/*Helper functions********************************************************************/

/**
 **Function: check_exhausted
 **Input: m, the length of the password; n, the # of unique values; pattern, counts
 **Description:
 **	This counts the number of repeats in the pattern seen so far, if that count is
 **	equal to rindex-1, then the branch is exhausted
 **Return: 0 if branch is not exhausted, 1 if branch is exhausted
 **/
int check_exhausted(int m, int n, int *pattern)
{
    int rindex = m - n + 1;
    int rcount = 0;
    int i;

    //Count number of repeats for those values that show up at least once
    for(i = 0; i < n; i++ ){
        if(pattern[i] != 0) rcount += (pattern[i]-1);
        //printf("[%d]:%d, ",i, pattern[i]);
    }

    //rindex is the number of times a single value may repeat, rcount is the number
    //of repeats total (not first occurence).
   // printf("exhausted: %d, ", rcount == (rindex - 1));
    return rcount == (rindex - 1);
}
