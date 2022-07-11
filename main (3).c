#include "Students.h"

void main(int argc, char* argv[])
{
	char** studentsNames;
	int size;
	int avarage;
	sscanf(argv[2], "%d",&avarage);
	studentsNames = findAverageGrade(argv[1],avarage , &size);//I'm assuming that im getting file's name in argv[1] and the avrage in argv[2] 
	printStudents(studentsNames, size);
	freeStudentsNamesArr(studentsNames, size);
}