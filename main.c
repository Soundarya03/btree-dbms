#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"
#include "insert.c"
#include "search.c"
#include "delete.c"
#include "display.c"

btreeNode *root = NULL;
btreeNode *result = NULL;

void main()
{
    printf("B-Tree Operations\n");

    root = (btreeNode *)malloc(sizeof(btreeNode));
    (*root).leaf = 1; //it's a leaf, it has no children as of now
    (*root).n = 0;    // Update number of keys in root

    int ch, value;
    char choice;
menu:
    printf("=====MENU=====\n");
    printf("1.Insert\n2.Delete\n3.Search\n4.Display\n5.Exit\n");
    printf("\nEnter your choice\n");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
    ins:
        printf("Enter value to be inserted\n");
        scanf("%d", &value);

        result = searchInsert(root, value);
        if (result != NULL)
            printf("Value is already present in the B-Tree, please refrain from inserting duplicate values\n");
        else
            insert(&root, value);
    
        printf("\nRoot now contains:-\n");
        for (int l = 0; l < root->n; l++)
        {
            printf("%d  ", root->keys[l]);
        }
        printf("\n");
        printf("Insert another value? Press y to insert,any other key to go back to menu\n");
        scanf(" %c", &choice);
        if (choice == 'y')
            goto ins;
        else
            goto menu;
        break;
    case 2:
    del:
        printf("Enter the value to be deleted\n");
        scanf("%d", &value);
        removeKey(root, value);
        printf("Delete another value?Press y to delete,any other key to go back to menu\n");
        scanf(" %c", &choice);
        if (choice == 'y')
            goto del;
        else
            goto menu;
        break;
    case 3:
    search:
        printf("Enter the value to be searched\n");
        scanf("%d", &value);
        result = search(root, value);
        if (result != NULL)
            printf("Value is present\n");
        else
            printf("Value not present in tree\n");
        printf("Search for another value? Press y to search,any other key to go back to menu\n");
        scanf(" %c", &choice);

        if (choice == 'y')
            goto search;
        else
            goto menu;
        break;
    case 4:
        if (root->n)
        {
            printf("The b-tree traversed in order : \n");
            display(root);
        }
        else
        {
            printf("Tree is empty. \n");
        }
        printf("\n\nPress any key to continue....\n");
        scanf(" %c", &choice);
        goto menu;
        break;
    case 5:
        printf("Exiting Menu\n");
        exit(0);
    default:
        printf("Invalid input.Try again\n");
        goto menu;
    }

    free(root);
}
