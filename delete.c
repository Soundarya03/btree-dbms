
// A function that returns the index of the first key that is greater
// or equal to k

int findKey(int k, btreeNode *node);

// A wrapper function to remove the key k in subtree rooted with
// this node.
void removeFromNode(int k, btreeNode *node);

// A function to remove the index-th key from this node - which is a leaf node
void removeFromLeaf(int index, btreeNode *node);

// A function to remove the index-th key from this node - which is a non-leaf node
void removeFromNonLeaf(int index, btreeNode *node);

// A function to get predecessor of keys[index]
int getPred(int index, btreeNode *p);

// A function to get the successor of the key- where the key
// is present in the index-th position in the node
int getSucc(int index, btreeNode *p);

// A function to fill child children[idx] which has less than t-1 keys
void fill(int index, btreeNode *node);

// A function to borrow a key from children[index-1] and insert it
// into children[index]
void borrowFromPrev(int index, btreeNode *node);

// A function to borrow a key from the children[index+1] and place
// it in children[index]
void borrowFromNext(int index, btreeNode *node);

// A function to merge children[index] with children[index+1]
// children[idx+1] is freed after merging
void merge(int index, btreeNode *node);

//Initially called to remove a key
void removeKey(btreeNode *root, int k);

// A utility function that returns the index of the first key that is
// greater than or equal to k
int findKey(int k, btreeNode *node)
{
    btreeNode *p = node;
    int index = 0;
    while (index < p->n && p->keys[index] < k)
    {
        ++index;
    }
    return index;
}

// A function to remove the key k from the sub-tree rooted with this node
void removeFromNode(int k, btreeNode *node)
{
    int index = findKey(k, node);
    btreeNode *p = node;

    // The key to be removed is present in this node
    if (index < p->n && p->keys[index] == k)
    {
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (p->leaf)
            removeFromLeaf(index, p);
        else
            removeFromNonLeaf(index, p);
    }
    else
    {
        // If this node is a leaf node, then the key is not present in tree
        if (p->leaf)
        {
            printf("The key %d is not present in the tree\n", k);
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        int flag = ((index == p->n) ? 1 : 0);

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (p->children[index]->n < M)
            fill(index, p);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (index-1)th child. Else, we recurse on the
        // (index)th child which now has atleast t keys
        if (flag && index > p->n)
            removeFromNode(k, (p->children[index - 1]));
        else
            removeFromNode(k, (p->children[index]));
    }
    return;
}

// A function to remove the index-th key from this node - which is a leaf node
void removeFromLeaf(int index, btreeNode *node)
{
    btreeNode *p = node;

    // Move all the keys after the idx-th pos one place backward
    for (int i = index + 1; i < p->n; ++i)
        p->keys[i - 1] = p->keys[i];

    // Reduce the count of keys
    int x = p->n;
    p->n = x - 1;

    return;
}

// A function to remove the index-th key from this node - which is a non-leaf node
void removeFromNonLeaf(int index, btreeNode *node)
{
    btreeNode *p = node;

    int k = p->keys[index];

    // If the child that precedes k (children[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // children[idx]. Replace k by pred. Recursively delete pred
    // in children[index]
    if (p->children[index]->n >= M)
    {
        int pred = getPred(index, p);
        p->keys[index] = pred;
        removeFromNode(pred, (p->children[index]));
    }

    // If the child children[index] has less that t keys, examine children[index+1].
    // If children[index+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at children[index+1]
    // Replace k by succ
    // Recursively delete succ in children[index+1]
    else if (p->children[index + 1]->n >= M)
    {
        int succ = getSucc(index, p);
        p->keys[index] = succ;
        removeFromNode(succ, (p->children[index + 1]));
    }

    // If both children[index] and children[index+1] has less that t keys,merge k and all of children[index+1]
    // into children[index]
    // Now children[index] contains 2t-1 keys
    // Free children[index+1] and recursively delete k from children[index]
    else
    {
        merge(index, p);
        removeFromNode(k, (p->children[index]));
    }
    return;
}

// A function to get predecessor of keys[index]
int getPred(int index, btreeNode *p)
{
    btreeNode *cur = (p->children[index]);

    // Keep moving to the right most node until we reach a leaf
    while (!(cur->leaf))
        cur = (cur->children[cur->n]);

    // Return the last key of the leaf
    return cur->keys[cur->n - 1];
}

// A function to get the successor of the key- where the key
// is present in the index-th position in the node
int getSucc(int index, btreeNode *p)
{
    btreeNode *cur = (p->children[index + 1]);

    // Keep moving the left most node starting from children[index+1] until we reach a leaf
    while (!(cur->leaf))
        cur = (cur->children[0]);

    // Return the first key of the leaf
    return cur->keys[0];
}

// A function to fill child children[idx] which has less than t-1 keys
void fill(int index, btreeNode *node)
{
    btreeNode *p = node;

    // If the previous child(children[index-1]) has more than t-1 keys, borrow a key
    // from that child
    if (index != 0 && p->children[index - 1]->n >= M)
        borrowFromPrev(index, p);

    // If the next child(children[index+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (index != p->n && p->children[index + 1]->n >= M)
        borrowFromNext(index, p);

    // Merge children[index] with its sibling
    // If children[index] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (index != p->n)
            merge(index, p);
        else
            merge(index - 1, p);
    }
    return;
}

// A function to borrow a key from children[index-1] and insert it
// into children[index]
void borrowFromPrev(int index, btreeNode *node)
{
    btreeNode *p = node;
    btreeNode *child = (p->children[index]);
    btreeNode *sibling = (p->children[index - 1]);

    // The last key from children[index-1] goes up to the parent and key[index-1]
    // from parent is inserted as the first key in children[index]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in children[index] one step ahead
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    // If children[index] is not a leaf, move all its child pointers one step ahead
    if (!(child->leaf))
    {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    // Setting child's first key equal to keys[index-1] from the current node
    child->keys[0] = p->keys[index - 1];

    // Moving sibling's last child as children[index]'s first child
    if (!(child->leaf))
        child->children[0] = sibling->children[sibling->n];

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    p->keys[index - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to borrow a key from the children[index+1] and place
// it in children[index]
void borrowFromNext(int index, btreeNode *node)
{
    btreeNode *p = node;
    btreeNode *child = (p->children[index]);
    btreeNode *sibling = (p->children[index + 1]);

    // keys[index] is inserted as the last key in children[index]
    child->keys[(child->n)] = p->keys[index];

    // Sibling's first child is inserted as the last child
    // into children[index]
    if (!(child->leaf))
        child->children[(child->n) + 1] = sibling->children[0];

    //The first key from sibling is inserted into keys[index]
    p->keys[index] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    // Moving the child pointers one step behind
    if (!(sibling->leaf))
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    // Increasing and decreasing the key count of children[index] and children[index+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to merge children[index] with children[index+1]
// children[idx+1] is freed after merging
void merge(int index, btreeNode *node)
{
    btreeNode *p = node;
    btreeNode *child = (p->children[index]);
    btreeNode *sibling = (p->children[index + 1]);

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of children[index]
    child->keys[M - 1] = p->keys[index];

    // Copying the keys from children[index+1] to children[index] at the end
    for (int i = 0; i < sibling->n; ++i)
        child->keys[M + i] = sibling->keys[i];

    // Copying the child pointers from children[index+1] to children[index]
    if (!(child->leaf))
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[M + i] = sibling->children[i]; //?? Check the logic
    }

    // Moving all keys after index in the current node one step before -
    // to fill the gap created by moving keys[index] to children[index]
    for (int i = index + 1; i < p->n; ++i)
        p->keys[i - 1] = p->keys[i];

    // Moving the child pointers after (index+1) in the current node one
    // step before
    for (int i = index + 2; i <= p->n; ++i)
        p->children[i - 1] = p->children[i];

    // Updating the key count of child and the current node
    child->n += sibling->n + 1;
    int x = p->n;
    p->n = x - 1;

    // Freeing the memory occupied by sibling
    free(sibling);
    return;
}

//Initially called to remove a key
void removeKey(btreeNode *root, int k)
{
    if (!(root))
    {
        printf("The tree is empty\n");
        return;
    }
    // Call the removeFromNode function for root
    removeFromNode(k, root);

    // If the root node has 0 keys, make its first child as the new root
    //  if it has a child, otherwise set root as NULL
    if (root->n == 0)
    {
        btreeNode *p = root;
        if (root->leaf)
            root = NULL;
        else
        {
            root = (root->children[0]);
        }
        // Free the old root
        free(p);
    }
    return;
}
