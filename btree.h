//this file can contain the data structure definition
#include <stdio.h>
#include <string.h>
#define M 2
//typedef struct btreeNode *btreePointer;

typedef struct _node
{
    int keys[(2 * M) - 1];         //array of keys
    struct _node *children[2 * M]; //array of POINTERS children;

    //const int t;    //minimum degree(no. of keys that should be there)
    int n;          //current no. of keys in this node
    short int leaf; //0 OR 1 : whether the node is a leaf or not

} btreeNode;

