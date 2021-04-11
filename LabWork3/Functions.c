
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
                menuForBinaryFile();
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
    char* fileName = (char*)calloc(20, sizeof(char));
    fileName = enterFileName(TEXTFILE, fileName);
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
    while (scanf("%d%c", &number, &c) != 2 || c != '\n')
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
    int choice;
    printf("\t1 to enter integers\n");
    printf("\t2 to count the number of integers, which are bigger than  sum previous integers\n");
    printf("\t3 to sort two files descending into one\n");
    printf("\t4 to output numbers\n");
    printf("\t0 to quite\n");
    printf("Enter -----> \n");
    choice = inputValidation();
    return choice;
}
void menuForBinaryFile()
{
    bool isQuite = false;
    bool isQuiteForMiniMenu = false;
//    char* firstFileName = "";
    char* firstFileName = (char*)calloc(20, sizeof(char));
    firstFileName = enterFileName(BINARYFILE, firstFileName);
    while (!isQuite)
    {
        switch(menuForBinaryChoice())
        {
            case 1:
            {
                inputIntegers(firstFileName);
                break;
            }
            case 2:
            {
                int amount = findNumbers(firstFileName);
                printf("%d", amount);
                break;
            }
            case 3:
            {
                char* secondFileName  = (char*)calloc(20, sizeof(char));
                char* resultFile = (char*)calloc(20, sizeof(char));
                printf("\tEnter the second file to sort \n");
                secondFileName = enterFileName(BINARYFILE, secondFileName);
                printf("\tEnter name for the result file \n");
                resultFile = enterFileName(BINARYFILE, resultFile);
                printf("\tEnter numbers on descending for the first file\n");
                enterIntegerOnDescending(firstFileName);
                printf("\tEnter numbers on descending for the second file\n");
                enterIntegerOnDescending(secondFileName);
                while (!isQuiteForMiniMenu)
                {
                    switch (menuForSortFiles()) {
                        case 1: {
                            outputIntegers(firstFileName);
                            break;
                        }
                        case 2: {
                            outputIntegers(secondFileName);
                            break;
                        }
                        case 0:
                        {
                            isQuiteForMiniMenu = true;
                            break;
                        }
                    }
                }
                combineTwoFilesInDescendingOrder(firstFileName, secondFileName, resultFile);
                printf("\t1 to output result\n");
                printf("\t0 to exit\n");
                int choice = inputValidation();
                switch(choice)
                {
                    case 1:
                        outputIntegers(resultFile);
                        break;
                    case 0:
                        break;
                }
                break;
            }
            case 4:
            {
                outputIntegers(firstFileName);
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

void inputIntegers(char* nameOfTheFile)
{
    int amountOfSuccessfullyReadNumbers;
    int n, indicator = 0, amount;
    char c;
    FILE* binaryFile = fopen(nameOfTheFile, "wb");
    rewind(binaryFile);
    printf("Enter an amount of number:\n");
    amount = inputValidation();
    printf("Enter numbers: \n");
    while(indicator < amount)
    {
        n = inputValidation();
        amountOfSuccessfullyReadNumbers = fwrite(&n, sizeof(int), 1, binaryFile);
        if (amountOfSuccessfullyReadNumbers != 1)
        {
             printf("Failed to read numbers\n");
        }
        else
        {
            indicator++;
        }
    }
    fclose(binaryFile);
}

void outputIntegers(char* nameOfTheFile)
{
    FILE* binaryFile = fopen(nameOfTheFile, "rb");
    rewind(binaryFile);
    int n, index = 0;
    printf("Your numbers: \n");
    rewind(binaryFile);
    while(!feof(binaryFile) && fread(&n, sizeof(int), 1, binaryFile) == 1 )
    {
        printf(" %d ", n);
    }
    printf("\n");
    fclose(binaryFile);
}

int findNumbers(char* nameOfTheFile)
{
    FILE* binaryFile = fopen(nameOfTheFile, "rb");
    rewind(binaryFile);
    fpos_t position;
    int tempSum = 0, n, amount = 0;
    while(!feof(binaryFile) && fread(&n, sizeof(int), 1, binaryFile) == 1)
    {
        if (n > tempSum)
        {
            amount++;
        }
        tempSum += n;
    }
    fclose(binaryFile);
    return amount;
}

char* enterFileName(enum fileType type, char* fileName)
{
//    char* fileName[20];
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

    switch(type)
    {
        case 1:
        {
            fileName[strlen(fileName)-1] = '\0';
            char expansion[5] = ".bin";
            strcat(fileName, expansion);
            return fileName;
            break;
        }
        case 2:
        {
            fileName[strlen(fileName)-1] = '\0';
            char expansion[5] = ".txt";
            strcat(fileName, expansion);
            return fileName;
            break;
        }
    }


}

void enterIntegerOnDescending(char* nameOfFile)
{
    int amountOfNumbers, indicator = 0, number, amountOfSuccessfullyReadNumbers;
    int tempNumber, index  = 0;
    fpos_t position;
    printf("Enter amount of numbers you want to enter: \n");
    scanf("%d", &amountOfNumbers);

    FILE* filePointer = fopen(nameOfFile, "wb");
    printf("Enter a numbers: \n");
    rewind(filePointer);
    while(indicator < amountOfNumbers)
    {

        number = inputValidation();
        if (index == 0)
        {
            amountOfSuccessfullyReadNumbers = fwrite(&number, sizeof(int), 1, filePointer);
            tempNumber = number;
            if (amountOfSuccessfullyReadNumbers != 1)
            {
                printf("Failed to read numbers\n");
            }
            else
            {
                indicator++;
            }
        }
        else
        {
            while (number > tempNumber)
            {
                printf("Please try again. Enter a number less than the previous one\n");
                number = inputValidation();
            }
            amountOfSuccessfullyReadNumbers = fwrite(&number, sizeof(int), 1, filePointer);
            if (amountOfSuccessfullyReadNumbers != 1)
            {
                printf("Failed to read numbers\n");
            }
            else
            {
                indicator++;
            }
            tempNumber = number;
        }
        index++;

        /*if (index == 1)
        {
            amountOfSuccessfullyReadNumbers = fwrite(&number, sizeof(int), 1, filePointer);
            if (amountOfSuccessfullyReadNumbers != 1)
            {
                printf("Failed to read numbers\n");
            }
            else
            {
                indicator++;
            }
        }
        else
        {
            fgetpos(filePointer, position);
            fsetpos(filePointer, position - 1);
//            fseek(filePointer, indicator - 2, SEEK_SET);
            fread(&tempNumber, sizeof(int), 1, filePointer);

            if (tempNumber < number)
            {
                printf("Please try again. Enter a number less than the previous one\n");
                number = inputValidation();
            }
            amountOfSuccessfullyReadNumbers = fwrite(&number, sizeof(int), 1, filePointer);
            if (amountOfSuccessfullyReadNumbers != 1)
            {
                printf("Failed to read numbers\n");
            }
            else
            {
                indicator++;
            }
        }*/

    }
    fclose(filePointer);
}

int menuForSortFiles()
{
    int choice;
    printf("\t1 to output content from the first file\n");
    printf("\t2 to output content from the second file\n");
    printf("\t0 to quite\n");
    choice = inputValidation();
    return choice;
}

void combineTwoFilesInDescendingOrder(char* firstFile, char* secondFile, char* resultFile)
{
    int firstNumber, secondNumber;
    FILE* firstFilePointer = fopen(firstFile, "rb");
    FILE* secondFilePointer = fopen(secondFile, "rb");
    FILE* resultFilePointer = fopen(resultFile, "wb");
    rewind(firstFilePointer);
    rewind(secondFilePointer);
    rewind(resultFilePointer);
    fread(&firstNumber, sizeof(int), 1, firstFilePointer);
    fread(&secondNumber, sizeof(int), 1, secondFilePointer);
    do
    {
        while(!feof(firstFilePointer) && firstNumber > secondNumber)
        {
            fwrite(&firstNumber, sizeof(int), 1, resultFilePointer);
            fread(&firstNumber, sizeof(int), 1, firstFilePointer);
        }
        while(!feof(secondFilePointer) && secondNumber > firstNumber)
        {
            fwrite(&secondNumber, sizeof(int), 1, resultFilePointer);
            fread(&secondNumber, sizeof(int), 1, secondFilePointer);
        }

    } while(!feof(secondFilePointer));

    while(!feof(firstFilePointer))
    {
        fwrite(&firstNumber, sizeof(int), 1, resultFilePointer);
        fread(&firstNumber, sizeof(int), 1, firstFilePointer);
    }
    while(!feof(secondFilePointer))
    {
        fwrite(&secondNumber, sizeof(int), 1, resultFilePointer);
        fread(&secondNumber, sizeof(int), 1, secondFilePointer);
    }
    fclose(resultFilePointer);
    fclose(secondFilePointer);
    fclose(firstFilePointer);
}
