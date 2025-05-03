#ifndef TIMSORT_H__
#define TIMSORT_H__
#include <vector>

using namespace std;

// returns a vector that is a slice of another vector
// vector<int>& data - where the slice is from
// int start - starting index of the slice 
// int end - ending index of the slice 
vector<int> slice_vector(vector<int>& data, int start, int end);

// checks if the sequence is reversed
// if the last number is smaller than the first sequence, it will swap
// and then move inwards to the next numbers and continue until
// done, or the last number is not smaller
// This is to reverse inverted sequences, which are the worse-case
// scenario for other sorts used in this algorithm
void reverse_check(vector<int>& data);

// merges together the sorted runs 
// checks for galloping behavior in the runs
// returns a merged and sorted vector 
// const vector<int>& left, right - the two vectors to be sorted 
vector<int> merge_runs(const vector<int>& left, const vector<int>& right);

// main timsort function
// splits the larger array into sections, runs
// sorts the individual runs
// merges the runs together
// vector<int>& data - vector to be sorted
void timsort(vector<int>& data);

// prints out a vector 
// const vector<int>& data - vector to be printed
void print_vector(const vector<int>& data);

#endif

