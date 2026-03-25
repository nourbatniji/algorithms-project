#include <iostream>
#include "datasets/datasets.h"
#include "sorting/alphadev/alphadevSorting.h"
#include "sorting/timsort/timsort.h"
#include "sorting/pdqsort/pdqsort.h"
#include <fstream>
#include <vector>
#include <chrono>
using namespace chrono;
using namespace std;


long long measureAlphaDevTime(vector<int> &data){
    auto start = high_resolution_clock::now();
    alphaDevSort(data, 0, data.size() - 1);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}
long long measureTimSortTime(vector<int> &data){
    auto start = high_resolution_clock::now();
    timSort(data);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}
long long measurePDQSortTime(vector<int> &data){
    auto start = high_resolution_clock::now();
    pdqsort(data.begin(), data.end());
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main()
{
    ofstream results("../results/sorting_results.csv");
    results << "Algorithm,Dataset,ExecutionTime_µs\n";


    //========================================================
    // Data sets generation 
    vector<int> random_data    =  generateRandoms();
    vector<int> nearly_sorted     =  generateNearlySorted();
    vector<int> reversed_sorted   =  generateReverseSorted(); 
    vector<int> duplicates =  generateDuplicates();

    // Save original datasets to files
    saveToFile(random_data,     "../datasets/randoms.txt");
    saveToFile(nearly_sorted,      "../datasets/nearly_sorted.txt");
    saveToFile(reversed_sorted,    "../datasets/reverse_sorted.txt");
    saveToFile(duplicates,  "../datasets/duplicates.txt");

    
    //========================================================
    // AlphaDev Sort
    vector<int> ad_randoms    =  random_data;
    vector<int> ad_nearly     =  nearly_sorted;
    vector<int> ad_reversed   =  reversed_sorted; 
    vector<int> ad_duplicates =  duplicates;
    
    
    alphaDevSort(ad_nearly, 0, ad_nearly.size() - 1);
    alphaDevSort(ad_reversed, 0, ad_reversed.size() - 1);
    alphaDevSort(ad_duplicates, 0, ad_duplicates.size() - 1);
    
    // Save sorted datasets (alphadev)
    saveToFile(ad_randoms, "../results/alphadev/randoms_sorted_AD.txt");
    saveToFile(ad_nearly, "../results/alphadev/nearly_sorted_sorted_AD.txt");
    saveToFile(ad_reversed, "../results/alphadev/reverse_sorted_sorted_AD.txt");
    saveToFile(ad_duplicates, "../results/alphadev/duplicates_sorted_AD.txt");
    
    // Save execution time results 
    results << "AlphaDev, Randoms, " << measureAlphaDevTime(ad_randoms) << "\n";
    results << "AlphaDev, NearlySorted, " << measureAlphaDevTime(ad_nearly) << "\n";
    results << "AlphaDev, ReverseSorted, " << measureAlphaDevTime(ad_reversed) << "\n";
    results << "AlphaDev, Duplicates, " << measureAlphaDevTime(ad_duplicates) << "\n";

    //========================================================
    // Tim Sort
    vector<int> ts_randoms    =  random_data;
    vector<int> ts_nearly     =  nearly_sorted;
    vector<int> ts_reversed   =  reversed_sorted; 
    vector<int> ts_duplicates =  duplicates;
    
    timSort(ts_randoms);
    timSort(ts_nearly);
    timSort(ts_reversed);
    timSort(ts_duplicates);

    // Save sorted datasets (timsort)
    saveToFile(ts_randoms, "../results/timsort/randoms_sorted_TS.txt");
    saveToFile(ts_nearly, "../results/timsort/nearly_sorted_sorted_TS.txt");
    saveToFile(ts_reversed, "../results/timsort/reverse_sorted_sorted_TS.txt");
    saveToFile(ts_duplicates, "../results/timsort/duplicates_sorted_TS.txt");

    // Save execution time results 
    results << "TimSort, Randoms, " << measureTimSortTime(ts_randoms) << "\n";
    results << "TimSort, NearlySorted, " << measureTimSortTime(ts_nearly) << "\n";
    results << "TimSort, ReverseSorted, " << measureTimSortTime(ts_reversed) << "\n";
    results << "TimSort, Duplicates, " << measureTimSortTime(ts_duplicates) << "\n";

    //========================================================

    //========================================================
    // PDQ Sort
    vector<int> pdq_randoms    =  random_data;
    vector<int> pdq_nearly     =  nearly_sorted;
    vector<int> pdq_reversed   =  reversed_sorted; 
    vector<int> pdq_duplicates =  duplicates;
    
    pdqsort(pdq_randoms.begin(), pdq_randoms.end());
    pdqsort(pdq_nearly.begin(), pdq_nearly.end());
    pdqsort(pdq_reversed.begin(), pdq_reversed.end());
    pdqsort(pdq_duplicates.begin(), pdq_duplicates.end());

    // Save sorted datasets (timsort)
    saveToFile(pdq_randoms, "../results/pdq/randoms_sorted_PDQ.txt");
    saveToFile(pdq_nearly, "../results/pdq/nearly_sorted_sorted_PDQ.txt");
    saveToFile(pdq_reversed, "../results/pdq/reverse_sorted_sorted_PDQ.txt");
    saveToFile(pdq_duplicates, "../results/pdq/duplicates_sorted_PDQ.txt");

    // Save execution time results 
    results << "PDQSort, Randoms, " << measurePDQSortTime(ts_randoms) << "\n";
    results << "PDQSort, NearlySorted, " << measurePDQSortTime(ts_nearly) << "\n";
    results << "PDQSort, ReverseSorted, " << measurePDQSortTime(ts_reversed) << "\n";
    results << "PDQSort, Duplicates, " << measureTimSortTime(ts_duplicates) << "\n";

    //========================================================

    cout << "Done!\n";
    return 0;
}