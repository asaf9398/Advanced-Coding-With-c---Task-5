#include "Student.h"

//The following function creates and returns students data pointers array from the input file
STUDENT_DATA** getDataFromFile(FILE* inputFile, short int* numOfStudents)
{
	STUDENT_DATA** students;
	short int nameLen;
	int i;
	fread(numOfStudents, sizeof(short int), 1, inputFile);//getting num of students from the file
	students = (STUDENT_DATA**)malloc(*numOfStudents * sizeof(STUDENT_DATA*));//making array with numOfStudents cells
	checkAlloc(students);
	for (i = 0; i < *numOfStudents; i++)
	{ //getting the students data into the array
		students[i] = (STUDENT_DATA*)malloc(sizeof(STUDENT_DATA));
		checkAlloc(students[i]);
		students[i]->index = ftell(inputFile);
		fread(&nameLen, sizeof(short int), 1, inputFile);//getting student's name length
		fseek(inputFile, nameLen, SEEK_CUR);//passing his name with marker
		fread(&(students[i]->average), sizeof(int), 1, inputFile);//getting student's avarage into arr
	}
	return students;
}

//The following function gets the optput&intpur file pointers and updates the outputFile to be with the updated students data
void createUpdatedStudentsDataFile(FILE* inputFile, FILE* outputFile)
{
	STUDENT_DATA** students;
	short int numberOfStudents;
	students = getDataFromFile(inputFile, &numberOfStudents);
	mergeSort(students, numberOfStudents);
	writeToNewStudentsDataFile(outputFile, students, numberOfStudents);
	freeArr(students,numberOfStudents);
}

//The following function gets sorts the studets array by their avarage
void mergeSort(STUDENT_DATA** students, short int numOfStudents)
{
	STUDENT_DATA** temp;
	short int i;
	if (numOfStudents <= 1)
	{ 
		return;
	}
	else
	{ 
		mergeSort(students, numOfStudents / 2);
		mergeSort(students + (numOfStudents / 2), numOfStudents - (numOfStudents / 2));
		temp = (STUDENT_DATA**)malloc(numOfStudents * sizeof(STUDENT_DATA*));
		checkAlloc(temp);
		merge(students, numOfStudents / 2, students +(numOfStudents / 2), numOfStudents - (numOfStudents /2), temp);
		for (i = 0; i < numOfStudents; i++)
		{
			students[i] = temp[i];
		}
		free(temp);
	}
}

//The following function is additional to mergeSort function
void merge(STUDENT_DATA** students1, unsigned int size1, STUDENT_DATA** students2, unsigned int size2, STUDENT_DATA** temp)
{
	unsigned int firstIndex, secondIndex, tempIndex;
	firstIndex = secondIndex = tempIndex = 0;
	while ((firstIndex < size1) && (secondIndex < size2))
	{
		if ((students1[firstIndex]->average) <= (students2[secondIndex]->average))
		{
			temp[tempIndex] = students1[firstIndex];
			firstIndex++;
		}
		else
		{
			temp[tempIndex] = students2[secondIndex];
			secondIndex++;
		}
		tempIndex++;
	}
	while (firstIndex < size1)
	{
		temp[tempIndex] = students1[firstIndex];
		firstIndex++;
		tempIndex++;
	}
	while (secondIndex < size2)
	{
		temp[tempIndex] = students2[secondIndex];
		secondIndex++;
		tempIndex++;
	}
}

//The following function gets students data pointers array and writes it into the new students data file
void writeToNewStudentsDataFile(FILE* out, STUDENT_DATA** students, short int numberOfStudents)
{
	short int i;
	for (i = 0; i < numberOfStudents; i++)
	{
		fwrite(&students[i]->index, sizeof(long int), 1,out);//writing to the new file in the array's order
	}
}

//The following function checks if file opening succeed
void checkOpen(FILE* fp)
{
	if (fp == NULL)
	{
		printf("File opening failed!! Exiting");
		exit(1);
	}
}

//The following function frees the students data array
void freeArr(STUDENT_DATA** arr, short int numOfStudents)
{
	int i;
	for (i = 0; i < numOfStudents; i++)
	{
		free(arr[i]);
	}
	free(arr);
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
