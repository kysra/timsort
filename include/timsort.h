#ifndef TIMSORT_H__
#define TIMSORT_H__
#include <vector>

using namespace std;

vector<int> slice_vector(vector<int>& data, int start, int end);

void timsort(vector<int>& data);

void print_vector(const vector<int>& data);

#endif

