#include "Student.h"

void main(int argc, char* argv[])
{
	FILE* in, *out;
	int fileNameLen;
	char* fileName;
	fileNameLen = strlen(argv[1]) + 5;//file's name + .ind\0
	fileName = (char*)malloc(fileNameLen * sizeof(char));
	checkAlloc(fileName);
	strcpy(fileName, argv[1]);
	strcat(fileName, ".ind");
	in = fopen(argv[1], "rb");
	checkOpen(in);
	out = fopen(fileName, "wb+");
	checkOpen(out);

	createUpdatedStudentsDataFile(in, out);
	fclose(in);
	fclose(out);
}
