
#ifndef LABWORKNUMBER2RIGTHVERSION_HEADER_H
#define LABWORKNUMBER2RIGTHVERSION_HEADER_H

#endif //LABWORKNUMBER2RIGTHVERSION_HEADER_H

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
    _Bool flag;
};

void menu(struct geometricShapes* pointer, int numberOfFigures);
int menuForDelete();
int menuForSeek();
void menuForOutput(struct geometricShapes* pointer, int numberOfFigures);
struct geometricShapes* menuForEnterArrayOfStructure(struct geometricShapes* pointer , int numberOfFigures);
int mainMenu();
int inputValidation();
float inputValidationForFloat();
int rightChoice();
void enterArrayOfStructure(struct geometricShapes* pointer, int index);
void outputFigure(struct geometricShapes* pointer, int index);
void outputStructures(struct geometricShapes* pointer, int numberOfFigures);
void printLine();
struct geometricShapes* allocateArrayOfStructures(struct geometricShapes* pointer , int numberOfFigures);
struct geometricShapes* addNewElements(struct geometricShapes* pointer, int numberOfFigures, int numberOfNewElements);
void seekByCharOptions(struct geometricShapes* pointer, int numberOfFigures, char* string, enum charType type);
void seekByIntegerOrFloatOptions(struct geometricShapes* pointer, int numberOfFigures,
                                 enum Type type);
int seekByName(struct geometricShapes* pointer, int numberOfFigures, char* compareString);
int deleteOneStructure(struct geometricShapes* pointer, int numberOfFigures, int index);
int deleteAll(struct geometricShapes* pointer, int numberOfFigures);
int seekByColor(struct geometricShapes* pointer, int numberOfFigures, char* compareString);
