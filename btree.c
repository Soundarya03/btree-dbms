//this file can contain the data structure definition
typedef struct btreeNode *btreePointer;

typedef struct btreeNode
{
    int *key;               //array of keys
    btreePointer *children; //array of pointers to children;

    int t;    //minimum degree(no. of keys that should be there)
    int n;    //current no. of keys in this node
    int leaf; //0 OR 1 : whether the node is a leaf or not
    
} btreeNode;
btreePointer root=NULL;

// btreePointer search(int k){
//     btreePointer p=root;
//     int i;
//     for(i=0;i<p->n;i++){

//     }
}
