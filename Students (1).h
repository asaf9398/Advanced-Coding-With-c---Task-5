#ifndef __STUDENTS_H
#define __STUDENTS_H
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct student
{
	char* name;
	int average;
}STUDENT;


char** findAverageGrade(char* database, int avgGrade, int*resSize);
int getGradeFromLocation(FILE* studentsFile, long int index);
void printStudents(char** arr, int size);
char* getName(FILE* studentsFile, long int location);
void binarySearchInIndexFile(char** arr, short int* size, FILE* studentsFile, FILE* indexFile, int grade);
void checkAlloc(void* p);
void checkOpen(FILE * fp);
void freeStudentsNamesArr(char** arr, int size);


#endif
