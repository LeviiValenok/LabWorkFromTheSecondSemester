
#include "Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

int inputValidation(bool type)
{
    int number;
    char c;
    if (type)
    {
        while (scanf("%d%c", &number, &c) != 2 || c != '\n' || number < 0)
        {
            rewind(stdin);
            printf("Try again\n");
        }
    }
    else
    {
        while (scanf("%d%c", &number, &c) != 2 || c != '\n') {
            rewind(stdin);
            printf("Try again\n");
        }
    }
    return number;
}

int menuForChoice ()
{
    int choice;
    bool isTrue = true;
    printf("\t1 to add elements to stack\n");
    printf("\t2 to output elements\n");
    printf("\t3 to delete item from stack\n");
    printf("\t4 to seek by option\n");
    printf("\t5 to save as file\n");
    printf("\t6 to load list from file\n");
    printf("\t0 to exit\n");
    printf("Enter ---->");
    choice = inputValidation(isTrue);
    return choice;
}

void pushToStack(struct geometricShapes** topOfStack)
{
    bool isQuite = false;
    do
    {
        struct geometricShapes *item = *topOfStack;
        if (!(*topOfStack = (struct geometricShapes *) calloc(1, sizeof(struct geometricShapes)))) {
            printf("Memory is not allocated\n");
            return;
        }
        enterArrayOfStructure(*topOfStack);
        (*topOfStack)->nextItem = item;
        item = *topOfStack;
        printf("\tDo you want to add more?\n");
        printf("\t1 to add more\n");
        printf("\t2 to quite\n");
        switch(rightChoice())
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                isQuite = true;
                break;
            }
        }

    } while (!isQuite);

}

void enterArrayOfStructure(struct geometricShapes* pointer)
{
    bool isType = true;
    printf("\n");
    printf("Enter a square: \n");
    (pointer)->square = inputValidation(isType);
    printf("Enter a name: \n");
    rewind(stdin);
    gets((pointer)->name);

    printf("\t 1  to enter a perimeter\n");
    printf("\t 2  to enter a color\n");
    switch(rightChoice())
    {
        case 1:
            printf("Enter a perimeter: \n");
            (pointer)->information.perimeter = inputValidationForFloat();
            (pointer)->flag = true;
            break;
        case 2:
            printf("Enter a color: \n");
            rewind(stdin);
            gets((pointer)->information.color);
            (pointer)->flag = false;
            break;
    }


}

float inputValidationForFloat()
{
    float number;
    char c;
    while (scanf("%f%c", &number, &c) != 2  || c != '\n' || number < 0)
    {
        rewind(stdin);
        printf("Try again\n");

    }
    return number;
}

int rightChoice()
{
    int number;
    char c;
    while ((scanf("%d%c", &number, &c) != 2 || c != '\n' || number < 0) || number > 3)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return number;
}

void mainMenu()
{
    bool isQuite = false;
    char* nameOfFile;
    struct geometricShapes* topOfTheStack = NULL;
    while(!isQuite)
    {
        switch (menuForChoice())
        {
            case 1:
            {
                pushToStack(&topOfTheStack);
                break;
            }
            case 2:
            {
                outputContent(topOfTheStack);
                break;
            }
            case 3:
            {
                menuForDelete(&topOfTheStack);
                break;
            }
            case 4:
            {
                seekByOptions(&topOfTheStack);
                break;
            }
            case 5:
            {
                menuForSave(topOfTheStack);
                break;
            }
            case 6:
            {
                 menuForLoadFromFile(&topOfTheStack);
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

void outputContent(struct geometricShapes* topOfTheStack)
{

    struct geometricShapes* item = topOfTheStack;
    struct geometricShapes* tempItem = topOfTheStack;
    if (item == NULL)
    {
        return;

    }
    if (item->square == 0)
    {
    }
    else
    {
        hatter();
    }
    while(item && item->square != 0)
    {
        outputFigure(item);
        item = item ->nextItem;
        printLine();
    }
}

void hatter()
{

    char table[] = "F i g u r ' s  t a b l e";
    printf("\n");
    printLine();
    printf("|\t\t\t%-44s|\n", table);
    printLine();
    printf("|\t%-10s|\t\t%-12s|\t%-20s|\n", "SQUARE", "NAME", "PERIMETER/COLOR");
    printLine();
}

void printLine()
{
    int n = 69;
    for (int i = 0; i < n; i++)
    {
        printf("%c", '-');
    }
    printf("\n");
}

void outputFigure(struct geometricShapes* pointer)
{
    if ((pointer)->flag)
    {
        printf("|\t%-10d|\t%-20s|\t%-20.3f|\n", (pointer)->square, (pointer)->name,
               (pointer)->information.perimeter);
    }
    else
    {
        printf("|\t%-10d|\t%-20s|\t%-20s|\n", (pointer)->square, (pointer)->name,
               (pointer)->information.color);
    }
}

void menuForDelete(struct geometricShapes** topOfStack)
{
    int number;
    bool isType = true;
    if (topOfStack == NULL)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Enter a number of element you want to delete\n");
    number = inputValidation(isType);
    printf("\tAre you sure you want to delete this element?\n");
    printf("\t1 yes\n");
    printf("\t2 no\n");
    switch(rightChoice())
    {
        case 1:
        {
            deleteAnItem(topOfStack, number);
            break;
        }
        case 2:
        {
            return;
        }
    }

}

void deleteAnItem(struct geometricShapes** topOfStack, int number)
{

    if (topOfStack == NULL) {
        printf("Stack is empty\n");
        return;
    }
    struct geometricShapes *temp = *topOfStack;                 //create new pointer and put it on the top of the stack
    struct geometricShapes *previousElement = NULL;            //create pointer for previous element
    struct geometricShapes *deletableItem = NULL;
    struct geometricShapes *nextElement = NULL;
    temp = *topOfStack;
    int i = 0;
    if (number == 1)
    {
        *topOfStack = temp->nextItem;
        free(temp);
        temp->nextItem = NULL;
        return;

//    *topOfStack = temp->nextItem;
//    free(temp);
//    temp->nextItem = *
//    }

//        previousElement->nextItem = temp->nextItem;
        *topOfStack = temp->nextItem;
        free(temp);
        previousElement = temp;
        temp = temp->nextItem;
    }
        while (i < number - 2)
        {
            i++;
            *topOfStack = (*topOfStack)->nextItem;
            if (temp == NULL)
            {
                break;
            }
        previousElement = *topOfStack;
        *topOfStack = (*topOfStack)->nextItem;
        deletableItem = *topOfStack;
        *topOfStack = (*topOfStack)->nextItem;
        nextElement = *topOfStack;
        previousElement->nextItem = nextElement;
        *topOfStack = temp;
        free(deletableItem);
/*        previousElement->nextItem = temp ->nextItem;            //connect lint from previous item to next item
        free(temp);
        temp->nextItem = NULL;*/
//    previousElement= temp;
//    temp = temp->nextItem;

        }
}



void seekByOptions(struct geometricShapes** topOfStack)
{
    bool isQuite = false;
    while(!isQuite)
    {
        switch (menuForSeek())
        {
            case 1:
            {
                seekByColor(*topOfStack);
                break;
            }
            case 2:
            {
                seekByFloats(*topOfStack); //check it
                break;
            }
            case 3:
            {
                seekByIntegers(*topOfStack);
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

int menuForSeek()
{
    bool isType = true;
    printf("\n");
    printf("\t1 to seek by color\n");
    printf("\t2 to seek by perimeter\n");
    printf("\t3 to seek by square\n");
    printf("\t0 to quite\n");
    printf("Enter ----> ");
    int choice = inputValidation(isType);
    return choice;
}

void seekByColor(struct geometricShapes* topOfStack) {
    int index = 0;
    printf("Enter a string to compare\n");
//    char tempString[20];
    char *tempString = (char*) calloc(20, sizeof(char));
    rewind(stdin);
    gets(tempString);
    convertToTheSameRegister(tempString);
    do
    {
        if (topOfStack->flag)
        {
            topOfStack = topOfStack->nextItem;
            continue;
        }
        convertToTheSameRegister(topOfStack->information.color);
        if (strcmp(topOfStack->information.color, tempString) == 0)
        {
            index++;
            if(index == 1)
            {
                hatter();
            }
//            printLine();
            outputFigure(topOfStack);
            printLine();
        }

        topOfStack = topOfStack->nextItem;

    }while(topOfStack);
    if (index == 0)
    {
        printf("There is no items with this color\n");
        return;
    }


}

void convertToTheSameRegister(char* string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if ((string[i] >= 'a') && (string[i] <= 'z'))
        {
            i++;
            continue;
        }


        if ((string[i] >= 'A') && (string[i] <= 'Z'))
        {
            string[i] = tolower(string[i]);
            i++;
            continue;
        }
        i++;
    }
}

void seekByIntegers(struct geometricShapes* topOfStack)
{
    int number, index = 0;
    bool isTrue = true;
    printf("Enter an integer to seek by it: \n");
    number = inputValidation(isTrue);

    do
    {
        if (topOfStack->square == number)
        {
            index++;
            if(index == 1)
            {
                hatter();
            }
//            printLine();
            outputFigure(topOfStack);
            printLine();

        }
        (topOfStack) = (topOfStack)->nextItem;
    } while (topOfStack);
    if (index == 0)
    {
        printf("There is no items with this square\n");
    }
    return;
}

void seekByFloats(struct geometricShapes* topOfStack)
{
    int index = 0;
    printf("Enter a float to seek by it: \n");
    float number = inputValidationForFloat();
    if (!(topOfStack->flag))
    {
        (topOfStack) = (topOfStack)->nextItem;
    }
    do
    {
        if(topOfStack->information.perimeter == number)
        {
            index++;
            if(index == 1)
            {
                hatter();
            }
//                printLine();
            outputFigure(topOfStack);
            printLine();

        }
        (topOfStack) = (topOfStack)->nextItem;
    }while(topOfStack);
    if (index == 0)
    {
        printf("There is no items with this square\n");
        return;
    }

}

int menuForLoadAsFileChoice()
{
    bool isType = true;
    int choice;
    printf("\n");
    printf("\t1 to load as text file\n");
    printf("\t2 to load as binary file\n");
    printf("\t0 to quite\n");
    choice = inputValidation(isType);
    return choice;
}

int menuForLoadFromFileChoice()
{
    bool isType = true;
    int choice;
    printf("\n");
    printf("\t 1 to load from text file\n");
    printf("\t 2 to load from binary file\n");
    printf("\t0 to quite\n");
    choice = inputValidation(isType);
    return choice;
}

void menuForSave(struct geometricShapes* topOfStack)
{
    char* nameOfTheFile;
    switch(menuForLoadAsFileChoice())
    {
        case 1:
        {
            saveAsTextFile(topOfStack);
            break;
        }
        case 2:
        {
            saveAsBinaryFile(topOfStack);
            break;
        }
        case 0:
        {
            break;
        }
    }
}

char* enterFileName(enum fileType type)
{
    char* fileName =(char*)calloc(20, sizeof(char));
    char letter;
    int i = 0, indicator;
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
            deleteSymbols(fileName);
            char expansion[] = ".bin";
            strcat(fileName, expansion);
            return fileName;
            break;
        }
        case 2:
        {
            deleteSymbols(fileName);
            char expansion[] = ".txt";
            strcat(fileName, expansion);
            return fileName;
            break;
        }
        default:
        {
            break;
        }
    }

    return fileName;
}

void saveAsTextFile(struct geometricShapes* topOfStack)
{
    char* nameOfFile = enterFileName(TEXTFILE);

    FILE* textFilePointer = fopen(nameOfFile, "w+");
    if (textFilePointer == NULL)
    {
        perror("An error occurred while opening the file\n");
        exit(0);
    }
    rewind(textFilePointer);
    while (topOfStack)
    {
        if(topOfStack->flag)
        {
            fprintf(textFilePointer, "%d\n", topOfStack->square);
            fprintf(textFilePointer, "%s\n", topOfStack->name);
            fprintf(textFilePointer, "%d\n", 1);
            fprintf(textFilePointer, "%fl\n", topOfStack->information.perimeter);
        }
        else
        {
            fprintf(textFilePointer, "%d\n", topOfStack->square);
            fprintf(textFilePointer, "%s\n", topOfStack->name);
            fprintf(textFilePointer, "%d\n", 0);
            fprintf(textFilePointer, "%s\n", topOfStack->information.color);
        }
        topOfStack = topOfStack->nextItem;
    }
    fclose(textFilePointer);
}

void outputFigureToFle(struct geometricShapes* pointer, FILE* textFilePointer)
{
    if ((pointer)->flag)
    {
        fprintf(textFilePointer, "|\t%-10d|\t%-20s|\t%-20.3f|\n", (pointer)->square, (pointer)->name,
               (pointer)->information.perimeter);
    }
    else
    {
        fprintf(textFilePointer, "|\t%-10d|\t%-20s|\t%-20s|\n", (pointer)->square, (pointer)->name,
               (pointer)->information.color);
    }
}

void menuForLoadFromFile(struct geometricShapes** topOfStack) {

    switch (menuForLoadAsFileChoice()) {
        case 1: {
            bool isType = false;
            int flag;
            char* nameOfFile = enterFileName(TEXTFILE);
            int counter = 0;
            fpos_t position;
            char letter;
            struct geometricShapes *copy = *topOfStack;
            struct geometricShapes *tempStack = *topOfStack;
            FILE *filePointer = fopen(nameOfFile, "r");
            rewind(filePointer);
            while (!feof(filePointer)) {

                if (!(*topOfStack = (struct geometricShapes *) calloc(1, sizeof(struct geometricShapes)))) {
                    printf("Memory is not allocated\n");
                    return;
                }
                counter++;
                fscanf(filePointer, "%d", &(*topOfStack)->square);
                if ((*topOfStack)->square == 0) {
                    break;
                }
                fseek(filePointer, 2, SEEK_CUR);
                fgets((*topOfStack)->name, 20, filePointer);
                deleteSymbols((*topOfStack)->name);
                fscanf(filePointer, "%d", &flag);
                fseek(filePointer, 2, SEEK_CUR);

                if (flag == 1)
                {
                    (*topOfStack)->flag = true;
                    fscanf(filePointer, "%f", &(*topOfStack)->information.perimeter);
                } else
                {
                    fgets((*topOfStack)->information.color, 20, filePointer);
                    (*topOfStack)->flag = false;
                    deleteSymbols((*topOfStack)->information.color);
                }
                (*topOfStack)->nextItem = copy;
                copy = *topOfStack;
            }
            if (*topOfStack == NULL) {
                printf("The contents of the file were not pushed onto the stack\n");
            } else {
                printf("The contents of the file were pushed onto the stack successful\n");
            }


            fclose(filePointer);

            copyOfStack(&copy, &(*topOfStack));


            break;
        }
        case 2:
        {
            char* nameOfFile = enterFileName(BINARYFILE);
            char letter, indicator;
            int flag;
            char* tempString = (char*)calloc(20, sizeof(char));
            int i = 0;
            FILE *binaryFile;
            if ((binaryFile = fopen(nameOfFile, "rb")) == NULL)
            {
                printf("File not founded\n");
                return;
            }
            struct geometricShapes *copy = *topOfStack;
            struct geometricShapes *tempStack = *topOfStack;
            rewind(binaryFile);
            while (!feof(binaryFile))
            {
                if (!(*topOfStack = (struct geometricShapes *) calloc(1, sizeof(struct geometricShapes)))) {
                    printf("Memory was not allocated\n");
                    return;
                }
                fread(&((*topOfStack)->square), sizeof(int), 1, binaryFile);
                fread(&indicator, sizeof(char), 1, binaryFile);
                if ((*topOfStack)->square == 0)
                {
                    break;
                }
                while (letter != ' ')
                {
                    fread(&letter, sizeof(char), 1, binaryFile);
                    tempString[i] = letter;
                    i++;
                }
//                tempString = (char*) realloc(tempString, i - 1);
                tempString[i - 1] = '\0';
                strcpy((*topOfStack)->name, tempString);
                tempString[0] = '\0';
                fread(&flag, sizeof(int), 1, binaryFile);
                if (flag == 1)
                {
                    (*topOfStack)->flag = true;
                }
                else
                {
                    (*topOfStack)->flag = false;
                }
                fread(&indicator, sizeof(char), 1, binaryFile);
                if ((*topOfStack)->flag)
                {
                    fread(&((*topOfStack)->information.perimeter), sizeof(float), 1, binaryFile);
                    fread(&indicator, sizeof(char), 1, binaryFile);
                }
                else
                {
                    letter = '\0';
                    i = 0;
                    tempString[0] = '\0';
                    while (letter != ' ')
                    {
                        fread(&letter, sizeof(char), 1, binaryFile);
                        tempString[i] = letter;
                        i++;
                    }
//                    tempString = (char*) realloc(tempString, i);
                    tempString[i - 1] = '\0';
                    letter = '\0';
                    i = 0;
                    strcpy((*topOfStack)->information.color, tempString);
                    deleteSymbols(((*topOfStack))->information.color);
                    tempString[0] = '\0';
                }
                ((*topOfStack))->nextItem = copy;
                copy = (*topOfStack);
                tempString[0]='\0';

            }
            if (*topOfStack == NULL)
            {
                printf("The contents of the file were not pushed onto the stack\n");
            } else
            {
                printf("The contents of the file were pushed onto the stack successful\n");

                fclose(binaryFile);

                copyOfStack(&copy, &(*topOfStack));
                break;
            }
        }
    }
}


void saveAsBinaryFile(struct geometricShapes* topOfStack)
{
    char* nameOfTheFile = enterFileName(BINARYFILE);
    int flagTrue = 1;
    int flagFalse = 0;
    char letter = ' ';

    FILE* binaryFile;
    if (!(binaryFile = fopen(nameOfTheFile, "wb")))
    {
        printf("File was not created\n");
        return;
    }
    rewind(binaryFile);
    while (topOfStack)

    {
        if (topOfStack->flag)
        {

             fwrite(&(topOfStack->square), sizeof(int), 1, binaryFile);
             fwrite (&letter, sizeof(char), 1, binaryFile);
             fwrite(&(topOfStack->name), strlen(topOfStack->name), 1, binaryFile);
             fwrite (&letter, sizeof(char), 1, binaryFile);
             fwrite(&flagTrue, sizeof(int), 1, binaryFile);
             fwrite (&letter, sizeof(char), 1, binaryFile);
             fwrite(&(topOfStack->information.perimeter), sizeof(float), 1, binaryFile);
             fwrite (&letter, sizeof(char), 1, binaryFile);
        }
        else
        {
            fwrite(&(topOfStack->square), sizeof(int), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&(topOfStack->name), strlen(topOfStack->name), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&flagFalse, sizeof(int), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&(topOfStack->information.color), strlen(topOfStack->information.color), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
        }
        topOfStack = topOfStack->nextItem;
    }
    rewind(binaryFile);
    fclose(binaryFile);
}

void deleteSymbols(char* string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
        i++;
    }
}



void copyOfStack(struct geometricShapes** source, struct geometricShapes** final)
{
    int counter = 0;
    bool isQuite = false;
    struct geometricShapes *item = *final;
    struct geometricShapes *topOfStack = *source;
    while (!isQuite)
    {
        if (!((*final) = (struct geometricShapes *) calloc(1, sizeof(struct geometricShapes)))) {
            printf("Memory is not allocated!\n");
            break;
        }
        (*final)->square = (*source)->square;
        strcpy((*final)->name, (*source)->name);
        if ((*source)->flag)
        {
            (*final)->flag = true;
            (*final)->information.perimeter = (*source)->information.perimeter;
        } else
        {
            (*final)->flag = false;
            strcpy((*final)->information.color, (*source)->information.color);
        }
        (*final)->nextItem = item;
        item = *final;
        counter++;
        if (!(*source)->nextItem)
        {
            isQuite = true;
            break;
        }
        (*source)=(*source)->nextItem;

    }
}


