#include "parallel_mergesort.h"
#include <vector>
#include <algorithm>
using namespace std;

extern long long comparisons;

// Simple merge with ONE comparison per step
void simpleMerge(vector<int>& arr, int left, int mid, int right, vector<int>& temp) {
    int i = left;
    int j = mid + 1;
    int k = left;
    
    while (i <= mid && j <= right) {
        comparisons++;  // ONLY ONE comparison per merge
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    // Copy back
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

// NO insertion sort - just recursive merge sort
void mergeSortRec(vector<int>& arr, int left, int right, vector<int>& temp) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    
    mergeSortRec(arr, left, mid, temp);
    mergeSortRec(arr, mid + 1, right, temp);
    
    simpleMerge(arr, left, mid, right, temp);
}

void parallelMergeSort(vector<int>& data) {
    if (data.empty()) return;
    vector<int> temp(data.size());
    mergeSortRec(data, 0, data.size() - 1, temp);
}

void parallelMergeSortWithComparisons(vector<int>& data) {
    comparisons = 0;
    parallelMergeSort(data);
}