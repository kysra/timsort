#ifndef SORTING_H__
#define SORITNG_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// quicksort algorithm, uses quicksort_partition
// vector<int>& data - vector to be sorted 
// int low_idx - lower end of the partition
// int high_idx - high end of the partition
void quicksort(vector<int>& data, int low_idx, int high_idx);
// used in the quicksort algorithm
// sorts the numbers in data versus the pivot
// vector<int>& data - vector to be sorted 
// int low_idx - lower end of the partition
// int high_idx - high end of the partition, pivot
int quicksort_partition(vector<int>& data, int low_idx, int high_idx);

// bubble sort algorithm, "bubbles" numbers to the top
// very slow and inefficient, unless the data is already sorted 
// vector<int>& data - to be sorted
void bubblesort(vector<int>& data);

// merge sort algorithm, splits arrays down until size 0 and 1
// then merges them back together to sort them
// vector<int>& data - to be sorted 
void mergesort(vector<int>& data);

// handles the remerging required of the merge sort function
// compares the values in the left and right vectors, and merges
// them back into the result
// vector<int>& left, vector<int>& right - the two functions to sort 
// vector<int>& result) - where we put the sorted data
void merge(vector<int>& left, vector<int>& right, vector<int>& result);

// radix sort, very fast method that uses buckets
// uses max_num and counting sort functions
// sorts the the 1s digit, then then 10s digit, etc
void radix_sort(vector<int>& data);
// finds the maximum value in the vector
// vector<int>& data - target data set 
int max_num(vector<int>& data);
// finds how many digits are in the largest number
int count(int n);
// organizes numbers into various buckets by value
void count_sort(vector<int>& data, int pow);

// builds a prioirity heap and then sorts the data within that heap
// sorts the leaves and then works back up
// vector<int>& data - data to be sorted
void heapsort(vector<int>& data);
// swaps the top of the tree and child if child is larger
// percolates down to maintain heap rules
// vector<int>& data - tree to heapify
// int n - size of the heap
// int i - index of the root
void heapify(vector<int>& data, int n, int i);

// insertion heap, works by inserting values into place
// used in the timsort function
void insertionsort(vector<int>& data);

#endif