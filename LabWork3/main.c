
#include "Header.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *textFilePointer = fopen("C:\\Users\\gaydi\\CLionProjects\\LabWork3\\textFile.txt", "r+");
//    FILE *binaryFilePointer = fopen
    if (textFilePointer == NULL)
    {
        perror("Error occured while opening textFile.txt\n");
        exit(0);
    }
    mainMenu(textFilePointer);
    fclose(textFilePointer);
    return 0;
}
