<b>DS Hack 2020 : Basic DBMS implementation using B-trees<b>
<br>

    B Tree is a specialized m-way tree that can be widely used for disk access. A B-Tree of order m can have at most m-1 keys and m children. One of the main reasons for using B tree is its capability to store large number of keys in a single node and large key values by keeping the height of the tree relatively small; in other words, it helps make data access faster when dealing with a large number of records and hence it's application in databases<br>
    B-trees are M-way search trees with guidelines:
    If m is the order of the B-tree,
    1. Every node in a B-Tree contains at most m children.
    2. Every node in a B-Tree except the root node and the leaf node contain at least m/2 children.
    3. The root nodes must have at least 2 nodes.
    4. All leaf nodes must be at the same level.
