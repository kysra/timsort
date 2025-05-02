#ifndef SORTING_H__
#define SORITNG_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;


void quicksort(vector<int>& data, int low_idx, int high_idx);

int quicksort_partition(vector<int>& data, int low_idx, int high_idx);

void bubblesort(vector<int>& data);

void mergesort(vector<int>& data);

void merge(vector<int>& left, vector<int>& right, vector<int>& result);

void radix_sort(vector<int>& data);

int max_num(vector<int>& data);

int count(int n);

void count_sort(vector<int>& data, int pow);

void heapsort(vector<int>& data);

void heapify(vector<int>& data, int n, int i);

void insertionsort(vector<int>& data);

#endif