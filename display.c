#include <stdio.h>


void display(btreeNode *p)
{
    int i;
    for (i = 0; i < (p->n); i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if ((p->leaf) == 0)
        {
            display((p->children[i]));
        }
        printf("%d  ", p->keys[i]);
    }

    // Print the subtree rooted with last child
    if ((p->leaf) == 0)
        display((p->children[i]));
}

