#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.c"
#include "insert.c"

btreePointer *root=NULL;
void main()
{
    int ch,value;
    char choice;
    menu:printf("=====MENU=====\n");
    printf("1.Insert\n2.Delete\n3.Search\n");
    switch(ch)
    {
        case 1:
        printf("Enter value to be inserted\n");
        scanf("%d",&value);
       ins: insert(root,value);
        printf("Insert another value?Press y to insert,any other key to go back to menu\n");
        if(choice=='y') goto ins;
        else goto menu;
        break;
        case 2:
        printf("Enter the value to be deleted\n");
        scanf("%d",&value);

    }
    
}