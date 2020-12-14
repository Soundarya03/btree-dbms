#include <stdio.h>
//#include "btree.h"

void display(btreeNode *p)
{
    int i;
    if ((p->n) == 1)
    {
        printf("Tree empty\n");
        return;
    }

    for (i = 0; i < (p->n) - 1; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!(p->leaf))
            display((p->children[i]));
        printf("%d ", p->keys[i]);
    }

    // Print the subtree rooted with last child
    if (!(p->leaf))
        display((p->children[i]));
}

/*void main()
{
    //printf("Hello world!");
}*/