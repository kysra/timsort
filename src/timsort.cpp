#include "../include/timsort.h"
#include "../include/sorting.h"
#include <vector>

using namespace std;

vector<int> slice_vector(vector<int>& data, int start, int end){
    return vector<int>(data.begin()+start, data.begin()+end);
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
    /*
    if (left_idx == left_size && right_idx != right_size){
        //cout << "RAN OUT OF LEFT INDEX" << endl;
        for (int n = right_idx; n<right_size; n++){
            //cout << "ADDING " << right[n] << " FROM RIGHT INDEX " << endl;
            merged[left_idx + n] = right[n];
            //cout << "INDEX: " << left_idx + n << endl;
        }
      
    } else if (right_idx == right_size && left_idx != left_size){
        //cout << "RAN OUT OF RIGHT INDEX" << endl;
        for (int n = left_idx; n<left_size; n++){
            //cout << "ADDING " << left[n]<< " FROM LEFT INDEX " << endl;
            merged[n + right_idx] = left[n];
            //cout << "INDEX: " << n + right_idx << endl;
        }
    }
   
    
    */  
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
    /*
    while (index < num_runs){
        
        if (index<num_runs-2){
            segment_multi = slice_vector(data, min_run*index, min_run*(index+2));
            insertionsort(segment_multi);
            runs[index] = slice_vector(segment_multi, 0, min_run);
            runs[index+1] = slice_vector(segment_multi, min_run, min_run*2);
            cout << "RUN INDEX: " << index << endl; 
            print_vector(runs[index]);
            cout << "RUN INDEX: " << index + 1  << endl; 
            print_vector(runs[index+1]);
            index+=2;
        } else {
            segment = slice_vector(data, min_run*index, min_run*index + leftover_run);
            segment.resize(leftover_run);
            insertionsort(segment);
            runs[index] = segment;
            cout << "RUN INDEX: " << index << endl; 
            print_vector(runs[index]);
            index ++;
        }
    }*/


    for (int i=0; i<num_runs; i++){
        //cout << "i= " << i << endl;
        //cout << "Range: " << min_run*i << " - " << min_run * (i+1) << endl;
        if (i<num_runs-1){
            segment = slice_vector(data, min_run*i, min_run*(i+1));
            
        } else {
            segment = slice_vector(data, min_run*i, min_run*i + leftover_run);
            segment.resize(leftover_run);

        }
        insertionsort(segment);
            runs[i] = segment;
    }

        
        //cout << "SEGMENT: ";
        //for (int n=0; n<segment.size(); n++){
        //    cout << segment[n] << " ";
        //}
        //cout << endl;

        // Multiple insertions runs 
    //cout << endl << "RUNS SORTED: " << endl;
    //for (int n=0; n<num_runs; n++){
    //    prints_vector(runs[n]);
    //    cout << endl;
    //}

    // Merge Adjacent runs
    while (runs.size()>1){
        vector<vector<int>> updated_runs;
        /*
        vector<int> merged = runs[0];
        //cout << "MERGING RUNS" << endl;
        //print_vector(runs[0]);
        //print_vector(runs[1]);
        merged = merge_runs(runs[0], runs[1]);
        //cout << "MERGED VECTOR" << endl;
        //print_vector(merged);
        runs.push_back(merged);
        //runs.erase(runs.begin());
        //runs.erase(runs.begin());
        //cout << "Runs size: " << runs.size() << endl;*/
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
    //cout << "FINAL SORT: " << endl;
    //print_vector(data);

    //cout << "SORING TEST: " << endl;
    //for (int n=0; n<runs.size(); n++ ){
    //    cout << "N: " << endl;
    //    prints_vector(runs[n]);
    //}
    //cout << "Vector size: " << data.size() << endl;



        // Galloping runs 

    }


