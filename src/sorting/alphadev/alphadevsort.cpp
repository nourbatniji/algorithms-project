#include "alphadevsort.h"
#include <vector>
using namespace std;

extern long long comparisons;

// Compare and swap two elements
void compareAndSwap(vector<int> &a, int i, int j)
{
    comparisons++;
    if (a[i] > a[j])
        swap(a[i], a[j]);
}

void sort3(vector<int> &a, int i)
{
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 0, i + 2);
    compareAndSwap(a, i + 1, i + 2);
}

void sort4(vector<int> &a, int i)
{
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 0, i + 2);
    compareAndSwap(a, i + 1, i + 3);
    compareAndSwap(a, i + 1, i + 2);
}

void sort5(vector<int> &a, int i)
{
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 0, i + 2);
    compareAndSwap(a, i + 1, i + 4);
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 1, i + 2);
    compareAndSwap(a, i + 3, i + 4);
    compareAndSwap(a, i + 2, i + 3);
}

void sort6(vector<int> &a, int i)
{
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 4, i + 5);
    compareAndSwap(a, i + 0, i + 2);
    compareAndSwap(a, i + 1, i + 3);
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 4);
    compareAndSwap(a, i + 3, i + 5);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 4, i + 5);
    compareAndSwap(a, i + 1, i + 4);
    compareAndSwap(a, i + 1, i + 2);
    compareAndSwap(a, i + 3, i + 4);
}

void sort7(vector<int> &a, int i)
{
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 4, i + 5);
    compareAndSwap(a, i + 0, i + 2);
    compareAndSwap(a, i + 1, i + 3);
    compareAndSwap(a, i + 4, i + 6);
    compareAndSwap(a, i + 0, i + 4);
    compareAndSwap(a, i + 1, i + 5);
    compareAndSwap(a, i + 2, i + 6);
    compareAndSwap(a, i + 1, i + 2);
    compareAndSwap(a, i + 3, i + 6);
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 4);
    compareAndSwap(a, i + 3, i + 5);
    compareAndSwap(a, i + 1, i + 2);
    compareAndSwap(a, i + 3, i + 4);
    compareAndSwap(a, i + 5, i + 6);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 4, i + 5);
}

void sort8(vector<int> &a, int i)
{
    compareAndSwap(a, i + 0, i + 1);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 4, i + 5);
    compareAndSwap(a, i + 6, i + 7);
    compareAndSwap(a, i + 0, i + 2);
    compareAndSwap(a, i + 1, i + 3);
    compareAndSwap(a, i + 4, i + 6);
    compareAndSwap(a, i + 5, i + 7);
    compareAndSwap(a, i + 0, i + 4);
    compareAndSwap(a, i + 1, i + 5);
    compareAndSwap(a, i + 2, i + 6);
    compareAndSwap(a, i + 3, i + 7);
    compareAndSwap(a, i + 1, i + 2);
    compareAndSwap(a, i + 3, i + 5);
    compareAndSwap(a, i + 4, i + 6);
    compareAndSwap(a, i + 1, i + 4);
    compareAndSwap(a, i + 2, i + 4);
    compareAndSwap(a, i + 3, i + 6);
    compareAndSwap(a, i + 5, i + 6);
    compareAndSwap(a, i + 2, i + 3);
    compareAndSwap(a, i + 4, i + 5);
    compareAndSwap(a, i + 3, i + 4);
}

// Merge: merges two sorted halves
void alphaMerge(vector<int> &data, int low, int mid, int high, vector<int> &temp)
{
    for (int x = low; x <= high; x++)
        temp[x] = data[x];

    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high)
    {
        comparisons++;
        data[k++] = (temp[i] <= temp[j]) ? temp[i++] : temp[j++];
    }
    while (i <= mid)
        data[k++] = temp[i++];
    while (j <= high)
        data[k++] = temp[j++];
}

void alphaDevSort(vector<int> &data, int low, int high, vector<int> &temp)
{
    int size = high - low + 1;

    if (size <= 1)
        return; // 1 element is already sorted, nothing to do
    if (size == 2)
    {
        compareAndSwap(data, low, high);
        return;
    }
    if (size == 3)
    {
        sort3(data, low);
        return;
    }
    if (size == 4)
    {
        sort4(data, low);
        return;
    }
    if (size == 5)
    {
        sort5(data, low);
        return;
    }
    if (size == 6)
    {
        sort6(data, low);
        return;
    }
    if (size == 7)
    {
        sort7(data, low);
        return;
    }
    if (size == 8)
    {
        sort8(data, low);
        return;
    }

    // for arrays larger than 8: split, sort each half, then merge
    int mid = low + (high - low) / 2; // to avoid integer overflow
    alphaDevSort(data, low, mid, temp);
    alphaDevSort(data, mid + 1, high, temp);
    comparisons++;
    if (data[mid] <= data[mid + 1])
        return;
    alphaMerge(data, low, mid, high, temp);
}

// Public entry point — allocates temp once
void alphaDevSort(vector<int> &data)
{
    vector<int> temp(data.size());
    alphaDevSort(data, 0, data.size() - 1, temp);
}