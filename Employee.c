#include "Employee.h"

//The following function gets the file's name and returns employees pointers arr 
Employee** createArr(char* fileName)
{
	FILE* fp;
	int logSize = 0;
	int physSize = 1;
	int fileSize;
	Employee** arr;
	fp = fopen(fileName, "rb");
	checkOpen(fp);
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);//getting the file's sizeusing the marker
	fseek(fp, 0, SEEK_SET);
	arr = (Employee**)malloc(sizeof(Employee));
	checkAlloc(arr);
	while (ftell(fp) < fileSize)
	{ 
		if (logSize == physSize)
		{
			physSize *= 2;
			arr = (Employee**)realloc(arr,physSize * sizeof(Employee*));
			checkAlloc(arr);
		}
		arr[logSize] = (Employee*)malloc(sizeof(Employee));
		checkAlloc(arr[logSize]);
		fread(&arr[logSize]->name_length, sizeof(int), 1,fp);
		arr[logSize]->name = (char*)malloc((arr[logSize]->name_length + 1) * sizeof(char));
		checkAlloc(arr[logSize]->name);
		fread(arr[logSize]->name, sizeof(char),arr[logSize]->name_length, fp);
		arr[logSize]->name[arr[logSize]->name_length] = END_OF_STRING;
		fread(&arr[logSize]->salary, sizeof(float), 1, fp);
		logSize++;
	}
	arr = (Employee**)realloc(arr, logSize * sizeof(Employee));
	checkAlloc(arr);
	fclose(fp);
	return arr;
}

//The following function gets employee pointers arr + size and exporting data to binary file
void exportArrayToFile(Employee** arr, int arrSize, char* fileName)
{
	FILE* fp;
	int i;
	fp = fopen(fileName, "wb");
	checkOpen(fp);
	for (i = 0; i < arrSize; i++)
	{
		fwrite(&arr[i]->name_length, sizeof(int), 1, fp);
		fwrite(arr[i]->name, sizeof(char), arr[i]->name_length, fp);
		fwrite(&arr[i]->salary, sizeof(float), 1, fp);
	}
	fclose(fp);
}

//The following function is a mergeSort for Employee pointers arr
void mergeSort(Employee** pointers, int size)
{
	Employee** temp;
	unsigned int i;
	if (size > 1)
	{ 
		mergeSort(pointers, size / 2);
		mergeSort(pointers + (size / 2), size - (size / 2));
		temp = (Employee**)malloc(size * sizeof(Employee*));
		checkAlloc(temp);
		merge(pointers, size / 2, pointers + (size / 2),size - (size / 2), temp);
		for (i = 0; i < size; i++)
		{
			pointers[i] = temp[i];
		}
		free(temp);
	}
}

//The following function is additional to mergeSort
void merge(Employee** pointers1,int size1, Employee** pointers2,int size2, Employee** temp)
{
	int firstIndex, secondIndex, ind;
	firstIndex=secondIndex=ind = 0;
	while ((firstIndex < size1) && (secondIndex < size2))
	{
		if ((pointers1[firstIndex]->salary) > (pointers2[secondIndex]->salary))
		{
			temp[ind] = pointers1[firstIndex];
			firstIndex++;
		}
		else
		{
			temp[ind] = pointers2[secondIndex];
			secondIndex++;
		}
		ind++;
	}
	while (firstIndex < size1)
	{
		temp[ind] = pointers1[firstIndex];
		firstIndex++;
		ind++;
	}
	while (secondIndex < size2)
	{
		temp[ind] = pointers2[secondIndex];
		secondIndex++;
		ind++;
	}
}

//The following function gets arr of employees pointers + file's name
//The function updates the pointers array by the second file data
//The function returns the arrSize
int updateArr(Employee** arr, char* fileName)
{
	FILE* fp;
	int fileSize;
	int i = 0;
	float cash;
	fp = fopen(fileName, "rb");
	checkOpen(fp);
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);//getting the file's size
	fseek(fp, 0, SEEK_SET);//returning the marker to the beggining of the file
	while (ftell(fp) < fileSize)
	{
		fread(&cash, sizeof(float), 1, fp);
		arr[i]->salary += cash;
		i++;
	}
	fclose(fp);
	return i;
}

//The following function checks memory allocation
void checkAlloc(void* p)
{
	if (p == NULL)
	{
		puts("Memory allocation Failed!! Exiting!");
		exit(1);
	}
}

//The following function checks file openning
void checkOpen(FILE * fp)
{
	if (fp == NULL)
	{
		puts("File Opening Failed!! Exiting!");
		exit(1);
	}
}

//The following function free the employees names + employees themself + arr allocation
void freeArr(Employee** arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(arr[i]->name);
		free(arr[i]);
	}
	free(arr);
}