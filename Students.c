#include "Students.h"

//The following function gets the string of db and returns the array of names of students that are with this avrage 
char** findAverageGrade(char* database, int avgGrade, int* resSize)
{
	FILE* studentsFile,* indexFile;
	short int studentsNumber;
	char** arr;
	studentsFile = fopen(database, "rb");//opening the database file
	checkOpen(studentsFile);
	int indexLen = strlen(database) + 5;//for .ind\0
	char* databaseIndex = (char*)malloc(indexLen * sizeof(char));
	checkAlloc(databaseIndex);
	strcpy(databaseIndex, database);//creating index file name from input
	strcat(databaseIndex, ".ind");
	indexFile = fopen(databaseIndex, "rb");//opening index file
	checkOpen(indexFile);
	fread(&studentsNumber, sizeof(short int), 1,studentsFile);
	arr = (char**)malloc(studentsNumber * sizeof(char*));
	checkAlloc(arr);
	binarySearchInIndexFile(arr, &studentsNumber, studentsFile,indexFile, avgGrade);//searching in the db for students + updating arr
	if (studentsNumber == 0)
	{//if there are no students -> get out
		free(arr);
		arr = NULL;
	}
	else
	{
		arr = (char**)realloc(arr,studentsNumber * sizeof(char*));
		checkAlloc(arr);
		*resSize = studentsNumber;
	}
	fclose(studentsFile);
	fclose(indexFile);
	free(databaseIndex);
	return arr;
}

//The following function returns the grade from a specific index in file
int getGradeFromLocation(FILE* studentsFile, long int index)
{
	short int nameLen;
	int grade;
	long int lastLocation;
	lastLocation = ftell(studentsFile);
	fseek(studentsFile, index, SEEK_SET);
	fread(&nameLen, sizeof(short), 1, studentsFile);
	fseek(studentsFile, nameLen, SEEK_CUR);
	fread(&grade, sizeof(int), 1, studentsFile);
	fseek(studentsFile, lastLocation, SEEK_SET);
	return grade;
}


//The following function searches for the students using binary search with the index file
void binarySearchInIndexFile(char** arr, short int* size, FILE* studentsFile, FILE* indexFile, int grade)
{
	short int leftIndex,rightIndex,middleIndex;
	long int placeInFile;
	int leftGrade,rightGrade,middleGrade;
	leftIndex = 0;
	rightIndex = *size;
	fseek(indexFile, 0, SEEK_SET);
	fread(&placeInFile, sizeof(int), 1, indexFile);
	leftGrade = getGradeFromLocation(studentsFile,placeInFile);
	fseek(indexFile, -4, SEEK_END);
	fread(&placeInFile, sizeof(int), 1, indexFile);
	rightGrade = getGradeFromLocation(studentsFile, placeInFile);
	*size = 0;
	if ((leftGrade > grade) || (rightGrade < grade))
	{ 
		return;
	}
	else
	{ 
		middleIndex = (leftIndex + rightIndex) / 2;
		while (leftIndex < rightIndex&&rightIndex>=2)
		{
			fseek(indexFile, middleIndex * sizeof(long int),SEEK_SET);
			fread(&placeInFile, sizeof(long int), 1,indexFile);
			middleGrade = getGradeFromLocation(studentsFile, placeInFile);
			if (middleGrade == grade)
			{
				arr[(*size)] = getName(studentsFile,placeInFile);
				(*size)++;
				
			}
			if (middleGrade < grade)
				leftIndex=middleIndex++;
			else
				rightIndex=middleIndex--;

			middleGrade = 0;
			middleIndex = (leftIndex + rightIndex) / 2;
		}
		
	}
}

//The following function prints the studetns in the names array
void printStudents(char** arr, int size)
{
	int i;
	printf("The relevent students are:\n");
	for (i = 0; i < size; i++)
		printf("%s\n", arr[i]);
}

//The following function returns the name in the specific index
char* getName(FILE* studentsFile, long int index)
{
	short int nameLength;
	char* name;
	long int lastLocation;
	lastLocation = ftell(studentsFile);
	fseek(studentsFile, index, SEEK_SET);
	fread(&nameLength, sizeof(short), 1, studentsFile);
	name = (char*)malloc((nameLength + 1) * sizeof(char));// adding place for \0
	checkAlloc(name);
	fread(name, sizeof(int), nameLength, studentsFile);
	fseek(studentsFile, lastLocation, SEEK_SET);
	return name;
}

//The following function checks if memory allocation succeed
void checkAlloc(void* p)
{
	if (p == NULL)
	{
		printf("Memory Allocation failed!! Exiting");
		exit(1);
	}
}

//The following function checks if file opening succeed
void checkOpen(FILE * fp)
{
	if (fp == NULL)
	{
		printf("File Opening failed!! Exiting");
		exit(1);
	}
}

//The following function frees all the names allocations + the arr itself
void freeStudentsNamesArr(char** arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
