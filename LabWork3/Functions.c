
#include "Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

int menu()
{
    int choice;
    printf("\t1 to work with text file\n");
    printf("\t2 to work with binary file\n");
    printf("\t0 to exit\n");
    printf("Enter -----> \n");
    choice = inputValidation();
    return choice;
}

void mainMenu(FILE* textFilePointer)
{
    _Bool isQuite = false;
    while (!isQuite)
    {
        switch (menu())
        {
            case 1:
            {
                menuForTextFile(textFilePointer);
                break;
            }
            case 2:
            {
                break;
            }
            case 0:
            {
                isQuite = true;
                break;
            }
        }
    }
}

void menuForTextFile(FILE* textFilePointer)
{
    bool isQuite = false;
    while (!isQuite) {
        switch (menuForTextChoice()) {
            case 1: {
                char sourceString[] = "This line was created to debug this program.";
                inputStrings(textFilePointer, sourceString);
                break;
            }
            case 2: {
                outputText(textFilePointer);
                break;
            }
            case 0: {
                isQuite = true;
                break;
            }

        }
    }
}

int menuForTextChoice()
{
    int choice;
    printf("\t1 to input a text\n");
    printf("\t2 to output the text\n");
    choice = inputValidation();
    return choice;
}
int menuForBinaryChoice()
{

}
void menuForBinaryFile()
{

}

int inputValidation()
{
    int number;
    char c;
    while (scanf("%d%c", &number, &c) != 2 || c != '\n' || number < 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return number;
}
void inputStrings(FILE* textFilePointer, char* sourceString)
{
    textFilePointer = fopen("C:\\Users\\gaydi\\CLionProjects\\LabWork3\\textFile.txt", "w");
    fprintf(textFilePointer, "%s", sourceString);

    rewind(textFilePointer);
    fclose(textFilePointer);
}

void outputText(FILE* textFilePointer)
{
    textFilePointer = fopen("C:\\Users\\gaydi\\CLionProjects\\LabWork3\\textFile.txt", "r");
    char letter;
	printf("\t\t  Source file  : \n");
	while ((letter = getc(textFilePointer)) != EOF)
	{
        fprintf(textFilePointer, "%c", letter);
    }
	rewind(textFilePointer);
	fclose(textFilePointer);
}
