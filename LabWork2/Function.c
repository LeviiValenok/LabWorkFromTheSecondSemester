#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Header.h"
#include <ctype.h>


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

void menu(struct geometricShapes* pointer, int numberOfFigures)
{

    _Bool quite = false;
    while (!quite)
    {
        switch(mainMenu())
        {
            case 1:
                printf("Enter a number of figures: \n");
                numberOfFigures = inputValidation();
                pointer= menuForEnterArrayOfStructure(pointer, numberOfFigures);
                break;
            case 2:
                menuForOutput(pointer, numberOfFigures);
                break;
            case 3:

                printf("Enter a number of new elements: \n");
                int numberOfNewElements = inputValidation();
                pointer = addNewElements(pointer, numberOfFigures, numberOfNewElements);
                numberOfFigures += numberOfNewElements;
                break;
            case 4:
               switch(menuForSeek())
               {
                   case 1:
                       {
                           char tempString[20];
                           printf("Enter an option to compare with\n");
                           printf("Enter ----> ");
                           scanf("%s", &tempString, sizeof(tempString));
                           seekByCharOptions(pointer, numberOfFigures, tempString, COLOR);
                       }
                       break;
                   case 2:
                       seekByIntegerOrFloatOptions(pointer, numberOfFigures,PERIMETER);
                       break;
                   case 3:
                       seekByIntegerOrFloatOptions(pointer, numberOfFigures, SQUARE);
                       break;

               }
                break;
            case 5:
                switch(menuForDelete())
                {
                    case 1:
                    {
                        int index;
                        char compareString[20];
                        printf("Enter a name to seek by: \n");
                        rewind(stdin);
                        gets(compareString);
                        for (int i = 0; i < numberOfFigures; i++)
                        {
                            index = seekByName(pointer, numberOfFigures, compareString);
                            if (index == -1)
                            {
                                printf("There is no item with this name\n");
                                break;
                            }
                            numberOfFigures = deleteOneStructure(pointer, numberOfFigures, index);
                            i--;
                        }
                        break;
                    }
                    case 2:
                        numberOfFigures = deleteAll(pointer, numberOfFigures);
                        break;
                    case 3:
                    {
                        int index;
                        char compareString[20];
                        printf("Enter a name to seek by: \n");
                        rewind(stdin);
                        gets(compareString);
                        for (int i = 0; i < numberOfFigures; i++)
                        {
                            index = seekByColor(pointer, numberOfFigures, compareString);
                            if (index == -1)
                            {
                                printf("There is no item with this name\n");
                                break;
                            }
                            numberOfFigures = deleteOneStructure(pointer, numberOfFigures, index);
                            i--;
                        }
                        break;
                    }
                }
                break;
            case 0:
                quite = true;
                free(pointer);
                break;
        }
    }
}

int mainMenu()
{
    int choice;
    printf("\t1 to enter an information about figures\n");
    printf("\t2 to output structure\n");
    printf("\t3 to add new structure\n");
    printf("\t4 to seek by options\n");
    printf("\t5 to delete by options\n");
    printf("\t0 to exit\n");
    printf("Enter ----> ");
    choice = inputValidation();
    return choice;
}

struct geometricShapes*
        allocateArrayOfStructures(struct geometricShapes* pointer , int numberOfFigures)
{

    if (!(pointer = (struct geometricShapes*)malloc(numberOfFigures*sizeof(struct geometricShapes))))
    {
        printf("An error has occurred\n");
        //it's not correct
    }
    return pointer;

}
void enterArrayOfStructure(struct geometricShapes* pointer, int index)
{

    printf("\n");
    printf("Enter a square: \n");
    (pointer + index)->square = inputValidation();
    printf("Enter a name: \n");
    rewind(stdin);
    gets((pointer + index)->name);

    printf("\t 1  to enter a perimeter\n");
    printf("\t 2  to enter a color\n");
    switch(rightChoice())
    {
        case 1:
            printf("Enter a perimeter: \n");
            (pointer + index)->information.perimeter = inputValidationForFloat();
            (pointer + index)->flag = true;
            break;
        case 2:
            printf("Enter a color: \n");
            rewind(stdin);
            gets((pointer + index)->information.color);
            (pointer + index)->flag = false;
            break;
    }


}
struct geometricShapes*
        menuForEnterArrayOfStructure(struct geometricShapes* pointer , int numberOfFigures)
{

    pointer = allocateArrayOfStructures(pointer, numberOfFigures);
    for (int i = 0; i < numberOfFigures; i++)
    {
        enterArrayOfStructure(pointer, i);
    }
    return pointer;
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
void outputStructures(struct geometricShapes* pointer, int numberOfFigures)
{

    char table[] = "F i g u r ' s  t a b l e";
    printf("\n");
    printLine();
    printf("|\t\t\t%-44s|\n", table);
    printLine();
    printf("|\t%-10s|\t\t%-12s|\t%-20s|\n", "SQUARE", "NAME", "PERIMETER/COLOR");
    printLine();
    for (int i = 0; i < numberOfFigures; i++)
    {
        outputFigure(pointer, i);
        printLine();
    }
}
void outputFigure(struct geometricShapes* pointer, int index)
{
    if ((pointer + index)->flag)
    {
        printf("|\t%-10d|\t%-20s|\t%-20.3f|\n", (pointer + index)->square, (pointer + index)->name,
               (pointer + index)->information.perimeter);
    }
   else
    {
        printf("|\t%-10d|\t%-20s|\t%-20s|\n", (pointer + index)->square, (pointer + index)->name,
               (pointer + index)->information.color);
    }
}
void menuForOutput(struct geometricShapes* pointer, int numberOfFigures)
{
    outputStructures(pointer, numberOfFigures);
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
struct geometricShapes*
        addNewElements(struct geometricShapes* pointer, int numberOfFigures, int numberOfNewElements)
{
//    struct geometricShapes** result;
    pointer = (struct geometricShapes*)realloc(
        pointer,
        (numberOfFigures + numberOfNewElements) * sizeof(struct geometricShapes)
    );
    for (int i = numberOfFigures; i < numberOfFigures + numberOfNewElements; i++)
    {
        enterArrayOfStructure(pointer, i);
    }

    return pointer;
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
void seekByCharOptions(struct geometricShapes* pointer, int numberOfFigures, char* string, enum charType type)
{
    int* arrayOfIndexes = (int*)calloc(numberOfFigures, sizeof(int));
    int k = 0, length;
    length = strlen(string);
    int j = 0;
    switch(type)
    {
        case COLOR:
        {
            for (int i = 0; i < numberOfFigures; i++)
            {
                if ((pointer + i)->flag)
                {
                    continue;
                }
                convertToTheSameRegister(string);
                convertToTheSameRegister((pointer + i)->information.color);
                for (j = 0; j < length + 1; j++)
                {
                    if (string[j] == (pointer + i)->information.color[j])
                    {
                        if (string[j] == '\0')
                        {
                            arrayOfIndexes[k] = i;
                            k++;
                            continue;
                        }
                    }
                    else
                    {
                        break;
                    }

                }
                j = 0;
            }
            arrayOfIndexes = (int*)realloc(arrayOfIndexes, k + 1);
            break;
        }

    }

//    int numberOfCoincidences = sizeof(arrayOfIndexes)/sizeof(int);
    for (int i = 0; i < k; i++)
    {
        printLine();
        outputFigure(pointer, arrayOfIndexes[i]);
        printLine();
    }
}
void seekByIntegerOrFloatOptions(struct geometricShapes* pointer, int numberOfFigures,
        enum Type type)
{
    switch (type)
    {
        case PERIMETER:
        {
            float number;
            int k = 0;
            printf("\n");
            printf ("Enter a number to compare with: \n");
            number = inputValidationForFloat();
            int* suitableItems = (int*)calloc(numberOfFigures, sizeof(int));
            for (int i = 0; i < numberOfFigures; i++)
            {
                if ((pointer + i)->flag == false)
                {
                    continue;
                }
                if ((pointer + i)->information.perimeter == number)
                {
                    suitableItems[k] = i;
                    k++;
                }
            }
            if (k == 0)
            {
                printf("There are no such items \n");
                free(suitableItems);
                break;
            }
            suitableItems = (int*)realloc(suitableItems, (k + 1)*sizeof(int));
            printLine();
            printf("|\t%-10s|\t\t%-12s|\t%-20s|\n", "SQUARE", "NAME", "PERIMETER/COLOR");
            printLine();
            for (int i = 0; i < k; i++)
            {
                outputFigure(pointer, suitableItems[i]);
                printLine();
            }
            break;
        }
        case SQUARE:
        {
            int k = 0;
            printf("\n");
            printf("Enter a number to compare with: \n");
            int number = inputValidation();
            int* suitableItems = (int*)calloc(numberOfFigures, sizeof(int));
            for (int i = 0; i < numberOfFigures; i++)
            {
                if ((pointer + i)->square == number)
                {
                    suitableItems[k] = i;
                    k++;
                }
            }
            if (k == 0)
            {
                printf("There are no such items \n");
                free(suitableItems);
                break;
            }
            suitableItems = (int*)realloc(suitableItems, (k + 1)*sizeof(int));
            printLine();
            printf("|\t%-10s|\t\t%-12s|\t%-20s|\n", "SQUARE", "NAME", "PERIMETER/COLOR");
            printLine();
            for (int i = 0; i < k; i++)
            {
                outputFigure(pointer, suitableItems[i]);
                printLine();
            }
            break;
        }

    }
}
int menuForSeek()
{
    printf("\n");
    printf("\t1 to seek by color\n");
    printf("\t2 to seek by perimeter\n");
    printf("\t3 to seek by square\n");
    printf("Enter ----> ");
    int choice = inputValidation();
    return choice;
}

int deleteOneStructure(struct geometricShapes* pointer, int numberOfFigures, int index)
{
    for (int i = index; i < numberOfFigures - 1; i++)
    {
        *(pointer + i) = *(pointer + i + 1);
    }
    numberOfFigures = numberOfFigures - 1;
    pointer = (struct geometricShapes*)realloc(pointer, numberOfFigures*sizeof(struct geometricShapes));
    return numberOfFigures;
}

int menuForDelete()
{
    int choice;
    printf("\n");
    printf("\t1 to delete items by name\n");
    printf("\t2 to delete all\n");
    printf("\t3 to delete by given color\n");
    choice = inputValidation();
    return choice;
}

int seekByName(struct geometricShapes* pointer, int numberOfFigures, char* compareString)
{
    int flag = 0;
    convertToTheSameRegister(compareString);
    for (int i = 0; i < numberOfFigures; i++)
    {
        convertToTheSameRegister((pointer + i)->name);
        if (strcmp((pointer + i)->name, compareString) == 0)
        {
            flag++;
            return i;
        }
    }
    if (flag == 0)
    {
        return -1;
    }

}

int deleteAll(struct geometricShapes* pointer, int numberOfFigures)
{
    for (int i = 0; i < numberOfFigures - 1; i++)
    {
        *(pointer + i) = *(pointer + i + 1);
    }
    numberOfFigures = 0;
    return numberOfFigures;
}

int seekByColor(struct geometricShapes* pointer, int numberOfFigures, char* compareString)
{
    int flag = 0;
    convertToTheSameRegister(compareString);
    for (int i = 0; i < numberOfFigures; i++)
    {
        if ((pointer + i)-> flag)
        {
            continue;
        }
        convertToTheSameRegister((pointer + i)->information.color);
        if (strcmp((pointer + i)->information.color, compareString) == 0)
        {
            flag++;
            return i;
        }
    }
    if (flag == 0)
    {
        return -1;
    }

}
