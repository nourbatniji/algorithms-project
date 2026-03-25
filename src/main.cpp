#include <iostream>
#include "datasets/datasets.h"
#include "sorting/alphadev/alphadevSorting.h"
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<int> randomData = generateRandoms();
    vector<int> nearlySortedData = generateNearlySorted();
    vector<int> reverseSortedData = generateReverseSorted(); 
    vector<int> duplicatedData = generateDuplicates();

    // Save original datasets
    saveToFile(randomData, "../datasets/randoms.txt");
    saveToFile(nearlySortedData, "../datasets/nearly_sorted.txt");
    saveToFile(reverseSortedData, "../datasets/reverse_sorted.txt");
    saveToFile(duplicatedData, "../datasets/duplicates.txt");

    // Sort ALL datasets (not just one)
    alphaDevSort(randomData, 0, randomData.size() - 1);
    alphaDevSort(nearlySortedData, 0, nearlySortedData.size() - 1);
    alphaDevSort(reverseSortedData, 0, reverseSortedData.size() - 1);
    alphaDevSort(duplicatedData, 0, duplicatedData.size() - 1);

    // Save sorted datasets
    saveToFile(randomData, "../results/alphadev/randoms_sorted_AD.txt");
    saveToFile(nearlySortedData, "../results/alphadev/nearly_sorted_sorted_AD.txt");
    saveToFile(reverseSortedData, "../results/alphadev/reverse_sorted_sorted_AD.txt");
    saveToFile(duplicatedData, "../results/alphadev/duplicates_sorted_AD.txt");

    cout << "Done!\n";
    return 0;
}