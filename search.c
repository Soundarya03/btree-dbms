
btreeNode *search(btreeNode *root, int k)
{
     if(root==NULL){
        printf("Empty B-tree");
        return;
    }
    //btreeNode *p = root; // first points to the root node
    int x = root->n; // n is the number of keys in the node
    printf("Searching in root, which contains:- ");
   
    for (int j = 0; j < root->n; j++)
    {
        printf(" %d ", root->keys[j]);
    }
    int i = 0;
    while (i < x && k > (root->keys[i])) // to find the first greater key than "k"
        i++;                             // increment until the condition results in false

    // if the k equals the key at position i
    if (root->keys[i] == k)
        return root; // then return pointer to that node

    // if the node is a leaf node and the key is not found then we return NULL
    if (root->leaf == 1)
        return NULL;

    //i++; YOU CULPRIT
    return search((root->children[i]), k); // recursive call
}
