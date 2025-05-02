#include "../include/timsort.h"
#include "../include/sorting.h"
#include <chrono>
#include <iostream>
#include <string>
#include <random>

using namespace std;
using namespace std::chrono;

vector<int> generate_random_vector(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 1000000; // Random numbers between 0 and 999
    }
    return data;
}


auto measure_function_time(void (*func)(vector<int>&), vector<int>& data) {
    auto start = high_resolution_clock::now();
    func(data);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

auto quicksort_time(vector<int>& data) {
    auto start = high_resolution_clock::now();
    quicksort(data, 0, data.size()-1);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main(){
    // Generate a random vector of size 100
    int size = 1000;
    vector<int> data;
    data = generate_random_vector(size);
    //cout << "UNSORTED DATA: " << endl;  
    //print_vector(data);
    radix_sort(data);
    vector<int> test;
    vector<int> data_02;
    
    data_02 = data;
    test.reserve(data.size()*2);
    test = data;
    
    test.insert(test.end(), data_02.begin(), data_02.end());
    test.insert(test.end(), data_02.begin(), data_02.end());
    data = test;

    //cout << "UNSORTED: " << endl;
    //print_vector(test);
    

    /* 
    //
    cout << "BUBBLESORT TIME: " << endl;
    cout << "    " << measure_function_time(bubblesort, test) << " ms" << endl;
    //cout << "SORTED: " << endl;
    //print_vector(test);
    */

    test = data;
    //cout << "UNSORTED: " << endl;
    // print_vector(test);
    cout << "MERGESORT TIME: "<< endl;
    cout << "    " << measure_function_time(mergesort, test) << " ms" << endl;
    //cout << "SORTED: " << endl;
    //print_vector(test);

    test = data;
    // cout << "UNSORTED: " << endl;
    //print_vector(test);
    cout << "RADIX SORT TIME: "<< endl;
    cout << "    " << measure_function_time(radix_sort, test) << " ms" << endl;
    //cout << "SORTED: " << endl;
    //print_vector(test);

    test = data;
    //cout << "UNSORTED: " << endl;
    //print_vector(test);
    cout << "QUICKSORT TIME: "<< endl;
    cout << "    " << quicksort_time(test) << " ms" << endl;
    //cout << "SORTED: " << endl;
    //print_vector(test);

    test = data;
    //cout << "UNSORTED: " << endl;
    //print_vector(test);
    cout << "HEAPSORT TIME: "<< endl;
    cout << "    " << measure_function_time(heapsort, test) << " ms" << endl;
    //cout << "SORTED: " << endl;
    //print_vector(test);

    test = data;
    //cout << "UNSORTED: " << endl;
    //print_vector(test);
    cout << "INSERTION SORT TIME: "<< endl;
    cout << "    " << measure_function_time(insertionsort, test) << " ms" << endl;
    //cout << "SORTED: " << endl;
    //print_vector(test);
   
    test = data;
    //test=data;
    cout << "TIMSORT SORT TIME: "<< endl;
    cout << "    " << measure_function_time(timsort, test) << " ms" << endl;
    //print_vector(test);
    return 0;
}

