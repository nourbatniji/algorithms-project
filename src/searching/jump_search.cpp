#include "jump_search.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int jumpSearch(vector<int> &data, int target)
{
    int n = data.size();
    int step = sqrt(n); // block size = root n
    int prev = 0;

    // jump forward until we find a block where target might be
    while (prev < n && data[min(step, n) - 1] < target)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    // linear scan forward within the block
    while (data[prev] < target)
    {
        prev++;
        if (prev == std::min(step, n))
            return -1; // not found
    }

    if (data[prev] == target)
        return prev;

    return -1; // not found
}