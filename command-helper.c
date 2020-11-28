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
    printf("===============THIS IS THE HELP SECTION===============\n");
    printf("\n\n");
    printf("VALID DATATYPES\n");
    printf("• NUM : An integer of 32-bits.\n• STR : A string of 100 bytes.\n\n\n");
    printf("COMMAND : -create\n");
    printf("Syntax : -create <ColName1>(i32) <ColName2>(<DataType2>) ...\n        The first column is always a unique key of type i32. This is the key used to store data in the B-tree. The rest of the columm can have different types and names. Column names cannot be repeated. A table can be created only once for a file.\n");
    printf("\n");
    printf("COMMAND : -insert\n");
    printf("Syntax : -insert key_value data_1 data_2 ...\n");
    printf("        The key_value must be of type NUM. The remaining data values must be of the same type as the column it belongs to. The given record is inserted into the database.\n");
    printf("\nCOMMAND : -delete\n");
    printf("Syntax : -delete key_value\n");
    printf("        This command deletes a record containing the key_value. If the key_value doesn't exist, it will throw an error.\n");
    printf("\n");
    printf("COMMAND : -select\n");
    printf("Syntax : -select key_value\n");
    printf("        This command selects certain record of key_value and displays it. If key_value is * , then it will print out all records. If the key_value doesn't exist, it will throw an error.\n");
    printf("\nCOMMAND : .exit\n");
    printf("Syntax : .exit\n");
    printf("        This command allows the user to exit the database.\n");
    printf("\n");
    printf("==============================END OF HELP ================================\n");


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