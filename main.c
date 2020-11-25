/*
    DS project: 20 mark component
    Topic: Basic DBMS implementation using B-trees
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command-helper.c"
// #include "btree.c"
// #include "insert.c"

//btreeNode *root; //pointer to root

int main()
{
    printf("DBMS using B Trees\n");
    printf("Enter .help for help or .exit to exit the Database Management System\n");
    char *input;
    size_t inputLength = 0;
    ssize_t bytesRead;

    while (1)
    {

        bytesRead = getline(&input, &inputLength, stdin);
       
        *(input+bytesRead-1)='\0';
        if (*input == '.' || *input== '-') //for exit and help
           command(input);
        else
        {
            printf("Unrecognized command '%s'\nUse command .help for help\n", input);
        }
    }
    return 0;
}
