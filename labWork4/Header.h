//
// Created by gaydi on 14.04.2021.
//

#ifndef LABWORK4_HEADER_H
#define LABWORK4_HEADER_H

#endif //LABWORK4_HEADER_H


enum charType
{
    COLOR = 1
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