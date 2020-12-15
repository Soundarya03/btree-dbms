#include <stdio.h>
//#include "btree.h"

void display(btreeNode *p)
{
    int i;
    printf("Display function reached\n");
    for (i = 0; i < (p->n); i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if ((p->leaf) == 0)
        {
            display((p->children[i]));
        }
        printf("%d ", p->keys[i]);
    }

    // Print the subtree rooted with last child
    if ((p->leaf) == 0)
        display((p->children[i]));
}

/*void main()
{
    //printf("Hello world!");
}*/