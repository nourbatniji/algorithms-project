#ifndef SORTINGEXPERIMENT_H    
#define SORTINGEXPERIMENT_H    

#include <vector>
using namespace std;


long long measureAlphaDevTime(const vector<int> &originalData);
long long measureAlphaDevMemory(int n);
long long measureAlphaDevComparisons(vector<int> data);

long long measureTimSortTime(const vector<int> &originalData);
long long measureTimSortMemory(int n);
long long measureTimSortComparisons(vector<int> data);

long long measureIntroSortTime(const vector<int> &originalData);
long long measureIntroSortMemory(int n);
long long measureIntroSortComparisons(vector<int> data);

long long measureParallelMergeSortTime(const vector<int>& originalData);
long long measureParallelMergeSortMemory(int n);
long long measureParallelMergeSortComparisons(vector<int> data);


#endif  