//
// Created by gaydi on 02.05.2021.
//
#include <stdio.h>
#include "header.h"
#include <stdlib.h>

//function to insert a node in queue
void enqueue(struct GeometricShapes** head, struct GeometricShapes** tail)
{
    bool isType = true;
    struct GeometricShapes* newItem = (struct GeometricShapes*)malloc(sizeof(struct GeometricShapes));
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
    if((*head == NULL)&&(*tail == NULL))
    {
        *head = *tail = newItem;
    }
    else
    {
        (*tail)->nextItem = newItem;
        *tail = newItem;
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
    printf("\t1 to add elements to queue\n");
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
                addToQueue(&tail, &head);
                break;
            }
            case 2:
            {
                outputContent(tail,head);
                break;
            }
            case 3:
            {

                printf("Enter a number of element you want to delete\n");
                int number = inputValidation(isType);
                dequeue(&tail, &head, number);
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

void addToQueue(struct GeometricShapes** tail, struct GeometricShapes** head)
{
    bool isQuite = false;
    do
    {
        enqueue(tail, head);
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

void outputContent(struct GeometricShapes* tail, struct GeometricShapes* head)
{
    struct GeometricShapes* tempStorage;
    if (head== NULL && tail == NULL)
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        hatter();
        tempStorage = head;
        while(tempStorage)
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

void dequeue(struct GeometricShapes** tail, struct GeometricShapes** head, int number)
{
    number--;
    int counter = 0;
    struct GeometricShapes* tempStorage;
    struct GeometricShapes* previousItem;

    tempStorage = (*head)->nextItem;
    previousItem = (*head);

    if (*head == *tail)
    {
        free(*tail);
        *tail=*head = NULL;
        printf("Removal was successful\n");
        return;
    }
    else
    {
        while(tempStorage != NULL)
        {
            if (counter == number)
            {
                previousItem->nextItem = tempStorage ->nextItem;
                /*tempStorage = *head;
                *head = (*head)->nextItem;*/
                free(tempStorage);
                tempStorage = previousItem->nextItem;
                printf("Removal was successful\n");
                return;
            }
            else
            {
                counter++;
                tempStorage = tempStorage->nextItem;
                previousItem = previousItem->nextItem;
//                *head = (*head)->nextItem;
            }

        }
    }

}