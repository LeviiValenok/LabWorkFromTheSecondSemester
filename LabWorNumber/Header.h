#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <Windows.h>
#include <stdbool.h>

enum fieldCharType {
    LASTNAME = 1,
    FIRSTNAME = 2,
    PATRONYMICNAME = 3,
    NAMEOFTHEBOOK = 4,
};
enum fieldIntType {
    RETURNPERIOD = 1,
    LIBRARYCARDNUMBER = 2

};


struct Reader
{
    char lastName[20];
    char firstName[20];
    char patronymicName[20];
    int libraryCardNumber;
    char nameOfTheBook[20];
    int returnPeriod;
    char unitOfMeasurement[20];

};
void mainMenu(struct Reader* pointer);
int menuWithMainChoice();
int menuForChange(); 
int menuForSeekByOptions();
int menuForSort();
int menuForDelete();
int inputValidation();
void deleteSymbols(char* string);
void printLine();
struct Reader* inputArrayOfStructure(struct Reader* pointer, int numberOfReaders, int start);
void outputStructures(struct Reader* pointer, int numberOfReaders);
void outputPerson(struct Reader* pointer, int index);
struct Reader*
    allocateMemory(struct Reader* pointer, int numberOfReaders);
int findIndexByLibraryCardNumber(struct Reader* pointer, int libraryCardNumber, int numberOfReaders);
int* seekByCharOptions(struct Reader* pointer,int numberOfReaders,char* string, enum fieldCharType type);
int* seekByIntOptions(struct Reader* pointer, int numberOfReaders, int number, enum fieldIntType type);
void convertToTheSameRegistr(char* string);
int sortAscending(const void* argument1, const void* argument2);
void sortByIntOtionsAscending(struct Reader* pointer, int numberOfReaders, enum fieldIntType type);
void sortByIntOtionsDescending(struct Reader* pointer, int numberOfReaders, enum fieldIntType type);
void sortStringsAlphabetically(struct Reader* pointer, int numberOfReaders, enum fieldCharType type);
int deleteByIntOption(struct Reader* pointer, int numberOfReaders, int index, enum fieldIntType type);
int deleteByCharOption(struct Reader* pointer, int numberOfReaders, char* string, enum fieldCharType type);
int* partialSearch(struct Reader* pointer, int numberOfReaders, enum fieldCharType type);
