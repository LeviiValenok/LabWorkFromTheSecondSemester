//
// Created by gaydi on 02.05.2021.
//
#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//function to insert a node in queue
void enqueue(struct GeometricShapes** head, struct GeometricShapes** tail)
{
    struct GeometricShapes* newItem;
    bool isType = true;
    if(!((newItem = (struct GeometricShapes*)malloc(sizeof(struct GeometricShapes)))))
    {
        printf("Memory is not allocated\n");
        return;
    }
    printf("Enter a square: \n");
    newItem->square = inputValidation(isType);
    printf("Enter a name: \n");
    rewind(stdin);
    fgets((newItem->name), 20, stdin);
    deleteSymbols((newItem->name));
    printf("\t 1  to enter a perimeter\n");
    printf("\t 2  to enter a color\n");
    switch(rightChoice())
    {
        case 1:
            printf("Enter a perimeter: \n");
            (newItem)->information.perimeter = inputValidationForFloat();
            (newItem)->flag = true;
            break;
        case 2:
            printf("Enter a color: \n");
            rewind(stdin);
            fgets((newItem->information.color), 20, stdin);
            deleteSymbols((newItem->information.color));
            (newItem)->flag = false;
            break;
    }
//    newItem->nextItem = NULL;
    if(*head == NULL)
    {
        *head = *tail = newItem;
    }
    else
    {
//        (*tail)->nextItem = newItem;
//        *tail = newItem;
        newItem->nextItem = *head;
        *head = newItem;
//        *tail = newItem;
//      newItem->nextItem = NULL;
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

int menuForChoice ()
{
    int choice;
    bool isTrue = true;
    printf("\t1 to insert elements to queue\n");
    printf("\t2 to output elements\n");
    printf("\t3 to delete item from queue\n");
    printf("\t4 to seek by option\n");
    printf("\t5 to save as file\n");
    printf("\t6 to load from file\n");
    printf("\t0 to exit\n");
    printf("Enter ---->");
    choice = inputValidation(isTrue);
    return choice;
}

void mainMenu()
{
    struct GeometricShapes* tail = NULL;
    struct GeometricShapes* head = NULL;
    bool isQuite = false;
    bool isType = true;
    while (!isQuite)
    {
        switch(menuForChoice())
        {
            case 1: {
                insertQueue(&tail, &head);
                break;
            }
            case 2:
            {
                outputContent(head);
                break;
            }
            case 3:
            {

                printf("Enter a number of element you want to delete\n");
                int number = inputValidation(isType);
                dequeue(&tail, &head, number);
                break;
            }
            case 4:
            {
                seekByOptions(&head);
                break;
            }
            case 5:
            {
                menuForSave(head);
                break;
            }
            case 6:
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

void insertQueue(struct GeometricShapes** tail, struct GeometricShapes** head)
{
    bool isQuite = false;
    struct GeometricShapes* queuePointer = *tail;
    do
    {

//        enqueue(tail, head);
        struct GeometricShapes* newItem;
        bool isType = true;
        if(!((newItem = (struct GeometricShapes*)malloc(sizeof(struct GeometricShapes)))))
        {
            printf("Memory is not allocated\n");
            return;
        }
        printf("Enter a square: \n");
        newItem->square = inputValidation(isType);
        printf("Enter a name: \n");
        rewind(stdin);
        fgets((newItem->name), 20, stdin);
        deleteSymbols((newItem->name));
        printf("\t 1  to enter a perimeter\n");
        printf("\t 2  to enter a color\n");
        switch(rightChoice())
        {
            case 1:
                printf("Enter a perimeter: \n");
                (newItem)->information.perimeter = inputValidationForFloat();
                (newItem)->flag = true;
                break;
            case 2:
                printf("Enter a color: \n");
                rewind(stdin);
                fgets((newItem->information.color), 20, stdin);
                deleteSymbols((newItem->information.color));
                (newItem)->flag = false;
                break;
        }
    newItem->nextItem = NULL;
        if(*head == NULL)
        {
            (*head) = newItem;
        }
        else
        {
//        (*tail)->nextItem = newItem;
//        *tail = newItem;
//            queuePointer->nextItem = newItem;
            (*tail)->nextItem = newItem;
//      newItem->nextItem = NULL;
        }
        (*tail) = newItem;
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

void outputFigure(struct GeometricShapes* pointer)
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

void outputContent(struct GeometricShapes* head)
{
    struct GeometricShapes* tempStorage;
    tempStorage = head;
    if (tempStorage == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        hatter();
//        tempStorage = head;
        while(tempStorage != NULL)
        {
            outputFigure(tempStorage);
            tempStorage = tempStorage->nextItem;
            printLine();
        }
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
// something get wrong with dequeue
// panic
void dequeue(struct GeometricShapes** tail, struct GeometricShapes** head, int number)
{

    int counter = 0;
    struct GeometricShapes* tempStorage;
    struct GeometricShapes* previousItem;
    previousItem = (*head);
    tempStorage = (*head)->nextItem;
    if (number == 0)
    {
        (*head)=(*head)->nextItem;
        free(previousItem);
        printf("Removal was successful\n");
        return;
    }
    if (!*head)
    {
        printf("Queue is empty\n");
        return;
    }
    if (*head == *tail)
    {
        free(*tail);
        *tail=*head = NULL;
        printf("Removal was successful\n");
        return;
    }


//    tempStorage = (*head)->nextItem;

    while(tempStorage != NULL)
    {
        for (int i = 1; i < number ; i++)
        {
            previousItem = previousItem->nextItem;
            tempStorage = tempStorage->nextItem;
        }

//      previousItem->nextItem = tempStorage ->nextItem;
        if (!(tempStorage->nextItem)) {
            previousItem->nextItem = tempStorage->nextItem;
            free(tempStorage);
            printf("Removal was successful\n");
            return;
        }
        previousItem->nextItem = tempStorage->nextItem;
        free(tempStorage);
//            *head = tempStorage->nextItem;
//            free(tempStorage);
//            tempStorage = previousItem = *head;
        /*tempStorage = *head;
        *head = (*head)->nextItem;*/
//            free(tempStorage);
//            tempStorage = previousItem->nextItem;
        printf("Removal was successful\n");
        return;




//                *head = (*head)->nextItem;



    }

}

void seekByOptions(struct GeometricShapes** head)
{
    bool isQuite = false;
    while(!isQuite)
    {
        switch (menuForSeek())
        {
            case 1:
            {
                seekByColor(*head);
                break;
            }
            case 2:
            {
//                seekByFloats(*topOfStack); //check it
                break;
            }
            case 3:
            {
//                seekByIntegers(*topOfStack);
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

void seekByColor(struct GeometricShapes* head)
{
    int index = 0;
    printf("Enter a string to compare\n");
//    char tempString[20];
    char *tempString = (char*) calloc(20, sizeof(char));
    rewind(stdin);
    gets(tempString);
    convertToTheSameRegister(tempString);
    do
    {
        if (head->flag)
        {
            continue;
        }
        convertToTheSameRegister(head->information.color);
        if (strcmp(head->information.color, tempString) == 0)
        {
            index++;
            if(index == 1)
            {
                hatter();
            }
//            printLine();
            outputFigure(head);
            printLine();
        }

        head = head->nextItem;

    }while(head);
    if (index == 0)
    {
        printf("There is no items with this color\n");
        return;
    }
    return;
}

int menuForLoadFromFile()
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


void menuForSave(struct GeometricShapes* head)
{
    switch(menuForLoadAsFileChoice())
    {
        case 1:
        {
            saveAsTextFile(head);
//            saveAsTextFile(head);
            break;
        }
        case 2:
        {
//            saveAsBinaryFile(head);
            break;
        }
        case 0:
        {
            break;
        }
    }
}


void saveAsTextFile(struct GeometricShapes* head)
{
//    int n = 69;
//    char* nameOfTheFile = enterFileName(TEXTFILE, nameOfTheFile);
    char nameOfTheFile [] = "Test.txt";
    FILE* textFilePointer = fopen(nameOfTheFile, "w+");
    if (textFilePointer == NULL)
    {
        perror("An error occurred while opening the file\n");
        exit(0);
    }
    rewind(textFilePointer);
    while (head)
    {
        if(head->flag)
        {
//            fprintf(textFilePointer, "%d\n%s\n%fl\n", topOfStack->square, topOfStack->name)
            fprintf(textFilePointer, "%d\n", head->square);
            fprintf(textFilePointer, "%s\n", head->name);
            fprintf(textFilePointer, "%fl\n", head->information.perimeter);
        }
        else
        {
            fprintf(textFilePointer, "%d\n", head->square);
            fprintf(textFilePointer, "%s\n", head->name);
            fprintf(textFilePointer, "%s\n", head->information.color);
        }
        head = head->nextItem;
    }
    /*fseek(textFilePointer, 1, SEEK_END);
    fprintf(textFilePointer, "%c", "\0");*/
    fclose(textFilePointer);
}

void loadFromFileToQueue(struct GeometricShapes **head, struct GeometricShapes** tail)
{
    switch(menuForLoadFromFile())
    {
        case 1:
        {
            break;
        }
        case 2:
        {
            break;
        }
    }
}