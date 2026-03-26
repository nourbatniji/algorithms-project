#include "exponential_search.h"
#include "binary_search.h"

int exponentialSearch(vector<int> &data, int target)
{
    int n = data.size();

    if (data[0] == target)
        return 0;

    // find range by doubling index
    int i = 1;
    while (i < n && data[i] <= target)
        i *= 2;

    // binary search within [i/2, min(i, n-1)]
    int low = i / 2;
    int high = min(i, n - 1);

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (data[mid] == target)
            return mid;
        else if (data[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // not found
}