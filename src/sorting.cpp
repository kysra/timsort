#include "../include/sorting.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void quicksort(vector<int>& data, int low_idx, int high_idx) {
    // If partition size is 1 or 0, sort is done
    if (low_idx < high_idx){
      int p = quicksort_partition(data, low_idx, high_idx);
      quicksort(data, low_idx, p-1);
      quicksort(data, p+1, high_idx);
    }
}

int quicksort_partition(vector<int>& data, int low_idx, int high_idx) {
    // Pick middle elements as pivot 
    int pivot = data[high_idx];
    int i = low_idx -1;
  
    // Sorting the partion vs the pivot
    for (int j = low_idx; j < high_idx; j ++){
      if (data[j] < pivot) {
        i++;
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp; 
      }
    }

    // Swapping the pivot as needed
    i++;
    if (data[high_idx] < data[i]){
        swap (data[i], data[high_idx]);
    }

    // Return the pivot index
    return i;
  }

void bubblesort(vector<int>& data) {
    int vector_size = data.size();
    for (int i=0; i < vector_size - 1; i++){
        bool bubble = false;
        for (int n=0; n < vector_size - i - 1; n++){
            if (data[n] > data[n+1]){
                swap(data[n], data[n+1]);
                bubble = true;
            }
        }
        if (!bubble){
            break;
        }
    }
}

void mergesort(vector<int>& data) {
    // Split the vector into two halves
    int vector_size = data.size();
    // Returns when vector is sized 0 or 1
    if (vector_size <= 1){
        return; 
    }

    // Creates two vectors of the proper size
    int mid = vector_size/2;
    vector<int> left_vector (mid);
    vector<int> right_vector (vector_size - mid);

    // Copies data over to new vectors
    for (int i = 0; i < mid; i++){
        left_vector[i] = data[i];
    }
    for (int n = 0; n <vector_size-mid; n++){
        right_vector[n] = data[mid+n];
    }

    // Recurs algorithm to split the vector until size 0 or 1
    mergesort(left_vector);
    mergesort(right_vector);
    // Sorts the vectors after splitting
    merge(left_vector, right_vector, data);
}

void merge(vector<int>& left, vector<int>& right, vector<int>& result) {
// Declare some starting variables
    int l = 0, r=0, k=0;
    int right_size = right.size();
    int left_size = left.size();
    if (int(result.size())!= (right_size+left_size)){
        result.resize(right_size + left_size);
    }
    while (l < left_size && r < right_size){
        if (left[l] < right[r]){
        result[k] = left[l];
        l++;
        k++;
        } else {
        result[k] =right[r];
        r++;
        k++;
        }
    } 
    while (l < left_size){
        result[k] = left[l];
        l++;
        k++;
        }
    while (r < right_size){
        result[k] = right[r];
        r++;
        k++;
    }
}

void radix_sort(vector<int>& data) {
    // Radix Sort Algorithm
    int max = max_num(data);
    int digits = count(max);
    for (int i = 0; i < digits; i++){
        count_sort(data, pow(10, i));
    }
}

int max_num(vector<int>& data) {
    int size = data.size();
    int max = data[0];
    for (int i=1; i < size; i++){
        if (max<data[i]){
        max = data[i];
        }
    }
    return max;
}

int count(int n) {
    int num = 0;
    while (n>0){
        n=n/10;
        num ++;
    }
    return num;
}
  
void count_sort(vector<int>& data, int pow){
    // Counting sort algorithm implemented for Radix sort
    int count_array[]= {0,0,0,0,0,0,0,0,0,0};
    int accum_array[]= {0,0,0,0,0,0,0,0,0,0};
    int vector_size = data.size();
    vector<int> index_storage(vector_size);
    vector<int> result(vector_size);

    // Counting instances for the array
    // And logging the values in the index_storage vector
    for (int i=0; i < vector_size; i++){
        index_storage[i]= ((data[i]/pow)%10);
        count_array[index_storage[i]]++;
    }

    // Accumulating totals
    for (int i=9; i>-1; i--){
        for (int n=i; n>-1; n--){
        accum_array[i] += count_array[n];
        }
    }

    // Using accumulation index + count array index to reaarange the original values
    for (int i=0; i< vector_size; i++){
        int new_index = accum_array[index_storage[i]] - count_array[index_storage[i]];
        
        count_array[index_storage[i]]--;
        result[new_index]= data[i];
    }
    data = move(result);

}

void heapsort(vector<int>& data) {
    int size = data.size();

    // Heapify non leaves
    for (int i = size/2 - 1; i >= 0; i--){
        heapify(data, size, i);
    }
    
    // Heapify the rest
    for (int i = size - 1; i > 0; i--){
        swap(data[0], data[i]);
        heapify(data, i, 0);    
    }
}

void heapify(vector<int>& data, int n, int i) {
    // Set the root and left and right children
    int root_idx = i;
    int left_child = 2*i + 1;
    int right_child = 2*i + 2;

    // If left child is larger than root
    if (left_child < n && data[left_child] > data[root_idx]){
        root_idx = left_child;
    }
    // If right child is larger than largest so far
    if (right_child < n && data[right_child] > data[root_idx]){
        root_idx = right_child;
    }
    // If largest is not tree root, swap 
    if (root_idx != i){
        swap (data[i], data[root_idx]);
        heapify(data, n, root_idx);
    }
}

void insertionsort(vector<int>& data){
    vector<int> sorted(data.size());
    int last_idx = 0;
    sorted[0] = data[0];
    for (int i=1; i< static_cast<int>(data.size()); i++){
        for (int n=last_idx+1; n>0; n--){
            // inserts values from data into the sorted array
            if (data[i] < sorted[n-1]){
                sorted[n] = sorted[n-1];
            } else if (data[i]>sorted[last_idx]) {
                sorted[n] = data[i];
                last_idx++;
                break;
            } else{
                sorted[n+1]=sorted[n];
                sorted[n] = data[i];
                last_idx++;
                break;
            }
            if (n==1){
                sorted[0] = data[i];
                last_idx++;
                break;
            }
        }
    }
    data = move(sorted);
}
