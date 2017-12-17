#ifndef STATISTICS_H
#define STATISTICS_H
#include <stdio.h>

/********************************************************
   
   DVA104, Lab 5, Statistics.h
   Innehaller funktioner for att halla reda pa
   statistik over hur manga byten och jamforelser man gor
   i sorteringsalgoritmer.

*********************************************************/

struct statistics
{
	unsigned int comparisons;
	unsigned int swaps;
};

typedef struct statistics Statistics;

// Nollstaller statistiken
void resetStatistics(Statistics* statistics);

// Skriver statistiken till fil
void printStatistics(const Statistics* statistics, FILE* file);

// Jamforelseoperatorer med statistik
int lessThan(unsigned int element1, unsigned int element2, Statistics* statistics); // sant om element1 < element2
int greaterThan(unsigned int element1, unsigned int element2, Statistics* statistics); // sant om element1 > element2
int equalTo(unsigned int element1, unsigned int element2, Statistics* statistics); // sant om element1 == element2
int notEqualTo(unsigned int element1, unsigned int element2, Statistics* statistics); // sant om element1 != element2
int lessThanOrEqualTo(unsigned int element1, unsigned int element2, Statistics* statistics); // sant om element1 <= element2
int greaterThanOrEqualTo(unsigned int element1, unsigned int element2, Statistics* statistics); // sant om element >= element2

// Byter plats på element1 och element2 med statistik
void swapElements(unsigned int* element1, unsigned int* element2, Statistics* statistics);

#endif
