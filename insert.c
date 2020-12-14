#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// A utility function to split the child of this node
// Note that child must be full when this function is called
void splitChild(btreeNode *node, int i, btreeNode *child)
{
    printf("inside splitChild\n");
    // Create a new node which is going to store (t-1) keys
    // of child
    btreeNode *z = (btreeNode *)malloc(sizeof(btreeNode));
    z->leaf = (*child).leaf;
    z->n = M;

    // Copy the last (t-1) keys of child to z
    for (int j = 0; j < M; j++)
        z->keys[j] = (*child).keys[j + M];

    // Copy the last t children of child to z
    if ((*child).leaf == 0)
    {
        for (int j = 0; j < M; j++)
            z->children[j] = (*child).children[j + M];
    }

    // Reduce the number of keys in child
    (*child).n = M - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = (*node).n; j >= i + 1; j--)
        (*node).children[j + 1] = (*node).children[j];

    // Link the new child to this node
    ((*node).children[i + 1]) = (z);

    // A key of child will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = ((*node).n) - 1; j >= i; j--)
        (*node).keys[j + 1] = (*node).keys[j];

    // Copy the middle key of child to this node
    (*node).keys[i] = (*child).keys[M - 1];

    // Increment count of keys in this node
    ((*node).n)++;
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void insertNonFull(btreeNode *node, int k)
{
    printf("inside insertNonFull\n");
    // Initialize index as index of rightmost element
    int i = (*node).n - 1;

    // If this is a leaf node
    if ((*node).leaf == 1)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && (*node).keys[i] > k)
        {
            (*node).keys[i + 1] = (*node).keys[i];
            i--;
        }

        // Insert the new key at found location
        (*node).keys[i + 1] = k;
        ((*node).n)++;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && (*node).keys[i] > k)
            i--;

        // See if the found child is full
        if (((node)->children[i + 1])->n == 2 * M - 1)
        {
            // If the child is full, then split it
            splitChild(node, i + 1, ((*node).children[i + 1]));

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if ((*node).keys[i + 1] < k)
                i++;
        }
        insertNonFull((*node).children[i + 1], k);
    }
}

void insert(btreeNode *root, int k)
{
    printf("inside insert - ");
    /*
    // If tree is empty
    if (!(*root))
    {
        // Allocate memory for root
        
    }*/

    // If root is full, then tree grows in height
    if ((*root).n == M)
    {
        printf("inside the if\n");
        // Allocate memory for new root
        btreeNode *s;
        s = (btreeNode *)malloc(sizeof(btreeNode));
        if (!s)
            printf("memory allocation NOT successful\n");
        printf("malloc done successfully\n");

        s->n = 1;
        printf("n assigned\n");
        s->leaf = 0; //not a leaf, obviously

        // Make old root as child of new root
        s->children[0] = (root);
        printf("stops here\n");
        // Split the old root and move 1 key to the new root
        splitChild(s, 0, (root));

        // New root has two children now.  Decide which of the
        // two children is going to have new key
        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->children[i], k);

        // Change root
        (root) = s;
    }
    else // If root is not full, call insertNonFull for root
        insertNonFull(root, k);
}

/*
void main()
{
    //printf("Hello world!");
}
*/
