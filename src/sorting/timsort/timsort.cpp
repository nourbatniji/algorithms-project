#include <vector>
#include "timsort.h"
using namespace std;

const int RUN = 32;

void insertionSort(vector<int> &data, int low, int high)
{
    for (int i = low + 1; i <= high; i++) // starts from second element of the run
    {
        int key = data[i];
        int j = i - 1;

        while (j >= low && data[j] > key) // shift elements right until correct position found
        {
            data[j + 1] = data[j]; // shift right
            j--;
        }
        data[j + 1] = key; // put the smaller key to the left
    }
}

void merge(vector<int> &data, int low, int mid, int high)
{
    vector<int> temp(high - low + 1);
    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (data[i] <= data[j])
        {
            temp[k++] = data[i++];
        }
        else
        {
            temp[k++] = data[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = data[i++];
    }
    while (j <= high)
    {
        temp[k++] = data[j++];
    }
    for (int x = 0; x < k; x++)
    {
        data[low + x] = temp[x];
    }
}
void timSort(vector<int> &data)
{
    int n = data.size(); //number of elements

    // ── PHASE 1: sort every run using insertion sort ──
    for (int i = 0; i < n; i += RUN)
    {
        int right = min(i + RUN - 1, n - 1);
        insertionSort(data, i, right);
    }

    // ── PHASE 2: merge sorted runs together ──
    for (int size = RUN; size < n; size *= 2) 
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            if (mid < right)
            {
                    merge(data, left, mid, right);
            }
        }
    }
}