#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
      case BUBBLE_SORT:
//      case INSERTION_SORT:
      case SELECTION_SORT:
//      case QUICK_SORT:
      case MERGE_SORT:
            return 1;
        default:
            return 0;
	}
}


/******************************************************************************************/
/* Era algoritmer har: */

static void bubbleSort(ElementType* arrayToSort, size_t size, Statistics* statistics)
{
	int swapped = 1;
	while (lessThan(0, swapped, statistics))
	{
		swapped = 0;
		for (int i = 0; lessThan(i, size - 1, statistics); i++)
		{
			if (lessThan(arrayToSort[i + 1], arrayToSort[i], statistics))
			{
				swapped++;
				swapElements(&arrayToSort[i + 1], &arrayToSort[i], statistics);
			}
		}
	}
}

static void insertionSort(ElementType* arrayToSort, size_t size, Statistics* statistics)
{
}

static void selectionSort(ElementType* arrayToSort, size_t size, Statistics* statistics)
{
	for (int i = 0; lessThan(i, size - 1, statistics); i++)
	{
		for (int j = i + 1; lessThan(j, size, statistics); j++)
		{
			if (lessThan(arrayToSort[j], arrayToSort[i], statistics))
			{
				swapElements(&arrayToSort[i], &arrayToSort[j], statistics);
			}
		}
	}
}

static void merge(ElementType* arrayToSort, int low, int middle, int high, Statistics* statistics)
{
	int lowSize = middle - low + 1;
	int highSize = high - middle;
	int *tempLow = malloc(sizeof(int)*lowSize);
	int *tempHigh = malloc(sizeof(int)*highSize);

	for (int i = 0; lessThan(i, lowSize, statistics); i++)
	{
		swapElements(&tempLow[i], &arrayToSort[low + i], statistics);
	}
	for (int i = 0; lessThan(i, highSize, statistics); i++)
	{
		swapElements(&tempHigh[i], &arrayToSort[middle + 1 + i], statistics);
	}


	int lowI = 0;
	int highI = 0;
	int I = low;
	while (lessThan(lowI, lowSize, statistics) && lessThan(highI, highSize, statistics))
	{
		if (lessThanOrEqualTo(tempLow[lowI], tempHigh[highI], statistics))
		{
			swapElements(&arrayToSort[I], &tempLow[lowI], statistics);
			lowI++;
		}
		else
		{
			swapElements(&arrayToSort[I], &tempHigh[highI], statistics);
			highI++;
		}
		I++;
	}
	while (lessThan(lowI, lowSize, statistics))
	{
		swapElements(&arrayToSort[I], &tempLow[lowI], statistics);
		I++;
		lowI++;
	}
	while (lessThan(highI, highSize, statistics))
	{
		swapElements(&arrayToSort[I], &tempHigh[highI], statistics);
		I++;
		highI++;
	}
}

static void split(ElementType* arrayToSort, int low, int high, Statistics* statistics)
{
	if (lessThan(low, high, statistics))
	{
		int middle = low+(high-low)/2;
		split(arrayToSort, low, middle, statistics);
		split(arrayToSort, middle + 1, high, statistics);
		merge(arrayToSort, low, middle, high, statistics);
	}

}

static void mergeSort(ElementType* arrayToSort, size_t size, Statistics* statistics)
{
	split(arrayToSort, 0, size, statistics);
}


static void quickSort(ElementType* arrayToSort, size_t size, Statistics* statistics)
{
}

/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/* Ar inte strangen vi allokerar lokal for funktionen?
	   Nej, inte i detta fall. Strangkonstanter ar ett speciallfall i C */
	switch (algorithm)
	{
        case BUBBLE_SORT:	 return "  Bubble sort ";
        case SELECTION_SORT: return "Selection sort";
        case INSERTION_SORT: return "Insertion sort";
        case MERGE_SORT:	 return "  Merge sort  ";
        case QUICK_SORT:	 return "  Quick sort  ";
        default: assert(0 && "Ogiltig algoritm!"); return "";
	}
}

// Sorterar 'arrayToSort' med 'algorithmToUse'. Statistik for antal byten och jamforelser hamnar i *statistics
static void sortArray(ElementType* arrayToSort, size_t size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if(statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:	 bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:	 mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:	 quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Ogiltig algoritm!");
	}
}

// Forbereder arrayer for sortering genom att allokera minne for dem, samt intialisera dem
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType)*sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

// Sorterar arrayerna
static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);
	
		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Fel! Algoritmen %s har inte sorterat korrekt!\n", getAlgorithmName(current->algorithm));
			printf("Resultatet är: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4d element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}
