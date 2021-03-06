#include "Header.h"

struct Reader*
    inputArrayOfStructure(struct Reader* pointer, int numberOfReaders, int start)
{
    for (int i = 0; i < numberOfReaders; i++)
    {
        rewind(stdin);
        printf("Enter a last name: \n");
        scanf_s("%s", &(pointer + i)->lastName, sizeof((pointer + i)->lastName));

        rewind(stdin);
        printf("Enter a first name: \n");
        scanf_s("%s", &(pointer + i)->firstName, sizeof((pointer + i)->firstName));

        rewind(stdin);
        printf("Enter a patronymic name: \n");
        scanf_s("%s", &(pointer + i)->patronymicName, sizeof((pointer + i)->patronymicName));

        rewind(stdin);
        printf("Enter a library card number: \n");
        //scanf_s("%d", &(pointer + i)->libraryCardNumber);
        (pointer + i)->libraryCardNumber = inputValidation();

        printf("Enter a name of the book: \n");
        rewind(stdin);
        fgets((pointer + i)->nameOfTheBook, 20, stdin);
        deleteSymbols((pointer + i)->nameOfTheBook);

        rewind(stdin);
        printf("Enter a return period: \n");
        //scanf_s("%d", &(pointer + i)->returnPeriod);
        (pointer + i)->returnPeriod = inputValidation();

        rewind(stdin);
        printf("Enter a unit of measurement: \n");
        scanf_s("%s", &(pointer + i)->unitOfMeasurement, sizeof((pointer + i)->unitOfMeasurement));
    }

    return pointer;
}
int inputValidation()
{
    int number;
    char c;
    while (scanf_s("%d%c", &number, &c) != 2 || c != '\n' || number < 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return number;
}

void outputStructures(struct Reader* pointer, int numberOfReaders)
{
    char table[] = "R e a d e r s  t a b l e";
    printLine();
    printf("|\t\t\t %-80s |\n", table);
    printLine();
    printf("|\t%-10s|\t%-10s|\t%-10s|\t%-10s|\t%-10s|\t%-5s|\t%-10s|\n", "LAST NAME", "FIRST NAME", "PATR.NAME",
        "CARD NUMBER", "BOOK NAME", "PERIOD", "UOM");
    printLine();
    for (int i = 0; i < numberOfReaders; i++)
    {
        outputPerson(pointer, i);
        printLine();
    }
}

void outputPerson(struct Reader* pointer, int index)
{
    printf("|\t%-10s|\t%-10s|\t%-10s|\t%-10d|\t%-10s|\t%-5d|\t%-10s|\n",
        (pointer + index)->lastName, (pointer + index)->firstName,
        (pointer + index)->patronymicName, (pointer + index)->libraryCardNumber,
        (pointer + index)->nameOfTheBook, (pointer + index)->returnPeriod,
        (pointer + index)->unitOfMeasurement);
}

void printLine()
{
    int n = 107;
    for (int i = 0; i < n; i++)
    {
        printf("%c", '-');
    }
    printf("\n");
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

int menuWithMainChoice()
{

    int choice;
    printf("\n");
    printf("\t1 if you want to input readers\n");
    printf("\t2 if you want to output readers\n");
    printf("\t3 if you want to change field\n");
    printf("\t4 if you want to seek by options\n");
    printf("\t5 if you want to sort\n");
    printf("\t6 if you want to delete a structure\n");
    printf("\t7 if you want to seek partly\n");
    printf("\t0 if you want to go out\n");
    printf("\n");
    printf("Enter ---->  ");
    choice = inputValidation();
    return choice;
}

int menuForSort()
{
    int n;
    printf("\n");
    printf("\t1 if you want to sort library card number ascending\n");
    printf("\t2 if you want to sort library card number descending\n");
    printf("\t3 if you want to sort last names alphabetically\n");
    printf("\t4 if you want to sort book names alphabetically\n");
    printf("\t5 if you want to sort last names in reverse order\n");
    printf("\t6 if you want to sort book names in reverse order\n");
    printf("\t0 if you don't want to sort anything\n");
    printf("\n");
    printf("Enter ---->  ");
    n = inputValidation();
    return n;
}

int menuForChange()
{
    int n;
    printf("\n");
    printf("Enter a field that you want to chande\n");
    printf("\t1 if you want to change last name \n");
    printf("\t2 if you want to change first name \n");
    printf("\t3 if you want to change patronymic name\n");
    printf("\t4 if you want to change name of the Book\n");
    printf("\t5 if you want to change return period\n");
    printf("\t6 if you want to change unit of measure\n");
    printf("\t0 if you don't want to change anything\n");
    printf("\n");
    printf("Enter ---->  ");
    n = inputValidation();
    return n;
}

int menuForSeekByOptions()
{
    int n;
    printf("Choose the option for the search:\n");
    printf("\t1 if you want to search by last name\n");
    printf("\t2 if you want to search by first name\n");
    printf("\t3 if you want to search by patronymic name\n");
    printf("\t4 if you want to search by name of the Book\n");
    printf("\t5 if you want to search by library card\n");
    printf("\t6 if you want to search by return period\n");
    printf("\t0 if you don't want to search\n");
    printf("\n");
    printf("Enter ---->  ");
    n = inputValidation();
    return n;

}

int menuForDelete()
{
    int n;
    printf("\n");
    printf("\t1 if you want delete by library card number\n");
    printf("\t2 if you want delete by last name\n");
    printf("\t0 if you want to exit\n");
    printf("\n");
    printf("Enter ---->  ");
    n = inputValidation();
    return n;
}

int menuForPartialSort()
{
    int n;
    printf("\t1 if you want to search in last name field\n");
    printf("\t2 if you want to search in book name name field\n");
    printf("\t0 if want to quite\n");
    printf("\n");
    printf("Enter ---->  ");
    n = inputValidation();
    return n;
}

struct Reader*
    allocateMemory(struct Reader* pointer, int numberOfReaders)
{
    if (!(pointer = (struct Reader*)calloc(numberOfReaders, sizeof(struct Reader))))
    {
        printf("Memory is not allocated\n");
        return 1;
    }   
    return pointer;
}

int findIndexByLibraryCardNumber(struct Reader* pointer,int libraryCardNumber,int numberOfReaders)
{
    int index;
    for (int i = 0; i < numberOfReaders; i++)
    {
        if ((pointer + i)->libraryCardNumber == libraryCardNumber)
        {
            return i;
        }
    }
    return -1;
}

int* seekByCharOptions(struct Reader* pointer, int numberOfReaders, char* string, enum fieldCharType type)
{
    int* arrayOfIndexes = (int*)malloc(numberOfReaders*(sizeof(int)));
    int k = 0, length;
    length = strlen(string);
    int j = 0;
    switch (type)
    {
        case LASTNAME:
        {
            for (int i = 0; i < numberOfReaders; i++)
            {
                convertToTheSameRegistr(string);
                convertToTheSameRegistr((pointer + i)->lastName);
                for (j = 0; j < length + 1; j++)
                {
                    if (string[j] == (pointer + i)->lastName[j])
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
                    }
                }
                j = 0;
            }
            if (k > 0)
            {
                return arrayOfIndexes;
            }
            else
            {
                return -1;
            }
            break;
        }
        case FIRSTNAME:
        {
            for (int i = 0; i < numberOfReaders; i++)
            {
                convertToTheSameRegistr(string);
                convertToTheSameRegistr((pointer + i)->firstName);
                for (j = 0; j < length + 1; j++)
                {
                    if (string[j] == (pointer + i)->firstName[j])
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
                    }
                }
                j = 0;
            }
            if (k > 0)
            {
                return arrayOfIndexes;
            }
            else
            {
                return -1;
            }
            break;
        }
        case PATRONYMICNAME:
        {
            for (int i = 0; i < numberOfReaders; i++)
            {
                convertToTheSameRegistr(string);
                convertToTheSameRegistr((pointer + i)->patronymicName);
                for (j = 0; j < length + 1; j++)
                {
                    if (string[j] == (pointer + i)->patronymicName[j])
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
            if (k > 0)
            {
                return arrayOfIndexes;
            }
            else
            {
                return -1;
            }
            break;
        }
        case NAMEOFTHEBOOK:
        {
            for (int i = 0; i < numberOfReaders; i++)
            {
                convertToTheSameRegistr(string);
                convertToTheSameRegistr((pointer + i)->nameOfTheBook);
                for (j = 0; j < length + 1; j++)
                {
                    if (string[j] == (pointer + i)->nameOfTheBook[j])
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
            if (k > 0)
            {
                return arrayOfIndexes;
            }
            else
            {
                return -1;
            }
            break;
        }
        default:
            printf("Try again\n");
            break;
    }
}
int* seekByIntOptions(struct Reader* pointer, int numberOfReaders, int number, enum fieldIntType type)
{
    int* arrayOfIndexes = (int*)calloc(numberOfReaders, sizeof(int));
    int k = 0;
    for (int i = 0; i < numberOfReaders; i++)
    {
        if ((pointer + i)->returnPeriod == number)
        {
            arrayOfIndexes[k] = i;
            k++;
        }
    }
    if (k > 0)
    {
        return arrayOfIndexes;
    }
    else
    {
        return -1;
    }
}
void convertToTheSameRegistr(char* string)
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

void sortByIntOtionsAscending(struct Reader* pointer, int numberOfReaders, enum fieldIntType type)
{
    switch (type)
    {
        case LIBRARYCARDNUMBER:
        {
            struct Reader temp;
            for (int i = 0; i < numberOfReaders - 1; i++)
            {
                for (int j = (numberOfReaders - 1); j > i; j--)
                {
                    if ((pointer + j - 1)->libraryCardNumber > (pointer + j)->libraryCardNumber)
                    {
                        struct Reader temp = *(pointer + j);
                        *(pointer + j) = *(pointer + j - 1);
                        *(pointer + j - 1) = temp;
                    }
                }
            }
        }
        break;

    }
}
void sortByIntOtionsDescending(struct Reader* pointer, int numberOfReaders, enum fieldIntType type)
{
    switch (type)
    {
    case LIBRARYCARDNUMBER:
    {
        struct Reader temp;
        for (int i = 0; i < numberOfReaders - 1; i++)
        {
            for (int j = (numberOfReaders - 1); j > i; j--)
            {
                if ((pointer + j - 1)->libraryCardNumber < (pointer + j)->libraryCardNumber)
                {
                    struct Reader temp = *(pointer + j);
                    *(pointer + j) = *(pointer + j - 1);
                    *(pointer + j - 1) = temp;
                }
            }
        }
        break;
    }

    }
}
void sortStringsAlphabetically(struct Reader* pointer, int numberOfReaders, enum fieldCharType type)
{
    switch (type)
    {
        case LASTNAME:
        {
            for (int i = 0; i < numberOfReaders - 1; i++)
            {
                for (int j = (numberOfReaders - 1); j > i; j--)
                {
                    if ((strcmp((pointer + j - 1)->lastName, (pointer + j)->lastName)) > 0)
                    {
                        struct Reader temp = *(pointer + j);
                        *(pointer + j) = *(pointer + j - 1);
                        *(pointer + j - 1) = temp;
                    }
                }
            }
            break;
        }
        case NAMEOFTHEBOOK:
        {
            for (int i = 0; i < numberOfReaders - 1; i++)
            {
                for (int j = (numberOfReaders - 1); j > i; j--)
                {
                    if ((strcmp((pointer + j - 1)->nameOfTheBook, (pointer + j)->nameOfTheBook)) > 0)
                    {
                        struct Reader temp = *(pointer + j);
                        *(pointer + j) = *(pointer + j - 1);
                        *(pointer + j - 1) = temp;
                    }
                }
            }
            break;
        }

    }
}

void sortStringsInReverseOrder(struct Reader* pointer, int numberOfReaders, enum fieldCharType type)
{
    
    switch (type)
    {
    case LASTNAME:
    {
        for (int i = 0; i < numberOfReaders - 1; i++)
        {
            for (int j = (numberOfReaders - 1); j > i; j--)
            {
                if ((strcmp((pointer + j - 1)->lastName, (pointer + j)->lastName)) < 0)
                {
                    struct Reader temp = *(pointer + j);
                    *(pointer + j) = *(pointer + j - 1);
                    *(pointer + j - 1) = temp;
                }
            }
        }
        break;
    }
    case NAMEOFTHEBOOK:
    {
        for (int i = 0; i < numberOfReaders - 1; i++)
        {
            for (int j = (numberOfReaders - 1); j > i; j--)
            {
                if ((strcmp((pointer + j - 1)->nameOfTheBook, (pointer + j)->nameOfTheBook)) < 0)
                {
                    struct Reader temp = *(pointer + j);
                    *(pointer + j) = *(pointer + j - 1);
                    *(pointer + j - 1) = temp;
                }
            }
        }
        break;
    }
    

    }
    
}

int sortAscending(const void* argument1, const void* argument2)
{
    if (argument1 < argument2)
    {
        return -1;
    }
    else if (argument1 = argument2)
    {
        return 0;
    }
    else if (argument1 > argument2)
    {
        return 1;
    }
}
void mainMenu(struct Reader* pointer)
{
    int numberOfReaders = 0;
    int choice;
    bool quit = false;
    bool exit = false;
    while (!quit)
    {

        switch (menuWithMainChoice())
        {
        case 1:
        {

            printf("Enter a number of readers: \n");
            numberOfReaders = inputValidation();
            pointer = allocateMemory(pointer, numberOfReaders);
            pointer = inputArrayOfStructure(pointer, numberOfReaders, 0);
            break;
        }

        case 2:
            system("cls");
            outputStructures(pointer, numberOfReaders);
            break;
        case 3:
            printf("Enter a library card number\n");
            system("cls");
            scanf_s("%d", &choice);
            int result = findIndexByLibraryCardNumber(pointer, choice, numberOfReaders);
            if (result != -1)
            {
                printLine();
                outputPerson(pointer, result);
                printLine();
            }
            else
            {
                printf("There no reader with this card number\n");
                break;
            }
            switch (menuForChange())
            {
            case 1:
                printf("Enter a new last name: \n");
                rewind(stdin);
                ((pointer + result)->lastName)[0] = '\0';
                fgets((pointer + result)->lastName, 20, stdin);
                deleteSymbols((pointer + result)->lastName);
                break;
            case 2:
                printf("Enter a new first name: \n");
                rewind(stdin);
                ((pointer + result)->firstName)[0] = '\0';
                fgets((pointer + result)->firstName, 20, stdin);
                deleteSymbols((pointer + result)->firstName);
                break;
            case 3:
                printf("Enter a new patronymic name: \n");
                rewind(stdin);
                ((pointer + result)->patronymicName)[0] = '\0';
                fgets((pointer + result)->patronymicName, 20, stdin);
                deleteSymbols((pointer + result)->patronymicName);
                break;
            case 4:
                printf("Enter a new book name: \n");
                rewind(stdin);
                ((pointer + result)->nameOfTheBook)[0] = '\0';
                fgets((pointer + result)->nameOfTheBook, 20, stdin);
                deleteSymbols((pointer + result)->nameOfTheBook);
                break;
            case 5:
                printf("Enter a new return period: \n");
                scanf_s("%d", &((pointer + result)->returnPeriod));
                break;
            case 6:
                printf("Enter a new unit of measure: \n");
                rewind(stdin);
                ((pointer + result)->unitOfMeasurement)[0] = '\0';
                fgets((pointer + result)->unitOfMeasurement, 20, stdin);
                deleteSymbols((pointer + result)->unitOfMeasurement);
                break;
            case 0:
                break;
            }
            break;
        case 4:
            while (!exit)
            {
                switch (menuForSeekByOptions())
                {
                    int* array;
                    int number;
                    char tempString[20];
                case 1:
                    printf("Enter a last name for search: \n");

                    rewind(stdin);
                    fgets(tempString, 20, stdin);
                    deleteSymbols(tempString);
                    if ((array = seekByCharOptions(pointer, numberOfReaders, tempString, LASTNAME)) != -1)
                    {
                        number = (sizeof(array) / sizeof(int));
                        for (int i = 0; i < number + 1; i++)
                        {
                            outputPerson(pointer, array[i]);
                        }
                      
                    }
                    else
                    {
                        printf("There no person with this option. Please try again\n");
                       
                    }
                    break;
                case 2:
                    printf("Enter a first name for search: \n");

                    rewind(stdin);
                    fgets(tempString, 20, stdin);
                    deleteSymbols(tempString);
                    if ((array = seekByCharOptions(pointer, numberOfReaders, tempString, FIRSTNAME)) != -1)
                    {
                        number = (sizeof(array) / sizeof(int));
                        for (int i = 0; i < number + 1; i++)
                        {
                            outputPerson(pointer, array[i]);
                        }
                    }
                    else
                    {
                        printf("There no person with this option. Please try again\n");
                    }
                    break;
                case 3:
                    printf("Enter a patronymic name for search: \n");

                    rewind(stdin);
                    fgets(tempString, 20, stdin);
                    deleteSymbols(tempString);
                    if ((array = seekByCharOptions(pointer, numberOfReaders, tempString, PATRONYMICNAME)) != -1)
                    {
                        number = (sizeof(array) / sizeof(int));
                        for (int i = 0; i < number + 1; i++)
                        {
                            outputPerson(pointer, array[i]);
                        }
                    }
                    else
                    {
                        printf("There no person with this option. Please try again\n");
                    }
                    break;
                case 4:
                    printf("Enter the name of the book for search: \n");

                    rewind(stdin);
                    fgets(tempString, 20, stdin);
                    deleteSymbols(tempString);
                    if ((array = seekByCharOptions(pointer, numberOfReaders, tempString, NAMEOFTHEBOOK)) != -1)
                    {
                        number = (sizeof(array) / sizeof(int));
                        for (int i = 0; i < number + 1; i++)
                        {
                            outputPerson(pointer, array[i]);
                        }
                    }
                    else
                    {
                        printf("There no person with this option. Please try again\n");
                    }
                    break;
                case 5:
                    printf("Enter a period for search: \n");
                    int amount;
                    number = inputValidation();
                    if ((array = seekByIntOptions(pointer, numberOfReaders, number, RETURNPERIOD)) != -1)
                    {
                        amount = (sizeof(array) / sizeof(int));
                        for (int i = 0; i < amount + 1; i++)
                        {
                            outputPerson(pointer, array[i]);
                        }
                    }
                    else
                    {
                        printf("There no person with this option. Please try again\n");
                    }
                    break;
                default:
                    exit = true;
                    break;
                }
            }
            break;
        case 5:
        {
            switch (menuForSort())
            {
            case 1:
                sortByIntOtionsAscending(pointer, numberOfReaders, LIBRARYCARDNUMBER);
                //outputStructures(pointer, numberOfReaders);
                break;
            case 2:
                sortByIntOtionsDescending(pointer, numberOfReaders, LIBRARYCARDNUMBER);
                break;
            case 3:
                sortStringsAlphabetically(pointer, numberOfReaders, LASTNAME);
                break;
            case 4:
                sortStringsAlphabetically(pointer, numberOfReaders, NAMEOFTHEBOOK);
                break;
            case 5:
                sortStringsInReverseOrder(pointer, numberOfReaders, LASTNAME);
                break;
            case 6:
                sortStringsInReverseOrder(pointer, numberOfReaders, NAMEOFTHEBOOK);
                break;
            default:
                break;
            }
            break;
        }
        case 6:
        {
            switch (menuForDelete())
            {
                case 1:
                {
                    printf("Enter a library card number to delete by it\n");
                    choice = inputValidation();
                    int index = findIndexByLibraryCardNumber(pointer, choice, numberOfReaders);
                    if (index == -1)
                    {
                        printf("There is no person with this option\n");
                        break;
                    }
                    else
                    {
                        numberOfReaders = deleteByIntOption(pointer, numberOfReaders, index, LIBRARYCARDNUMBER);
                        //numberOfReaders--;
                    }
                    break;
                }
                case 2:
                {
                    printf("Enter a last name by which you want to delete\n");
                    char lastName[20];
                    rewind(stdin);
                    fgets(lastName, 20, stdin);
                    deleteSymbols(lastName);
                    numberOfReaders = deleteByCharOption(pointer, numberOfReaders, lastName, LASTNAME);
                }
                default:
                    break;
            }
            break;
        }
        case 7:
            system("cls");
            switch (menuForPartialSort())
            {
                case 1:
                {
                    int* array = partialSearch(pointer, numberOfReaders, LASTNAME);
                    int size = sizeof(array) / sizeof(int);
                    for (int i = 0; i < size; i++)
                    {
                        printLine();
                        outputPerson(pointer, array[i]);
                        printLine();
                    }
                    
                    break;
                }
                case 2:
                {

                    break;
                }
                default:
                    break;

            }
            
            break;

        case 0:
            system("cls");
            quit = true;
            for (int i = 0; i < numberOfReaders; i++)
            {
                free(pointer);
            }

            break;

        }
    }
}

int deleteByIntOption(struct Reader* pointer, int numberOfReaders, int index, enum fieldIntType type)
{
    switch(type)
    {
        case LIBRARYCARDNUMBER:
        {
            for (int i = index; i < numberOfReaders - 1; i++)
            {
                *(pointer + i) = *(pointer + i + 1);
            }
            numberOfReaders--;
            pointer = (struct Reader*)realloc(pointer, (numberOfReaders) * sizeof(struct Reader));
            break;
        }
        
    }
    return numberOfReaders;
}

int deleteByCharOption(struct Reader* pointer, int numberOfReaders, char* string, enum fieldCharType type)
{
    int k = 0, length;
    length = strlen(string);
    int j = 0;


    switch (type)
    {
        case LASTNAME:
        {
            for (int i = 0; i < numberOfReaders; i++)
            {
                convertToTheSameRegistr(string);
                convertToTheSameRegistr((pointer + i)->lastName);
                for (j = 0; j < length + 1; j++)
                {
                    if (string[j] == (pointer + i)->lastName[j])
                    {
                        if (string[j] == '\0')
                        {
                            numberOfReaders = deleteByIntOption(pointer, numberOfReaders, i, LIBRARYCARDNUMBER);
                            i--;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            return numberOfReaders;
        }
    }
}

int* partialSearch(struct Reader* pointer, int numberOfReaders, enum fieldCharType type)
{
    int* arrayOfIndexes = (int*)calloc(10, sizeof(int));
    printf("Enter a phrase in form *a*, a*k or *f*k\n");
    char needle[20];
    rewind(stdin);
    fgets(needle, 20, stdin);
    deleteSymbols(needle);
    char tempChar;
    int matchedNumber = 0, foundNumber = 0, l = 0;
    switch (type)
    {
        case LASTNAME:
        {
            for (int k = 0; k < numberOfReaders; k++)
            {
                int j = 0, i = 0, j1 = 0;
                for (i; i < strlen(needle); i++)
                {
                    while ((needle[i] != '*') && (needle[i] != '\n') && (needle[i] != '\0'))
                    {
                        tempChar = needle[i];
                        foundNumber++;
                        for (j = j1; j < strlen(pointer[k].lastName); j++)
                        {
                            if ((pointer[k].lastName)[j] == tempChar)
                            {
                                matchedNumber++;
                                    j1 = j;
                                    break;
                            }
                        }
                        break;
                    }
                }
                if ((matchedNumber == foundNumber) && (foundNumber != 0))
                {
                    arrayOfIndexes[l] = k;
                    l++;
                }
                matchedNumber = 0;
                foundNumber = 0;
            }
            break;
        }  
        case NAMEOFTHEBOOK:
        {
            for (int k = 0; k < numberOfReaders; k++)
            {
                int j = 0, i = 0, j1 = 0;
                for (i; i < strlen(needle); i++)
                {
                    while ((needle[i] != '*') && (needle[i] != '\n') && (needle[i] != '\0'))
                    {
                        tempChar = needle[i];
                        foundNumber++;
                        for (j = j1; j < strlen(pointer[k].nameOfTheBook); j++)
                        {
                            if ((pointer[k].nameOfTheBook)[j] == tempChar)
                            {
                                matchedNumber++;
                                j1 = j;
                                //j = strlen(pointer[k].nameOfTheBook);
                                break;
                            }
                        }
                        break;
                    }
                }
                if ((matchedNumber == foundNumber) && (foundNumber != 0))
                {
                    arrayOfIndexes[l] = k;
                    l++;
                }
                matchedNumber = 0;
                foundNumber = 0;
            }
            break;
        }
    }
    return arrayOfIndexes;
}

//int addStructure(struct Reader* pointer, int numberOfReaders)
//{
//    int  temp = numberOfReaders;
//    printf("Enter the number of new readers: \n");
//    int amount = inputValidation();
//    numberOfReaders = numberOfReaders + amount;
//    pointer = (struct Reader*)realloc(pointer, numberOfReaders);
//    pointer = inputArrayOfStructure(pointer, numberOfReaders, temp);
//    return numberOfReaders;
//}
