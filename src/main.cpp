#include <iostream>
#include "datasets.h"
#include "alphadevSorting.h"
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    vector<int> randomData = generateRandoms();
    saveToFile(randomData, "randoms.txt");

    alphaDevSort(randomData, 0, randomData.size() - 1);
    saveToFile(randomData, "randoms_sorted.txt");

    int minVal = INT_MAX;

    for (int x : randomData)
        minVal = min(minVal, x);

    cout << "Min = " << minVal << endl;
    
    cout << "Done!\n";
    return 0;
}