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
                loadFromFileToQueue(&head, &tail);
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
                seekByFloats(*head); //check it
                break;
            }
            case 3:
            {
                seekByIntegers(*head);
                break;
            }
            case 4:
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
    struct GeometricShapes* tempPointer = head;
    rewind(stdin);
    gets(tempString);
    convertToTheSameRegister(tempString);
    do
    {
        if (tempPointer->flag)
        {
            tempPointer = tempPointer->nextItem;
            continue;
        }
        convertToTheSameRegister(tempPointer->information.color);
        if (strcmp(tempPointer->information.color, tempString) == 0)
        {
            index++;
            if(index == 1)
            {
                hatter();
            }
//            printLine();
            outputFigure(tempPointer);
            printLine();
        }

        tempPointer = tempPointer->nextItem;

    }while(tempPointer);
    if (index == 0)
    {
        printf("There is no items with this color\n");
        return;
    }
}

void seekByFloats(struct GeometricShapes *head)
{
        struct GeometricShapes* tempPointer = head;
        int index = 0;
        printf("Enter a float to seek by it: \n");
        float number = inputValidationForFloat();
        if (!(tempPointer->flag))
        {
            (tempPointer) = (tempPointer)->nextItem;
        }
        do
        {
            if(tempPointer->information.perimeter == number)
            {
                index++;
                if(index == 1)
                {
                    hatter();
                }
    //                printLine();
                outputFigure(tempPointer);
                printLine();

            }
            (tempPointer) = (tempPointer)->nextItem;
        }while(tempPointer);
        if (index == 0)
        {
            printf("There is no items with this square\n");
            return;
    }

}

void seekByIntegers(struct GeometricShapes* head)
{
    struct GeometricShapes* tempPointer = head;
    int number, index = 0;
    bool isTrue = true;
    printf("Enter an integer to seek by it: \n");
    number = inputValidation(isTrue);

    do
    {
        if (tempPointer->square == number)
        {
            index++;
            if(index == 1)
            {
                hatter();
            }
//            printLine();
            outputFigure(tempPointer);
            printLine();

        }
        (tempPointer) = (tempPointer)->nextItem;
    } while (tempPointer);
    if (index == 0)
    {
        printf("There is no items with this square\n");
        return;
    }

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
            break;
        }
        case 2:
        {
            saveAsBinaryFile(head);
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

    char *nameOfTheFile = enterFileName(TEXTFILE);
    FILE* textFilePointer;
    if (!(textFilePointer = fopen(nameOfTheFile, "w+")))
    {
        printf("File was not created\n");
        return;
    }

        rewind(textFilePointer);
        while (head) {
            if (head->flag)
            {
                fprintf(textFilePointer, "%d\n", head->square);
                fprintf(textFilePointer, "%s\n", head->name);
                fprintf(textFilePointer, "%d\n", 1);
                fprintf(textFilePointer, "%fl\n", head->information.perimeter);
            } else {
                fprintf(textFilePointer, "%d\n", head->square);
                fprintf(textFilePointer, "%s\n", head->name);
                fprintf(textFilePointer, "%d\n", 0);
                fprintf(textFilePointer, "%s\n", head->information.color);
            }
            head = head->nextItem;
        }
        /*fseek(textFilePointer, 1, SEEK_END);
        fprintf(textFilePointer, "%c", "\0");*/
        fclose(textFilePointer);
}


void saveAsBinaryFile(struct GeometricShapes* head)
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
    while (head)

    {
        if (head->flag)
        {

            fwrite(&(head->square), sizeof(int), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&(head->name), strlen(head->name), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&flagTrue, sizeof(int), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&(head->information.perimeter), sizeof(float), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
        }
        else
        {
            fwrite(&(head->square), sizeof(int), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&(head->name), strlen(head->name), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&flagFalse, sizeof(int), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
            fwrite(&(head->information.color), strlen(head->information.color), 1, binaryFile);
            fwrite (&letter, sizeof(char), 1, binaryFile);
        }
        head = head->nextItem;
    }
    rewind(binaryFile);
    fclose(binaryFile);
}


void loadFromFileToQueue(struct GeometricShapes **head, struct GeometricShapes** tail)
{
    switch(menuForLoadFromFile())
    {
        case 1:
        {
            int flag;
            char *nameOfFile = enterFileName(TEXTFILE);
            FILE *textFile;
            if ((textFile = fopen(nameOfFile, "r")) == NULL) {
                printf("File not founded\n");
                return;
            }
            rewind(textFile);
            while (!feof(textFile))
            {
                struct GeometricShapes *newElement;
                if (!(newElement = (struct GeometricShapes *) calloc(1, sizeof(struct GeometricShapes)))) {
                    printf("Memory is not allocated\n");
                    return;
                }
                fscanf(textFile, "%d", &(newElement->square));
                if ((newElement)->square == 0)
                {
                    break;
                }
                fseek(textFile, 2, SEEK_CUR);
                fgets(newElement->name, 20, textFile);
                deleteSymbols(newElement->name);
                fscanf(textFile, "%d", &flag);
                fseek(textFile, 2, SEEK_CUR);
                if (flag == 1) {
                    newElement->flag = true;
                    fscanf(textFile, "%f", &(newElement)->information.perimeter);
                } else {
                    fgets((newElement)->information.color, 20, textFile);
                    deleteSymbols(newElement->information.color);
                    newElement->flag = false;
                }
                fseek(textFile, 2, SEEK_CUR);
                newElement->nextItem = NULL;
                if (*head == NULL) {
                    (*head) = newElement;
                } else {
                    (*tail)->nextItem = newElement;
                }
                (*tail) = newElement;
            }
            fclose(textFile);
            if (*head == NULL) {
                printf("The contents of the file were not pushed onto the stack\n");
            } else {
                printf("The contents of the file were pushed onto the stack successful\n");
            }
            break;
        }


        case 2:
        {
            struct GeometricShapes *newElement;
            char *nameOfFile = enterFileName(BINARYFILE);
            char letter, indicator;
            int flag;
            char *tempString = (char *) calloc(20, sizeof(char));
            int i = 0;
            FILE *binaryFile;
            if ((binaryFile = fopen(nameOfFile, "rb")) == NULL) {
                printf("File not founded\n");
                return;
            }
            rewind(binaryFile);
            while (!feof(binaryFile))
            {
                if (!(newElement = (struct GeometricShapes *)calloc(1, sizeof(struct GeometricShapes)))) {
                    printf("Memory was not allocated\n");
                    return;
                }
                fread(&((newElement)->square), sizeof(int), 1, binaryFile);
                fread(&indicator, sizeof(char), 1, binaryFile);
                if ((newElement)->square == 0)
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
                strcpy((newElement)->name, tempString);
                tempString[0] = '\0';
                fread(&flag, sizeof(int), 1, binaryFile);
                if (flag == 1)
                {
                    (newElement)->flag = true;
                    fread(&indicator, sizeof(char), 1, binaryFile);
                    fread(&((newElement)->information.perimeter), sizeof(float), 1, binaryFile);
                }
                else
                {
                    (newElement)->flag = false;
                    fread(&indicator, sizeof(char), 1, binaryFile);
                    letter = '\0';
                    i = 0;
                    tempString[0] = '\0';
                    while (letter != ' ')
                    {
                        fread(&letter, sizeof(char), 1, binaryFile);
                        tempString[i] = letter;
                        i++;
                    }
                    tempString[i - 1] = '\0';
                    letter = '\0';
                    i = 0;
                    strcpy((newElement)->information.color, tempString);
                    deleteSymbols(((newElement))->information.color);
                    tempString[0] = '\0';

                }
                fread(&indicator, sizeof(char), 1, binaryFile);


                newElement->nextItem = NULL;
                if (*head == NULL)
                {
                    (*head) = newElement;
                } else
                {
                    (*tail)->nextItem = newElement;
                }
                (*tail) = newElement;
                tempString[0]='\0';
                letter = '\0';
                i = 0;
                if (feof(binaryFile))
                {
                    break;
                }
            }

            if (*head == NULL)
            {
                printf("The contents of the file were not pushed onto the stack\n");
            } else
            {
                printf("The contents of the file were pushed onto the stack successful\n");
            }
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