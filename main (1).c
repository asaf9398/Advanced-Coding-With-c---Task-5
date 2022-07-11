#include "Employee.h"

void main(int argc, char** argv)
{ 
	Employee** arr;
	int size;
	arr = createArr(argv[1]);
	size = updateArr(arr, argv[2]);
	mergeSort(arr, size);
	exportArrayToFile(arr, size, argv[1]);
	freeArr(arr,size);
}
