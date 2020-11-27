//this file can contain the data structure definition
#include <stdio.h>
#include <string.h>

typedef struct btreeNode *btreePointer;

typedef struct
{
    int *keys;              //array of keys
    btreePointer *children; //array of pointers to children;

    int t;    //minimum degree(no. of keys that should be there)
    int n;    //current no. of keys in this node
    int leaf; //0 OR 1 : whether the node is a leaf or not

} btreeNode;

/*
void main()
{
    printf("Hello world!");
}
*/