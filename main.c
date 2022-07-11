#include "File.h"


void main(int argc, char** argv)
{
	char** arr; 
	int size;
	arr = createArrayFromBinaryFile(argv[1], argv[2]);//updating the strings array
	sscanf(argv[2], "%d", &size);
	mergeSort(arr, size);
	exportToTextFile(argv[1], arr, argv[2]);//making text file throw the arr
	freeArr(arr, argv[2]);
}
