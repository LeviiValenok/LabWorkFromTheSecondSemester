//
// Created by gaydi on 02.05.2021.
//

#ifndef LABWORK5_HEADER_H
#define LABWORK5_HEADER_H
#endif //LABWORK5_HEADER_H
#include <stdbool.h>

union PerimeterAndColor
{

    float perimeter;
    char color[20];

};

struct GeometricShapes
{
    int square;
    char name [20];
    union PerimeterAndColor information;
    struct GeometricShapes* nextItem;
    _Bool flag;
};
struct GeometricShapes* head;
struct GeometricShapes* tail;


enum fileType
{
    BINARYFILE = 1,
    TEXTFILE = 2
};



float inputValidationForFloat();
int inputValidation(bool type);
void deleteSymbols(char* string);
int rightChoice();
void insertQueue(struct GeometricShapes** tail, struct GeometricShapes** head);
void hatter();
void printLine();
void outputContent(struct GeometricShapes* head);
void dequeue(struct GeometricShapes** head, struct GeometricShapes** tail, int number);
void convertToTheSameRegister(char* string);
void seekByColor(struct GeometricShapes* head);
void seekByFloats(struct GeometricShapes *head);
void seekByIntegers(struct GeometricShapes* head);
void seekByOptions(struct GeometricShapes** head);
void saveAsTextFile(struct GeometricShapes* head);
void loadFromFileToQueue(struct GeometricShapes **head, struct GeometricShapes** tail);
char* enterFileName(enum fileType type);
void saveAsBinaryFile(struct GeometricShapes* head);

void mainMenu();
int menuForChoice ();
int menuForSeek();
int menuForLoadAsFileChoice();
void menuForSave(struct GeometricShapes* topOfStack);
int menuForLoadFromFile();