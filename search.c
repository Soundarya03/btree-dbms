
btreeNode * search(btreeNode *root, int k)
{
    btreeNode *p = root; // first points to the root node
    int n = p->n;        // n is the number of keys in the node
    int i = 0;
    while (i < n && k > p->keys[i]) // to find the first greater key than "k"
        i++;                        // increment until the condition results in false

    // if the k equals the key at position i
    if (p->keys[--i] == k)
        return p; // then return pointer to that node

    // if the node is a leaf node and the key is not found then we return NULL
    if (p->leaf == 1)
        return NULL;

    return search(&(p->children[++i]), k); // recursive call
}
