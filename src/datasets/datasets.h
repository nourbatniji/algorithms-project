#ifndef DATASETS_H
#define DATASETS_H

#include <vector>
#include <string>
using namespace std;

vector<int> generateRandoms();
vector<int> generateNearlySorted();
vector<int> generateReverseSorted();
vector<int> generateDuplicates();

vector<int> generateRandomsBig(int size);

void saveToFile(const vector<int>& data, const string& filename);


#endif
