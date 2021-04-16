//
// Created by gaydi on 14.04.2021.
//

#include "Header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <stdbool.h>

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
    printf("\t5 to save list as text file\n");
    printf("\t6 to load list from text file\n");
    printf("\t7 to save list as binary file\n");
    printf("\t8 to load list from binary file\n");
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
        printf("Do you want to add more?\n");
        printf("\1 to add more\n");
        printf("\2 to quite\n");
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
    struct geometricShapes* previousElement = NULL;             //create pointer for previous element
    temp = *topOfStack;
    int i = 0;
    while(i < number - 1)
    {
        i++;
        temp = (temp)->nextItem;
        if (temp == NULL)
        {
            break;
        }

    }
    if(temp == *topOfStack)
    {
        *topOfStack = temp->nextItem;
        free(temp);
        temp->nextItem = NULL;
    }
    else
    {

        previousElement->nextItem = temp ->nextItem;            //connect lint from previous item to next item
        free(temp);
        temp->nextItem = NULL;
    }
    previousElement= temp;
    temp = temp->nextItem;

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
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
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