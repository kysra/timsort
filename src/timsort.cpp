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
    int num = 0;
    int temp;
    for (int n=0; n<size; n++){
        if (data[size-1-n]<data[n]){
            temp = data[size-1-n];
            data[size-1-n] = data[n];
            data[n] = temp;
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
    //print_vector(left);
    //print_vector(right);
    //cout << "Left size: " << left_size << endl;
    //cout << "Right size: " << right_size << endl;

    if (left.front() > right.back()){
        // add all of left onto right
        merged = right;
        //cout << "GALLOPING" << endl;
        merged.insert(merged.end(), left.begin(), left.end());
        return merged;
    } else if (right.front() > left.back()){
        // add all of right onto left 
        merged = left;
        //cout << "GALLOPING" << endl;
        merged.insert(merged.end(), right.begin(), right.end());
        return merged;
    }

    while (left_idx < left_size && right_idx < right_size){
        if (left[left_idx] <= right[right_idx]){
            merged.push_back(left[left_idx]);
            //cout << "Adding " << left[left_idx] << " from left from index: " << left_idx << endl;
            //cout << "INDEX: " << left_idx + right_idx << endl;
            left_idx ++;
        } else {
            merged.push_back(right[right_idx]);
            //cout << "Adding " << right[right_idx] << " from right from index: " << right_idx << endl;
            //cout << "INDEX: " << left_idx + right_idx << endl;
            right_idx ++;
        }
    }
    //cout << "RAN OUT OF INDEX" << endl;
    //cout << "INDEXES: " << left_idx << " " << right_idx << endl;
    //cout << "SIZES: " << left_size << " " << right_size << endl;

    while (left_idx == left_size && right_idx < right_size){
        //cout << "RAN OUT OF LEFT INDEX" << endl;
        merged.push_back(right[right_idx]);
        right_idx++;
    }
    while (right_idx == right_size && left_idx < left_size){
        //cout << "RAN OUT OF RIGHT INDEX" << endl;
        merged.push_back(left[left_idx]);
        left_idx++;
    }
   //cout << "Merged size: " << merged.size() << endl;
   //print_vector (merged);
   return merged;
}


void timsort(vector<int>& data) {
    // Determine run length
    int size = data.size();
    // TO DO - add feature to vary run-size to size of vector
    int min_run = 32;
    if (size>32*50){
        min_run = 64;
    }

    int num_runs = size/min_run + 1;
    int leftover_run = size%min_run;
    //int index = 0;
    vector<int> segment(min_run);
    vector<vector<int>> runs (num_runs);
    //cout << "Size of vector: " << size << endl;;
    //cout << "Number of runs: " << num_runs << endl;;

    // If run is short, insertion sort only
    if (size<min_run){
        insertionsort(data);
        return;
    }
    // Determine reverse runs 

    // Insertion sort on runs 
    for (int i=0; i<num_runs; i++){
        //cout << "i= " << i << endl;
        //cout << "Range: " << min_run*i << " - " << min_run * (i+1) << endl;
        if (i<num_runs-1){
            segment = slice_vector(data, min_run*i, min_run*(i+1));
            
        } else {
            segment = slice_vector(data, min_run*i, min_run*i + leftover_run);
            segment.resize(leftover_run);

        }
        reverse_check(segment);
        insertionsort(segment);
            runs[i] = segment;
    }

    // Merge Adjacent runs
    while (runs.size()>1){
        vector<vector<int>> updated_runs;
        int size = runs.size();
        for (int i=0; i<size; i +=2){
            //cout << "LOOPING... " << endl;
            if (i + 1 < runs.size()) {
                //print_vector(runs[i]);
                //print_vector(runs[i+1]);
                updated_runs.push_back(merge_runs(runs[i], runs[i+1]));
            } else {
                updated_runs.push_back(runs[i]);
            }
        } 
        runs = move(updated_runs);
    }

    data = move(runs[0]);

    }


