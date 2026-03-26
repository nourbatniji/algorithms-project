#include "introsort.h"
#include <cmath>
#include <algorithm>
using namespace std;

extern long long comparisons;

const int INSERTION_SORT_THRESHOLD = 16;


void swapValues(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void introInsertionSort(vector<int> &data, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int key = data[i];
        int j = i - 1;

        while (j >= low)
        {
            comparisons++;
            if (data[j] > key)
            {
                data[j + 1] = data[j];
                j--;
            }
            else
            {
                break;
            }
        }
        data[j + 1] = key;
    }
}

int medianOfThree(vector<int> &data, int low, int mid, int high)
{
    comparisons++;
    if (data[low] > data[mid])
        swapValues(data[low], data[mid]);

    comparisons++;
    if (data[low] > data[high])
        swapValues(data[low], data[high]);

    comparisons++;
    if (data[mid] > data[high])
        swapValues(data[mid], data[high]);

    return mid;
}

int partitionArray(vector<int> &data, int low, int high)
{
    int mid = low + (high - low) / 2;
    int pivotIndex = medianOfThree(data, low, mid, high);

    swapValues(data[pivotIndex], data[high]);
    int pivot = data[high];

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;
        if (data[j] < pivot)
        {
            i++;
            swapValues(data[i], data[j]);
        }
    }

    swapValues(data[i + 1], data[high]);
    return i + 1;
}


void heapifyRange(vector<int> &data, int start, int heapSize, int root)
{
    while (true)
    {
        int largest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < heapSize)
        {
            comparisons++;
            if (data[start + left] > data[start + largest])
                largest = left;
        }

        if (right < heapSize)
        {
            comparisons++;
            if (data[start + right] > data[start + largest])
                largest = right;
        }

        if (largest == root)
            break;

        swapValues(data[start + root], data[start + largest]);
        root = largest;
    }
}

void heapSortRange(vector<int> &data, int low, int high)
{
    int heapSize = high - low + 1;

    for (int i = heapSize / 2 - 1; i >= 0; i--)
    {
        heapifyRange(data, low, heapSize, i);
    }

    for (int i = heapSize - 1; i > 0; i--)
    {
        swapValues(data[low], data[low + i]);
        heapifyRange(data, low, i, 0);
    }
}


void introSortUtil(vector<int> &data, int low, int high, int depthLimit)
{
    while (low < high)
    {
        int size = high - low + 1;

        if (size <= INSERTION_SORT_THRESHOLD)
        {
            introInsertionSort(data, low, high);
            return;
        }

        if (depthLimit == 0)
        {
            heapSortRange(data, low, high);
            return;
        }

        int pivotIndex = partitionArray(data, low, high);

        depthLimit--;

        // sort smaller part first to reduce recursion depth
        if (pivotIndex - low < high - pivotIndex)
        {
            introSortUtil(data, low, pivotIndex - 1, depthLimit);
            low = pivotIndex + 1;
        }
        else
        {
            introSortUtil(data, pivotIndex + 1, high, depthLimit);
            high = pivotIndex - 1;
        }
    }
}

void introSort(vector<int> &data)
{
    if (data.empty())
        return;

    int depthLimit = 2 * log2(data.size());
    introSortUtil(data, 0, data.size() - 1, depthLimit);
}