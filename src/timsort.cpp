#include "../include/timsort.h"
#include "../include/sorting.h"
#include <vector>
#include <algorithm>

using namespace std;

vector<int> slice_vector(vector<int>& data, int start, int end){
    return vector<int>(data.begin()+start, data.begin()+end);
}

void reverse_check(vector<int>& data){
    int size = data.size();
    for (int n=0; n<size; n++){
        if (data[size-1-n]<data[n]){
            swap(data[size-1-n], data[n]);
        } else {
                return;
        }
    }
}

void print_vector(const vector<int>& data) {
    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

vector<int> merge_runs(const vector<int>& left, const vector<int>& right){
    int left_size = left.size();
    int left_idx = 0;
    int right_size = right.size();
    int right_idx = 0;
    vector<int> merged;

    if (left.front() > right.back()){
        // checkings for galloping
        // add all of left onto right
        merged = right;
        merged.insert(merged.end(), left.begin(), left.end());
        return merged;
    } else if (right.front() > left.back()){
        // add all of right onto left 
        merged = left;
        merged.insert(merged.end(), right.begin(), right.end());
        return merged;
    }

    // compares both vectors to merge
    while (left_idx < left_size && right_idx < right_size){
        if (left[left_idx] <= right[right_idx]){
            merged.push_back(left[left_idx]);
            left_idx ++;
        } else {
            merged.push_back(right[right_idx]);
            right_idx ++;
        }
    }

    // merged all of one vector
    while (left_idx == left_size && right_idx < right_size){
        merged.push_back(right[right_idx]);
        right_idx++;
    }
    while (right_idx == right_size && left_idx < left_size){
        merged.push_back(left[left_idx]);
        left_idx++;
    }
   return merged;
}


void timsort(vector<int>& data) {
    // Determine run length
    int size = data.size();
    // if vector size is huge, increases the size of the run
    int min_run = 32;
    if (size>32*100){
        min_run = 64;
    }

    vector<int> segment(min_run);
    vector<vector<int>> runs;

    // If run is short, insertion sort only
    if (size<min_run){
        reverse_check(data);
        insertionsort(data);
        return;
    }
    // Insertion sort on runs 
    for (int i=0; i<size; i+= min_run){
        int run_end = min (i + min_run, size);
        segment = slice_vector(data,i, run_end); 
        reverse_check(segment);
        insertionsort(segment);
        runs.push_back(segment);
    }
    // Merge Adjacent runs until there is only one left
    while (runs.size()>1){
        vector<vector<int>> updated_runs;
        int size = runs.size();
        for (int i=0; i<size; i +=2){
            if (i + 1 < size) {
                updated_runs.push_back(merge_runs(runs[i], runs[i+1]));
            } else {
                updated_runs.push_back(runs[i]);
            }
        } 
        runs = move(updated_runs);
    }
    data = move(runs[0]);
}


