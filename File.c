#include "File.h"

//The following function gets file's name and creates array of strings for him
char** createArrayFromBinaryFile(char* fileName, char* size)
{	
	FILE* fp;
	int numOfStrings,i,j,numOfCharacters,stringSize;
	char ch;
	char** arr;
	sscanf(size, "%d", &numOfStrings);
	arr = (char**)malloc(numOfStrings * sizeof(char*));
	checkAlloc(arr);
	fp = fopen(fileName, "rb");
	checkOpen(fp);
	for (i = 0; i < numOfStrings; i++)
	{
		stringSize = 0;
		fread(&numOfCharacters, sizeof(int), 1, fp);
		arr[i] = (char*)malloc((numOfCharacters +1) * sizeof(char));
		checkAlloc(arr[i]);
		for (j = 0; j < numOfCharacters; j++)
		{ 
			fread(&ch, sizeof(char), 1, fp);
			if (islower(ch) != 0) 
			{
				arr[i][stringSize] = ch;
				stringSize++;
			}
		}
		arr[i] = (char*)realloc(arr[i], (stringSize +1) * sizeof(char));
		checkAlloc(arr[i]);
		arr[i][stringSize] = END_OF_STRING;
	}
	fclose(fp);
	return arr;
}

//The following function is a mergeSort to the sub strings
void mergeSort(char** pointers, unsigned int size)
{
	char** temp;
	int i;
	if (size > 1)
	{ 
		mergeSort(pointers, size / 2);
		mergeSort(pointers + (size / 2), size - (size / 2));
		temp = (char**)malloc(size * sizeof(char*));
		checkAlloc(temp);
		merge(pointers, size / 2, pointers + (size / 2),
			size - (size / 2), temp);
		for (i = 0; i < size; i++)
		{
			pointers[i] = temp[i];
		}
		free(temp);
	}
}

//Additional function for mergeSort
void merge(char** pointers1, unsigned int size1, char** pointers2, unsigned int size2, char** temp)
{
	
	int firstIndex = 0;
	int secondIndex = 0;
	int ind = 0;
	while ((firstIndex < size1) && (secondIndex < size2))
	{
		if (strcmp(pointers1[firstIndex], pointers2[secondIndex]) == -1)
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


//The following function gets file's name and data creates new text file
void exportToTextFile(char* fileName, char** arr, char* size)
{
	int numOfStrings,nameLen,i;
	char* textFileName;
	FILE* fp;
	sscanf(size, "%d", &numOfStrings);
	nameLen = strlen(fileName) + 5;
	textFileName = (char*)malloc(nameLen * sizeof(char));
	checkAlloc(textFileName);
	strcpy(textFileName, fileName);
	strcat(textFileName, ".txt");
	fp = fopen(textFileName, "w+");
	checkOpen(fp);
	for (i = 0; i < numOfStrings; i++)
	{
		fprintf(fp, "%s\n", arr[i]);
	}
	fclose(fp);
}

//The following function free all the array 
void freeArr(char** arr, char* size)
{
	int numOfStrings;
	int i;
	sscanf(size, "%d", &numOfStrings);
	for (i = 1; i < numOfStrings; i++)
	{
		free(arr[i]);//free all allocations one by one
	}
	free(arr);//free the bigger array
}


//The following function checks if the memory allocation succeed
void checkAlloc(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation failed!!Exiting");
		exit(1);
	}
}

//The following function checks if the file openning succeed
void checkOpen(FILE * fp)
{
	if (fp == NULL)
	{
		puts("File opening failed!!Exiting");
		exit(1);
	}
}
