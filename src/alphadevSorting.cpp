#include "alphadevSorting.h"
#include <vector>
using namespace std;

// ─────────────────────────────────────────────
// HELPER: compare and swap two elements
// ─────────────────────────────────────────────
void compareAndSwap(vector<int> &a, int i, int j)
{
    if (a[i] > a[j])
        swap(a[i], a[j]);
}

// ─────────────────────────────────────────────
// ALPHADEV SORTING NETWORKS
// ─────────────────────────────────────────────
void sort3(vector<int> &a, int i)
{
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+0, i+2);
    compareAndSwap(a, i+1, i+2);
}

void sort4(vector<int> &a, int i)
{
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+0, i+2);
    compareAndSwap(a, i+1, i+3);
    compareAndSwap(a, i+1, i+2);
}

void sort5(vector<int> &a, int i)
{
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+0, i+2);
    compareAndSwap(a, i+1, i+4);
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+1, i+2);
    compareAndSwap(a, i+3, i+4);
    compareAndSwap(a, i+2, i+3);
}

void sort6(vector<int> &a, int i)
{
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+4, i+5);
    compareAndSwap(a, i+0, i+2);
    compareAndSwap(a, i+1, i+3);
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+4);
    compareAndSwap(a, i+3, i+5);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+4, i+5);
    compareAndSwap(a, i+1, i+4);
    compareAndSwap(a, i+1, i+2);
    compareAndSwap(a, i+3, i+4);
}

void sort7(vector<int> &a, int i)
{
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+4, i+5);
    compareAndSwap(a, i+0, i+2);
    compareAndSwap(a, i+1, i+3);
    compareAndSwap(a, i+4, i+6);
    compareAndSwap(a, i+0, i+4);
    compareAndSwap(a, i+1, i+5);
    compareAndSwap(a, i+2, i+6);
    compareAndSwap(a, i+1, i+2);
    compareAndSwap(a, i+3, i+6);
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+4);
    compareAndSwap(a, i+3, i+5);
    compareAndSwap(a, i+1, i+2);
    compareAndSwap(a, i+3, i+4);
    compareAndSwap(a, i+5, i+6);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+4, i+5);
}

void sort8(vector<int> &a, int i)
{
    compareAndSwap(a, i+0, i+1);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+4, i+5);
    compareAndSwap(a, i+6, i+7);
    compareAndSwap(a, i+0, i+2);
    compareAndSwap(a, i+1, i+3);
    compareAndSwap(a, i+4, i+6);
    compareAndSwap(a, i+5, i+7);
    compareAndSwap(a, i+0, i+4);
    compareAndSwap(a, i+1, i+5);
    compareAndSwap(a, i+2, i+6);
    compareAndSwap(a, i+3, i+7);
    compareAndSwap(a, i+1, i+2);
    compareAndSwap(a, i+3, i+5);
    compareAndSwap(a, i+4, i+6);
    compareAndSwap(a, i+1, i+4);
    compareAndSwap(a, i+2, i+4);
    compareAndSwap(a, i+3, i+6);
    compareAndSwap(a, i+5, i+6);
    compareAndSwap(a, i+2, i+3);
    compareAndSwap(a, i+4, i+5);
    compareAndSwap(a, i+3, i+4);
}

// ─────────────────────────────────────────────
// MERGE: merges two sorted halves
// ─────────────────────────────────────────────
void merge(vector<int> &data, int low, int mid, int high)
{
    vector<int> temp(high - low + 1);

    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (data[i] <= data[j])
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while (i <= mid)
        temp[k++] = data[i++];

    while (j <= high)
        temp[k++] = data[j++];

    for (int x = 0; x < k; x++)
        data[low + x] = temp[x];
}

// ─────────────────────────────────────────────
// ALPHADEV HYBRID SORT
// ─────────────────────────────────────────────
void alphaDevSort(vector<int> &data, int low, int high)
{
    int size = high - low + 1;

    if (size <= 2) { compareAndSwap(data, low, high); return; }
    if (size == 3) { sort3(data, low); return; }
    if (size == 4) { sort4(data, low); return; }
    if (size == 5) { sort5(data, low); return; }
    if (size == 6) { sort6(data, low); return; }
    if (size == 7) { sort7(data, low); return; }
    if (size == 8) { sort8(data, low); return; }

    int mid = low + (high - low) / 2;
    alphaDevSort(data, low, mid);
    alphaDevSort(data, mid + 1, high);
    merge(data, low, mid, high);
}