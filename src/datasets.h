#include <vector>
#include <string>
using namespace std;

vector<int> generateRandoms();
vector<int> generateNearlySorted();
vector<int> generateReverseSorted();
vector<int> generateDuplicates();
void saveToFile(const vector<int>& data, const string& filename);