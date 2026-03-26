#ifndef SEARCHING_EXPERIMENTS_H
#define SEARCHING_EXPERIMENTS_H

#include <vector>
#include <fstream>
#include <string>
using namespace std;

void measureSearchPerformance(vector<int> &sortedData, string algoName, string datasetName, ofstream &results);

#endif