//
// Created by gaydi on 25.03.2021.
//

#ifndef LABWORK3_HEADER_H
#define LABWORK3_HEADER_H

#endif //LABWORK3_HEADER_H
#include <stdio.h>

void mainMenu(FILE* textFilePointer);
void menuForTextFile(FILE* textFilePointer);
int inputValidation();
int menu();
int menuForTextChoice();
void inputStrings(char* nameOfFile);
void outputText(char* string);void outputWord(char* nameOfFile, int wordSize, int place);
void seekAndOutputSuitableItem(int number, char* nameOfFile);
void reverseWord(char* fileName, int wordLength, int endPosition);
void findByItem(char* nameOfFile, int number);
void outputWord(char* nameOfFile, int wordSize, int place);