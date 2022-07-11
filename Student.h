#ifndef __STUDENT_H
#define __STUDENT_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_GRADE 100 

typedef struct studentData 
{
	int index;
	int average;
}STUDENT_DATA;

void mergeSort(STUDENT_DATA** students, short int numOfStudents);
void merge(STUDENT_DATA** students1, unsigned int size1, STUDENT_DATA** students2, unsigned int size2, STUDENT_DATA** temp);
STUDENT_DATA** getDataFromFile(FILE* inputFile, short int* numOfStudents);
void writeToNewStudentsDataFile(FILE* out, STUDENT_DATA** students, short int numberOfStudents);
void createUpdatedStudentsDataFile(FILE* inputFile, FILE* outputFile);
void freeArr(STUDENT_DATA** arr, short int numOfStudents);
void checkAlloc(void* p);
void checkOpen(FILE* fp);


#endif