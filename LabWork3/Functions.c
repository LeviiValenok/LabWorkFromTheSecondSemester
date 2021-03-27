
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
    char fileName[] = "C:\\Users\\gaydi\\CLionProjects\\LabWork3\\textFile.txt";
    while (!isQuite)
    {
        switch (menuForTextChoice())
        {
            case 1:
            {
                char sourceString[] = "This line was created to debug this program.";
                inputStrings(fileName, sourceString);
                break;
            }
            case 2:
            {
                outputText(fileName);
                break;
            }
            case 3:
            {
                printf("Enter a number of letter in the word to seek by: \n");
                int number = inputValidation();
                seekAndOutputSuitableItem(number, fileName);
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

int menuForTextChoice()
{
    int choice;
    printf("\t1 to input a text\n");
    printf("\t2 to output the text\n");
    printf("\t3 to search by a set number\n");
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
void inputStrings(char* nameOfFile, char* sourceString)
{
    FILE* textFilePointer = fopen(nameOfFile, "w");
    fprintf(textFilePointer, "%s", sourceString);

    rewind(textFilePointer);
    fclose(textFilePointer);
}

void outputText(char* nameOfFile)
{
    FILE* textFilePointer = fopen(nameOfFile, "r");
    char letter;
	printf("\t\t  Source file  : \n");
	while ((letter = getc(textFilePointer)) != EOF)
	{
        fprintf(textFilePointer, "%c", letter);
    }
	rewind(textFilePointer);
	fclose(textFilePointer);
}

void seekAndOutputSuitableItem(int number, char* nameOfFile)
{
    char letter;
    int counter = 0, position = 0, successfulOperations = 0;

    bool isQuite = false;
    FILE* textFilePointer = fopen(nameOfFile, "a+");
    rewind(textFilePointer);
    while (!isQuite)
    {
        while (!feof(textFilePointer))
        {
            fscanf(textFilePointer, "%c", &letter);
            if (letter != ' ')
            {
                position++;
                counter++;
                break;
            }
            else
            {
                position++;
                if (counter == number)
                {
                    outputWord(nameOfFile, number, position);
                    successfulOperations++;
                    counter = 0;
                }
                else
                {
                    counter = 0;
                }
            }
        }
        if(feof(textFilePointer))
        {
            isQuite = true;
            break;
        }
    }
    if (successfulOperations == 0)
    {
        printf("There no suitable words\n");
    }
    fclose(textFilePointer);
}
void outputWord(char* nameOfFile, int wordSize, int place)
{
    char letter;
    FILE* textFilePointer = fopen(nameOfFile, "r");
    fseek(textFilePointer,place - wordSize - 1,SEEK_SET);
    printf("Found word: \n");
    /*int result1 = fgetpos(textFilePointer, position);
    int result2 = fsetpos(textFilePointer, position);*/
    while((letter = getc(textFilePointer)) != ' ')
    {
        printf("%c", letter);
    }
    printf("\n");
    fclose (textFilePointer);
}