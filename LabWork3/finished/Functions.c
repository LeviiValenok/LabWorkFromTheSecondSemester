
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
//    char fileName[] = "C:\\Users\\gaydi\\CLionProjects\\LabWork3\\textFile.txt";
    char fileName[20];
    char letter;
    int i = 0;
    printf("Enter a name of the file\n");
    rewind(stdin);
    while (fileName[i] != '\n')
    {
        scanf("%c", &fileName[i]);
        if (fileName[i] == '.' || fileName[i] == '*' || fileName[i] == '/' || (fileName[i] == ':')
        || fileName[i] == '[' || fileName[i] == ']' || fileName[i] == '+' || fileName[i] == '-'
        || fileName[i] == ';' || fileName[i] == ',')
        {
            printf("Incorrect name of the file. Try again\n");
            fileName[0] = '\0';
            rewind(stdin);
            i = 0;
            continue;
        }
        if (fileName[i] == '\n')
        {
            break;
        }
        i++;
    }
    fileName[strlen(fileName)-1] = '\0';

    while (!isQuite)
    {
        switch (menuForTextChoice())
        {
            case 1:
            {
//                char sourceString[] = "This line was created to debug this program ";
                inputStrings(fileName);
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
            case 4:
            {
                printf("Enter a number, to reverse all words longer than you entered\n");
                int number = inputValidation();
                findByItem(fileName, number);
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
    printf("\t4 to reverse words\n");
    printf("\t0 to quite\n");
    choice = inputValidation();
    return choice;
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
void inputStrings(char* nameOfFile)
{
    FILE* textFilePointer = fopen(nameOfFile, "w");
    char item;
    fpos_t *position;
    printf("Enter a string: \n");
    rewind(textFilePointer);
    while (item != '\n')
    {

        scanf("%c", &item);
        putc(item, textFilePointer);
    }
//    fgetpos(textFilePointer, position);
//    fsetpos(textFilePointer, position);
//    fseek(textFilePointer, -1, SEEK_END);
//    putc('\0', textFilePointer);
    rewind(textFilePointer);
    fclose(textFilePointer);
}

void outputText(char* nameOfFile)
{
    FILE* textFilePointer = fopen(nameOfFile, "r");
    printf("\n");
    rewind(stdin);
    char letter;
	while ((letter = getc(textFilePointer)) != EOF)
	{
        printf("%c", letter);
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
            if (letter != ' ' && letter != '\n' && letter != '\0')
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
    printf("Found word: \n");
    for (int i = 0; i < wordSize; i++)
    {
        fseek(textFilePointer,place - wordSize - 1 + i,SEEK_SET);
        fscanf(textFilePointer, "%c", &letter);
       if (letter != ' ' && letter != '\n')
        {
            printf("%c", letter);
        }
       else
       {
           break;
       }
    }
//    fseek(textFilePointer,place - wordSize - 1,SEEK_SET);
//    while(((letter = getc(textFilePointer)) != ' ') && (letter = getc(textFilePointer)) != '\n')
    printf("\n");
    fclose (textFilePointer);
}

void findByItem(char* nameOfFile, int number)
{
    bool isQuite = false;
    char letter;
    int wordLength = 0, position = 0,counter = 0, successfulOperations = 0;
    FILE* textFilePointer = fopen(nameOfFile, "r+");
    rewind(textFilePointer);
    while(!isQuite)
    {
        while (!feof(textFilePointer))
        {
            fscanf(textFilePointer, "%c", &letter);
            if (letter != ' ' && letter != EOF && letter != '\n')
            {
                position++;
                counter++;
                break;
            }
            else
            {
                position++;
                if (counter > number)
                {
                    reverseWord(nameOfFile, counter, position - 1);
                    successfulOperations++;
                    counter = 0;
                }
                else
                {
                     counter = 0;
                }
//                position++;
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

void reverseWord(char* fileName, int wordLength, int endPosition)
{
    char  tempLetterForEnd, tempLetterForBeginning;
    FILE* textFilePointer = fopen (fileName, "r+");
    for (int i = 0; i < wordLength/2; i++)
    {
        fseek(textFilePointer, endPosition - 1 - i, SEEK_SET);
        fscanf(textFilePointer, "%c", &tempLetterForEnd);
        fseek(textFilePointer, endPosition - wordLength + i, SEEK_SET);
        fscanf(textFilePointer, "%c", &tempLetterForBeginning);
        fseek(textFilePointer, endPosition - wordLength + i, SEEK_SET);
        fprintf(textFilePointer, "%c", tempLetterForEnd);
        fseek(textFilePointer, endPosition - 1 - i, SEEK_SET);
        fprintf(textFilePointer, "%c", tempLetterForBeginning);
    }
    fclose(textFilePointer);
}
int menuForBinaryChoice()
{

}
void menuForBinaryFile()
{

}
