#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define END_OF_STRING '\0'

typedef struct employee
{
	int name_length;
	char* name;
	float salary;
}Employee;

Employee** createArr(char* fileName);
int updateArr(Employee** arr,char* fileName);
void mergeSort(Employee** pointers,int size);
void merge(Employee** pointers1,int size1, Employee** pointers2,int size2, Employee** temp);
void exportArrayToFile(Employee** arr,int arrSize, char* fileName);
void checkAlloc(void* ptr);
void checkOpen(FILE * fp);
void freeArr(Employee** arr, int size);

#endif
