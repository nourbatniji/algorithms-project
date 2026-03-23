#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

const int N = 1000000;
mt19937 mersenne_twister(42); // mt19937 is the Mersenne Twister random number engine, seeded with 42 so it gives same results every run

// 1. GENERATING RANDOMS
vector<int> generateRandoms()
{
	vector<int> data(N);					  // creating a vector of size N
	uniform_int_distribution<int> dist(1, N); // range of randoms from 1 to 1m

	for (int i = 0; i < N; i++)
	{
		data[i] = dist(mersenne_twister); // take random value from engine, and convert it into a number within the range, assign it with this vector element
	}
	return data;
}

// 2. GENERATING NEARLY SORTED
vector<int> generateNearlySorted()
{
	vector<int> data(N);

	for (int i = 0; i < N; i++)
	{
		data[i] = i + 1;
	}

	for (int i = 0; i < N / 100; i++) // 10 000 swaps we do (1%)
	{
		int position = i * 100; // pick a pos every 100 steps
		swap(data[position], data[position + 1]);
	}
	return data;
}

// 3. GENERATING REVERSED SORTED
vector<int> generateReverseSorted()
{
	vector<int> data = generateRandoms();
	sort(data.begin(), data.end(), greater<int>()); //(start iterator, end iterator, comparator)  nlogn
	return data;
}

// 4. GENERATING DUPLICATES
vector<int> generateDuplicates()
{
	vector<int> data(N);
	uniform_int_distribution<int> dist(1, 1000);
	for (int i = 0; i < N; i++){
		data[i] = dist(mersenne_twister);
	}
	return data;
}

void saveToFile(const vector<int> &data, const string &filename)
{ // pass data and filename with reference. never modify
	ofstream file(filename);
	for (int x : data)
	{ // loops through every number in data
		file << x << "\n";
	}
}

int main()
{
	saveToFile(generateRandoms(), "randoms.txt");
	saveToFile(generateNearlySorted(), "nearly_sorted.txt");
	saveToFile(generateReverseSorted(), "reverse_sorted.txt");
	saveToFile(generateDuplicates(), "duplicates.txt");
	return 0;
}