#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef enum
{
    COMMAND_SUCCESS,
    COMMAND_UNRECOGNIZED_COMMAND
} CommandResult;
void help()
{
    printf("this is help");
}
CommandResult prepareCreate(char *input)
{
    char *temp = input + 8;
    int colNameLength,dataTypeLength;
    char *colName, *dataType;

loop:
    if (*temp == '<')
    {
        temp++;
        colNameLength=0;
        dataTypeLength=0;
        while (*temp != '>')
        {
            colNameLength++;
            temp++;
        }
        colName = (char *)malloc(colNameLength);
        strncpy(colName, temp - colNameLength, colNameLength);

        //insert col in db
    }
    temp++;
    if (*temp == '(')
    {
        temp++;
        while (*temp != ')')
        {
            dataTypeLength++;
            temp++;
        }
       
        dataType = (char *)malloc(dataTypeLength);
        strncpy(dataType, temp - dataTypeLength, dataTypeLength);
        
    }
    temp++;
   
    if ((strncmp(dataType,"NUM",3) != 0) && (strncmp(dataType,"STR",3) != 0))
    {
        return COMMAND_UNRECOGNIZED_COMMAND;
    }

    if (*temp == ' ')
    {
        //insert colname and datatype
        temp++;
        goto loop;
    }
    else if (*temp == '\0')
    {
        //insert that last col
        return COMMAND_SUCCESS;
    }
    else
        return COMMAND_UNRECOGNIZED_COMMAND;
}
void command(char *input)
{

    if (strcmp(input, ".exit") == 0)
    {
        exit(0);
    }
    if (strcmp(input, ".help") == 0)
    {
        help();
        free(input);
    }
    else if (strncmp(input, "-create ", 8) == 0)
    {
        switch (prepareCreate(input))
        {
        case (COMMAND_SUCCESS):
            printf("yayin create");
            return;
        case (COMMAND_UNRECOGNIZED_COMMAND):
            printf("Unrecognized command '%s'\n", input);
            return;
        }
    }
    else if (strncmp(input, "-insert ", 8) == 0)
    {
        //if db already created insert
        //else ask them to create db
    }
    else if (strncmp(input, "-delete ", 8) == 0)
    {
        //if db exists and not empty, delete
        //else say nopeeeee
        //check if the parameters are correct
    }
    else if (strncmp(input, "-select ", 8) == 0)
    {
        //print out the selected record based on given key
    }
    else
    {
        printf("Unrecognized command '%s'\nUse command .help for help", input);
        return;
    }
}