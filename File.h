#ifndef __FILE_H
#define __FILE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define END_OF_STRING '\0'

char** createArrayFromBinaryFile(char* fileName, char* size);
void mergeSort(char** pointers, unsigned int size);
void merge(char** pointers1, unsigned int size1, char** pointers2, unsigned int size2, char** temp);
void exportToTextFile(char* fileName, char** arr, char* size);
void freeArr(char** arr, char* size);
void checkAlloc(void* ptr);
void checkOpen(FILE* fp);

#endif
