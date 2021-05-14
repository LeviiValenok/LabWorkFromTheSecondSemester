
#ifndef LABWORK4_HEADER_H
#define LABWORK4_HEADER_H

#endif //LABWORK4_HEADER_H
#include <stdio.h>

enum charType
{
    COLOR = 1
};


enum fileType
{
    BINARYFILE = 1,
    TEXTFILE = 2
};

enum Type
{
    PERIMETER = 1,
    SQUARE = 2
};


union perimeterAndColor
{

    float perimeter;
    char color[20];

};
struct geometricShapes
{
    int square;
    char name [20];
    union perimeterAndColor information;
    struct geometricShapes* nextItem;
    _Bool flag;
};


void mainMenu();
int menuForChoice ();
void enterArrayOfStructure(struct geometricShapes* pointer);
void pushToStack(struct geometricShapes** topOfStack);
float inputValidationForFloat();
int rightChoice();
void printLine();
void outputFigure(struct geometricShapes* pointer);
void hatter();
void outputContent(struct geometricShapes* topOfTheStack);
void deleteAnItem(struct geometricShapes** topOfStack, int number);
void menuForDelete(struct geometricShapes** topOfStack);
int menuForSeek();
void convertToTheSameRegister(char* string);
void seekByColor(struct geometricShapes* topOfStack);
void seekByOptions(struct geometricShapes** topOfStack);
void seekByIntegers(struct geometricShapes* topOfStack);
void seekByFloats(struct geometricShapes* topOfStack);
int menuForLoadAsFileChoice();
char* enterFileName(enum fileType type);
void outputFigureToFle(struct geometricShapes* pointer, FILE* textFilePointer);
void saveAsTextFile(struct geometricShapes* topOfStack);
char* menuForSave(struct geometricShapes* topOfStack);
int menuForLoadFromFileChoice();
void menuForLoadFromFile(struct geometricShapes** topOfStack);
void saveAsBinaryFile(struct geometricShapes* topOfStack);
void loadFromBinaryFile(struct geometricShapes** topOfStack);
void deleteSymbols(char* string);
void copyOfStack(struct geometricShapes** source, struct geometricShapes** final);