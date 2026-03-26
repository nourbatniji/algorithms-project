#include <iostream>
#include "datasets/datasets.h"
#include "sorting/alphadev/alphadevsort.h"
#include "sorting/timsort/timsort.h"
#include "sorting/introsort/introsort.h"
#include "sorting/parallel/parallel_mergesort.h"
#include "experiments/sorting_experiments.h"
#include "experiments/searching_experiments.h"
#include <fstream>
#include <vector>
#include <chrono>

#ifdef _OPENMP
#include <omp.h> // ← ADD THIS
#endif
using namespace chrono;
using namespace std;

//========================================================
long long comparisons = 0;

int main()
{

    cout << "Starting experiments...\n";
    //========================================================
    // Open results files
    ofstream time_results("../results/sorting_time_results.csv");
    ofstream memory_results("../results/sorting_memory_results.csv");
    ofstream comparison_results("../results/sorting_comparison_results.csv");
    ofstream search_results("../results/search_results.csv");
    time_results << "Algorithm,Dataset,ExecutionTime_µs\n";
    memory_results << "Algorithm,Dataset,Memory_KB\n";
    comparison_results << "Algorithm,Dataset,Comparisons\n";
    search_results << "Algorithm,Dataset,AvgTime_ns,WorstTime_ns,Memory_KB\n";

    //========================================================
    // Data sets generation
    cout << "Generating datasets...\n";
    vector<int> random_data = generateRandoms();
    vector<int> nearly_sorted = generateNearlySorted();
    vector<int> reversed_sorted = generateReverseSorted();
    vector<int> duplicates = generateDuplicates();
    cout << "Datasets generated.\n";

    // Save original datasets to files
    saveToFile(random_data, "../datasets/randoms.txt");
    saveToFile(nearly_sorted, "../datasets/nearly_sorted.txt");
    saveToFile(reversed_sorted, "../datasets/reverse_sorted.txt");
    saveToFile(duplicates, "../datasets/duplicates.txt");

    //========================================================
    // AlphaDev Sort
    cout << "Running AlphaDev\n";
    vector<int> ad_randoms = random_data;
    vector<int> ad_nearly = nearly_sorted;
    vector<int> ad_reversed = reversed_sorted;
    vector<int> ad_duplicates = duplicates;

    // Save execution time results in time results file
    time_results << "AlphaDev,Randoms," << measureAlphaDevTime(ad_randoms) << "\n";
    time_results << "AlphaDev,NearlySorted," << measureAlphaDevTime(ad_nearly) << "\n";
    time_results << "AlphaDev,ReverseSorted," << measureAlphaDevTime(ad_reversed) << "\n";
    time_results << "AlphaDev,Duplicates," << measureAlphaDevTime(ad_duplicates) << "\n";

    // Save execution time results in memory results file
    memory_results << "AlphaDev,Randoms," << measureAlphaDevMemory(ad_randoms.size()) << "\n";
    memory_results << "AlphaDev,NearlySorted," << measureAlphaDevMemory(ad_nearly.size()) << "\n";
    memory_results << "AlphaDev,ReverseSorted," << measureAlphaDevMemory(ad_reversed.size()) << "\n";
    memory_results << "AlphaDev,Duplicates," << measureAlphaDevMemory(ad_duplicates.size()) << "\n";

    // Save number of comparisons in comparisons file
    comparison_results << "AlphaDev,Randoms," << measureAlphaDevComparisons(ad_randoms) << "\n";
    comparison_results << "AlphaDev,NearlySorted," << measureAlphaDevComparisons(ad_nearly) << "\n";
    comparison_results << "AlphaDev,ReverseSorted," << measureAlphaDevComparisons(ad_reversed) << "\n";
    comparison_results << "AlphaDev,Duplicates," << measureAlphaDevComparisons(ad_duplicates) << "\n";

    // Sort for saving
    alphaDevSort(ad_randoms);
    alphaDevSort(ad_nearly);
    alphaDevSort(ad_reversed);
    alphaDevSort(ad_duplicates);

    // Save sorted datasets (alphadev)
    saveToFile(ad_randoms, "../results/alphadev/randoms_sorted_AD.txt");
    saveToFile(ad_nearly, "../results/alphadev/nearly_sorted_sorted_AD.txt");
    saveToFile(ad_reversed, "../results/alphadev/reverse_sorted_sorted_AD.txt");
    saveToFile(ad_duplicates, "../results/alphadev/duplicates_sorted_AD.txt");

    cout << "AlphaDev complete\n";

    //========================================================
    // TIMSORT
    cout << "Running TimSort...\n";
    vector<int> ts_randoms = random_data;
    vector<int> ts_nearly = nearly_sorted;
    vector<int> ts_reversed = reversed_sorted;
    vector<int> ts_duplicates = duplicates;

    // Save execution time results
    time_results << "TimSort,Randoms," << measureTimSortTime(ts_randoms) << "\n";
    time_results << "TimSort,NearlySorted," << measureTimSortTime(ts_nearly) << "\n";
    time_results << "TimSort,ReverseSorted," << measureTimSortTime(ts_reversed) << "\n";
    time_results << "TimSort,Duplicates," << measureTimSortTime(ts_duplicates) << "\n";

    // Save execution memory results
    memory_results << "TimSort,Randoms," << measureTimSortMemory(ts_randoms.size()) << "\n";
    memory_results << "TimSort,NearlySorted," << measureTimSortMemory(ts_nearly.size()) << "\n";
    memory_results << "TimSort,ReverseSorted," << measureTimSortMemory(ts_reversed.size()) << "\n";
    memory_results << "TimSort,Duplicates," << measureTimSortMemory(ts_duplicates.size()) << "\n";

    // Save number of comparisons in comparisons file
    comparison_results << "TimSort,Randoms," << measureTimSortComparisons(ts_randoms) << "\n";
    comparison_results << "TimSort,NearlySorted," << measureTimSortComparisons(ts_nearly) << "\n";
    comparison_results << "TimSort,ReverseSorted," << measureTimSortComparisons(ts_reversed) << "\n";
    comparison_results << "TimSort,Duplicates," << measureTimSortComparisons(ts_duplicates) << "\n";

    // Sort for saving
    timSort(ts_randoms);
    timSort(ts_nearly);
    timSort(ts_reversed);
    timSort(ts_duplicates);

    // Save sorted datasets (timsort)
    saveToFile(ts_randoms, "../results/timsort/randoms_sorted_TS.txt");
    saveToFile(ts_nearly, "../results/timsort/nearly_sorted_sorted_TS.txt");
    saveToFile(ts_reversed, "../results/timsort/reverse_sorted_sorted_TS.txt");
    saveToFile(ts_duplicates, "../results/timsort/duplicates_sorted_TS.txt");

    cout << "TimSort complete\n";

    //========================================================
    // INTROSORT
    cout << "Running IntroSort...\n";
    vector<int> intro_randoms = random_data;
    vector<int> intro_nearly = nearly_sorted;
    vector<int> intro_reversed = reversed_sorted;
    vector<int> intro_duplicates = duplicates;

    // Save execution time results
    time_results << "IntroSort,Randoms," << measureIntroSortTime(intro_randoms) << "\n";
    time_results << "IntroSort,NearlySorted," << measureIntroSortTime(intro_nearly) << "\n";
    time_results << "IntroSort,ReverseSorted," << measureIntroSortTime(intro_reversed) << "\n";
    time_results << "IntroSort,Duplicates," << measureIntroSortTime(intro_duplicates) << "\n";

    // Save execution memory results
    memory_results << "IntroSort,Randoms," << measureIntroSortMemory(intro_randoms.size()) << "\n";
    memory_results << "IntroSort,NearlySorted," << measureIntroSortMemory(intro_nearly.size()) << "\n";
    memory_results << "IntroSort,ReverseSorted," << measureIntroSortMemory(intro_reversed.size()) << "\n";
    memory_results << "IntroSort,Duplicates," << measureIntroSortMemory(intro_duplicates.size()) << "\n";

    // Save number of comparisons in comparisons file
    comparison_results << "IntroSort,Randoms," << measureIntroSortComparisons(intro_randoms) << "\n";
    comparison_results << "IntroSort,NearlySorted," << measureIntroSortComparisons(intro_nearly) << "\n";
    comparison_results << "IntroSort,ReverseSorted," << measureIntroSortComparisons(intro_reversed) << "\n";
    comparison_results << "IntroSort,Duplicates," << measureIntroSortComparisons(intro_duplicates) << "\n";

    // Sort for saving
    introSort(intro_randoms);
    introSort(intro_nearly);
    introSort(intro_reversed);
    introSort(intro_duplicates);

    // Save sorted datasets (timsort)
    saveToFile(intro_randoms, "../results/introsort/randoms_sorted_intro.txt");
    saveToFile(intro_nearly, "../results/introsort/nearly_sorted_sorted_intro.txt");
    saveToFile(intro_reversed, "../results/introsort/reverse_sorted_sorted_intro.txt");
    saveToFile(intro_duplicates, "../results/introsort/duplicates_sorted_PDQ.txt");

    cout << "IntroSort complete.\n";

    //========================================================
    // PARALLEL MERGE SORT
    cout << "running parallel .\n";

    vector<int> parallel_randoms = random_data;
    vector<int> parallel_nearly = nearly_sorted;
    vector<int> parallel_reversed = reversed_sorted;
    vector<int> parallel_duplicates = duplicates;

    time_results << "ParallelMergeSort,Randoms," << measureParallelMergeSortTime(parallel_randoms) << "\n";
    time_results << "ParallelMergeSort,NearlySorted," << measureParallelMergeSortTime(parallel_nearly) << "\n";
    time_results << "ParallelMergeSort,ReverseSorted," << measureParallelMergeSortTime(parallel_reversed) << "\n";
    time_results << "ParallelMergeSort,Duplicates," << measureParallelMergeSortTime(parallel_duplicates) << "\n";

    memory_results << "ParallelMergeSort,Randoms," << measureParallelMergeSortMemory(parallel_randoms.size()) << "\n";
    memory_results << "ParallelMergeSort,NearlySorted," << measureParallelMergeSortMemory(parallel_nearly.size()) << "\n";
    memory_results << "ParallelMergeSort,ReverseSorted," << measureParallelMergeSortMemory(parallel_reversed.size()) << "\n";
    memory_results << "ParallelMergeSort,Duplicates," << measureParallelMergeSortMemory(parallel_duplicates.size()) << "\n";

    comparison_results << "ParallelMergeSort,Randoms," << measureParallelMergeSortComparisons(parallel_randoms) << "\n";
    comparison_results << "ParallelMergeSort,NearlySorted," << measureParallelMergeSortComparisons(parallel_nearly) << "\n";
    comparison_results << "ParallelMergeSort,ReverseSorted," << measureParallelMergeSortComparisons(parallel_reversed) << "\n";
    comparison_results << "ParallelMergeSort,Duplicates," << measureParallelMergeSortComparisons(parallel_duplicates) << "\n";

    //========================================================
    // Search Experiments
    // Binary Search
    cout << "Running search experiments...\n";
    measureSearchPerformance(intro_randoms, "BinarySearch", "Randoms", search_results);
    measureSearchPerformance(intro_nearly, "BinarySearch", "NearlySorted", search_results);
    measureSearchPerformance(intro_reversed, "BinarySearch", "ReverseSorted", search_results);
    measureSearchPerformance(intro_duplicates, "BinarySearch", "Duplicates", search_results);

    // Jump Search
    measureSearchPerformance(intro_randoms, "JumpSearch", "Randoms", search_results);
    measureSearchPerformance(intro_nearly, "JumpSearch", "NearlySorted", search_results);
    measureSearchPerformance(intro_reversed, "JumpSearch", "ReverseSorted", search_results);
    measureSearchPerformance(intro_duplicates, "JumpSearch", "Duplicates", search_results);

    // Exponential Search
    measureSearchPerformance(intro_randoms, "ExponentialSearch", "Randoms", search_results);
    measureSearchPerformance(intro_nearly, "ExponentialSearch", "NearlySorted", search_results);
    measureSearchPerformance(intro_reversed, "ExponentialSearch", "ReverseSorted", search_results);
    measureSearchPerformance(intro_duplicates, "ExponentialSearch", "Duplicates", search_results);

    // Sorting 100 Million Numbers

    // Generate data
    const int BIG_SIZE = 100000000;

    vector<int> big_data = generateRandomsBig(BIG_SIZE);

    // Open CSV file
    ofstream hundredM_experiment("../results/100M_results.csv");
    hundredM_experiment << "Algorithm,Time_ms\n";

    // AlphaDev
    vector<int> alpha_big = big_data;
    auto start = high_resolution_clock::now();
    alphaDevSort(alpha_big);
    auto alpha_time = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    hundredM_experiment << "AlphaDev," << alpha_time << "\n";

    // TimSort
    vector<int> tim_big = big_data;
    start = high_resolution_clock::now();
    timSort(tim_big);
    auto tim_time = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    hundredM_experiment << "TimSort," << tim_time << "\n";

    // IntroSort
    vector<int> intro_big = big_data;
    start = high_resolution_clock::now();
    introSort(intro_big);
    auto intro_time = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    hundredM_experiment << "IntroSort," << intro_time << "\n";

    // ParallelMergeSort
    vector<int> parallel_big = big_data;
    start = high_resolution_clock::now();
    parallelMergeSort(parallel_big);
    auto parallel_time = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
    hundredM_experiment << "ParallelMergeSort," << parallel_time << "\n";

    cout << "Done!\n";
    return 0;
}