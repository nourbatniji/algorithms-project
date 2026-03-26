#include "searching_experiments.h"
#include "../searching/binary_search.h"
#include "../searching/jump_search.h"
#include "../searching/exponential_search.h"
#include <chrono>
#include <random>
using namespace chrono;
using namespace std;

void measureSearchPerformance(vector<int> &sortedData, string algoName, string datasetName, ofstream &results)
{
    const int QUERIES = 1000;

    mt19937 rng(42);
    uniform_int_distribution<int> indexDist(0, sortedData.size() - 1);

    long long totalTime = 0;
    long long worstTime = 0;

    for (int i = 0; i < QUERIES; i++)
    {
        // choose a random existing value from the sorted array
        int target = sortedData[indexDist(rng)];

        auto start = high_resolution_clock::now();

        if (algoName == "BinarySearch")
            binarySearch(sortedData, target);
        else if (algoName == "JumpSearch")
            jumpSearch(sortedData, target);
        else if (algoName == "ExponentialSearch")
            exponentialSearch(sortedData, target);

        auto end = high_resolution_clock::now();

        long long duration = duration_cast<nanoseconds>(end - start).count();
        totalTime += duration;

        if (duration > worstTime)
            worstTime = duration;
    }

    long long avgTime = totalTime / QUERIES;

    // all three search algorithms use constant extra memory
    results << algoName << "," << datasetName << "," << avgTime << "," << worstTime << "," << 0 << "\n";
}