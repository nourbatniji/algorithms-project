#include <iostream>
#include "datasets/datasets.h"
#include "sorting/alphadev/alphadevSorting.h"
#include "sorting/timsort/timsort.h"
#include <fstream>
#include <vector>
using namespace std;

int main()

{
    // Save original datasets to files
    
    saveToFile(generateRandoms(),              "../datasets/randoms.txt");
    saveToFile(generateNearlySorted(),        "../datasets/nearly_sorted.txt");
    saveToFile(generateReverseSorted(),       "../datasets/reverse_sorted.txt");
    saveToFile(generateDuplicates(),          "../datasets/duplicates.txt");

    //========================================================
    // AlphaDev Sort
    vector<int> ad_randoms    =  generateRandoms();
    vector<int> ad_nearly     =  generateNearlySorted();
    vector<int> ad_reversed   =  generateReverseSorted(); 
    vector<int> ad_duplicates =  generateDuplicates();

    alphaDevSort(ad_randoms, 0, ad_randoms.size() - 1);
    alphaDevSort(ad_nearly, 0, ad_nearly.size() - 1);
    alphaDevSort(ad_reversed, 0, ad_reversed.size() - 1);
    alphaDevSort(ad_duplicates, 0, ad_duplicates.size() - 1);
    
    // Save sorted datasets (alphadev)
    saveToFile(ad_randoms, "../results/alphadev/randoms_sorted_AD.txt");
    saveToFile(ad_nearly, "../results/alphadev/nearly_sorted_sorted_AD.txt");
    saveToFile(ad_reversed, "../results/alphadev/reverse_sorted_sorted_AD.txt");
    saveToFile(ad_duplicates, "../results/alphadev/duplicates_sorted_AD.txt");


    //========================================================
    // Tim Sort
    vector<int> ts_randoms    =  generateRandoms();
    vector<int> ts_nearly     =  generateNearlySorted();
    vector<int> ts_reversed   =  generateReverseSorted(); 
    vector<int> ts_duplicates =  generateDuplicates();
    
    timSort(ts_randoms);
    timSort(ts_nearly);
    timSort(ts_reversed);
    timSort(ts_duplicates);

    // Save sorted datasets (timsort)
    saveToFile(ts_randoms, "../results/timsort/randoms_sorted_TS.txt");
    saveToFile(ts_nearly, "../results/timsort/nearly_sorted_sorted_TS.txt");
    saveToFile(ts_reversed, "../results/timsort/reverse_sorted_sorted_TS.txt");
    saveToFile(ts_duplicates, "../results/timsort/duplicates_sorted_TS.txt");

    //========================================================

    cout << "Done!\n";
    return 0;
}