
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
                nameOfFile = menuForSave(topOfTheStack);
                break;
            }
            case 6:
            {
                menuForLoadFromFile(nameOfFile, &topOfTheStack);
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
    if (item == NULL)
    {
        return;

    }
    else
    {
        hatter();
    }
    while(item)
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
    if (topOfStack == NULL)
    {
        printf("Stack is empty\n");
        return;
    }
    struct geometricShapes* temp = *topOfStack;                 //create new pointer and put it on the top of the stack
    struct geometricShapes* previousElement = NULL;            //create pointer for previous element
    struct geometricShapes* deletableItem = NULL;
    struct geometricShapes* nextElement = NULL;
    temp = *topOfStack;
    int i = 0;
    if(number == 1)
    {
        *topOfStack = temp->nextItem;
        free(temp);
        temp->nextItem = NULL;
        return;
    }
    while(i < number - 2)
    {
        i++;
        *topOfStack = (*topOfStack)->nextItem;
        if (temp == NULL) {
            break;
        }

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
            continue;
        }
        convertToTheSameRegister(topOfStack->information.color);
        if (strcmp(topOfStack->information.color, tempString) == 0)
        {
            index++;
            printLine();
            outputFigure(topOfStack);
            printLine();
        }

        topOfStack = topOfStack->nextItem;

    }while(topOfStack);
    if (index == 0)
    {
        printf("There is no items with this color\n");
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
            printLine();
            outputFigure(topOfStack);
            printLine();
            index++;
        }
        (topOfStack) = (topOfStack)->nextItem;
    } while (topOfStack);
    if (index == 0)
    {
        printf("There is no items with this square\n");
    }
}

void seekByFloats(struct geometricShapes* topOfStack)
{
    int index = 0;
    printf("Enter a float to seek by it: \n");
    float number = inputValidationForFloat();
    if (topOfStack->flag)
    {
        do
        {
            if(topOfStack->information.perimeter == number)
            {
                printLine();
                outputFigure(topOfStack);
                printLine();
                index++;
            }
            (topOfStack) = (topOfStack)->nextItem;
        }while(topOfStack);
        if (index == 0)
        {
            printf("There is no items with this square\n");
        }
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

char* menuForSave(struct geometricShapes* topOfStack)
{
    char* nameOfTheFile;
    switch(menuForLoadAsFileChoice())
    {
        case 1:
        {
            nameOfTheFile = saveAsTextFile(topOfStack);
            return nameOfTheFile;
            break;
        }
        case 2:
        {
            break;
        }
        case 0:
        {
            break;
        }
    }
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

char* saveAsTextFile(struct geometricShapes* topOfStack)
{
    int n = 69;
    char* nameOfTheFile = enterFileName(TEXTFILE, nameOfTheFile);

    FILE* textFilePointer = fopen(nameOfTheFile, "w+");
    if (textFilePointer == NULL)
    {
        perror("Error occured while opening file\n");
        exit(0);
    }
    char table[] = "F i g u r ' s  t a b l e";
    fprintf(textFilePointer, "\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(textFilePointer, "%c", '-');
    }
    fprintf(textFilePointer, "\n");
    fprintf(textFilePointer, "|\t\t\t%-44s|\n", table);
    for (int i = 0; i < n; i++)
    {
        fprintf(textFilePointer, "%c", '-');
    }
    fprintf(textFilePointer, "\n");
    fprintf(textFilePointer, "|\t%-10s|\t\t%-12s|\t%-20s|\n", "SQUARE", "NAME", "PERIMETER/COLOR");
    for (int i = 0; i < n; i++)
    {
        fprintf(textFilePointer, "%c", '-');
    }
    while (topOfStack)
    {
        fprintf(textFilePointer, "\n");
        outputFigureToFle(topOfStack, textFilePointer);
        for (int i = 0; i < n; i++)
        {
            fprintf(textFilePointer, "%c", '-');
        }
        topOfStack = topOfStack->nextItem;
    }
    fclose(textFilePointer);
    return nameOfTheFile;
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

void menuForLoadFromFile(char* fileName, struct geometricShapes** topOfStack)
{

    switch(menuForLoadAsFileChoice())
    {
        case 1:
        {
            loadFromTextFile(&topOfStack, fileName);
            break;
        }
        case 2:
        {
            break;
        }
    }
}

/*void loadFromTextFile(struct geometricShapes** topOfStack, char* fileName)
{
    bool isType = false;
    struct geometricShapes* copyOfStack = *topOfStack;
    struct geometricShapes* tempStack = *topOfStack;
    FILE* filePointer = fopen(fileName, "r");
    while(!isType)
    {
        if(feof(filePointer))
        {
            isType = true;
            break;
        }
        if (!(*topOfStack = (struct geometricShapes*)calloc(1, sizeof(struct  geometricShapes))))
        {
            printf("Memory is not allocated\n");
            return;
        }
        fscanf(filePointer, "%d", &(*topOfStack)->square);
        fgets((*topOfStack)->name, 20, filePointer);
        if ((*topOfStack)->flag)
        {
            fscanf(filePointer, "%fl", &(*topOfStack)->information.perimeter);
        }
        else
        {
            fgets((*topOfStack)->information.color, 20, filePointer);
        }
        (*topOfStack)->nextItem = copyOfStack;
        copyOfStack = *topOfStack;
    }
    while ()
    fclose(filePointer);
}*/

void loadFromTextFile(struct geometricShapes** topOfStack, char* fileName)
{
    bool isType = false;
    struct geometricShapes* copyOfStack = *topOfStack;
    struct geometricShapes* tempStack = *topOfStack;
    FILE* filePointer = fopen(fileName, "r");
    while(!isType)
    {
        if(feof(filePointer))
        {
            isType = true;
            break;
        }
        if (!(copyOfStack = (struct geometricShapes*)calloc(1, sizeof(struct  geometricShapes))))
        {
            printf("Memory is not allocated\n");
            return;
        }
        fscanf(filePointer, "%d", &(copyOfStack)->square);
        fgets((copyOfStack )->name, 20, filePointer);
        if ((copyOfStack )->flag)
        {
            fscanf(filePointer, "%fl", &(copyOfStack)->information.perimeter);
        }
        else
        {
            fgets((copyOfStack)->information.color, 20, filePointer);
        }
        (copyOfStack)->nextItem = tempStack;
        tempStack = copyOfStack;
    }
//    while (copyOfStack)
//    {
//        Push()
//    }
//    while (!IsEmpty(stack))
//    {
//        Push(&newstack, Pop(&stack));
//    }
        fclose(filePointer);
}

//struct geometricShapes* push(struct geometricShapes** topOfStack, struct geometricShapes* item)
//{
//    struct geometricShapes *pointer = (struct geometricShapes *)calloc(1, sizeof(struct geometricShapes));
//    pointer = item;
//    pointer->nextItem = *topOfStack;
//    *topOfStack = pointer;
//
//    return *topOfStack;
//}
//
//struct geometricShapes* pop(struct geometricShapes** topOfStack)
//{
//    struct geometricShapes* pointer = *topOfStack;
//    *topOfStack = pointer->nextItem;
//    int value = node->value;
//    free(node);
//
//    return value;
//}
