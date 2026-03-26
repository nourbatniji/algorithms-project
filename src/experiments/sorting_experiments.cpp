#include <vector>
#include "sorting_experiments.h"
#include "../sorting/alphadev/alphadevsort.h"
#include "../sorting/introsort/introsort.h"
#include "../sorting/timsort/timsort.h"
#include "../sorting/parallel/parallel_mergesort.h"
#include <cmath>
#include <chrono>
using namespace chrono;
using namespace std;

extern long long comparisons;

//========================================================
// ALPHADEV
long long measureAlphaDevTime(const vector<int> &originalData)
{
    const int RUNS = 5;
    long long totalTime = 0;

    for (int i = 0; i < RUNS; i++)
    {
        vector<int> data = originalData;
        auto start = high_resolution_clock::now();
        alphaDevSort(data);
        auto end = high_resolution_clock::now();
        totalTime += duration_cast<microseconds>(end - start).count();
    }

    return totalTime / RUNS;
}

long long measureAlphaDevMemory(int n)
{
    return (n * sizeof(int)) / 1024;
}

long long measureAlphaDevComparisons(vector<int> data)
{
    comparisons = 0;
    alphaDevSort(data);
    return comparisons;
}

//========================================================
// TIMSORT
long long measureTimSortTime(const vector<int> &originalData)
{
    const int RUNS = 5;
    long long totalTime = 0;

    for (int i = 0; i < RUNS; i++)
    {
        vector<int> data = originalData;
        auto start = high_resolution_clock::now();
        timSort(data);
        auto end = high_resolution_clock::now();
        totalTime += duration_cast<microseconds>(end - start).count();
    }

    return totalTime / RUNS;
}

long long measureTimSortMemory(int n)
{
    return (n * sizeof(int)) / 1024;
}

long long measureTimSortComparisons(vector<int> data)
{
    comparisons = 0;
    timSort(data);
    return comparisons;
}

//========================================================
// Intro Sort
long long measureIntroSortTime(const vector<int> &originalData)
{
    const int RUNS = 5;
    long long totalTime = 0;

    for (int i = 0; i < RUNS; i++)
    {
        vector<int> data = originalData;
        auto start = chrono::high_resolution_clock::now();
        introSort(data);
        auto end = chrono::high_resolution_clock::now();
        totalTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return totalTime / RUNS;
}

long long measureIntroSortMemory(int n)
{
    return 1;
}

long long measureIntroSortComparisons(vector<int> data)
{
    comparisons = 0;
    introSort(data);
    return comparisons;
}

// ========================================================
// Parallel Merge Sort
long long measureParallelMergeSortTime(const vector<int>& originalData) {
    const int RUNS = 3;  // Fewer runs because it's slower to copy large data
    long long totalTime = 0;

    for (int i = 0; i < RUNS; i++) {
        vector<int> data = originalData;
        auto start = high_resolution_clock::now();
        parallelMergeSort(data);
        auto end = high_resolution_clock::now();
        totalTime += duration_cast<microseconds>(end - start).count();
    }

    return totalTime / RUNS;
}

long long measureParallelMergeSortMemory(int n) {
    // Parallel merge sort uses O(n) extra memory for temporary arrays
    // Plus thread overhead, but we'll report just the main array memory
    return (n * sizeof(int)) / 1024;
}

long long measureParallelMergeSortComparisons(vector<int> data) {
    comparisons = 0;
    parallelMergeSortWithComparisons(data);
    return comparisons;
}