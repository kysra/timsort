#include "../include/timsort.h"
#include "../include/sorting.h"
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

vector<int> generate_random_vector(int size, int max_range, int type) {
// Generates a vector containing an array of a random integers
// int size - size of the vector 
// int range - max value of array
// int type - type of array to be generated 
//      1 - fully randomized array
//      2 - partially sorted array
//      3 - fully sorted array
//      4 - reversed array
//      5 - many duplicates in array
    vector<int> data(size);
    if (type == 1 ){
    // fully randomized array
        for (int i = 0; i < size; ++i) {
            data[i] = rand() % max_range; 
        }
        return data;

    } else if (type == 2){
    // partially sorted array
        vector<int> data_01(size/3);
        for (int i = 0; i < size/3; ++i) {
            data_01[i] = rand() % max_range; 
        }
        radix_sort(data_01);    // using radix sort as the default sorting function for speed
        vector<int> data_02(size/3);
        for (int i = 0; i < size/3; ++i) {
            data_02[i] = rand() % max_range;
        }
        int size_03 = size - data_01.size() - data_02.size();
        vector<int> data_03(size_03);
        for (int i = 0; i < size_03; ++i) {
            data_03[i] = rand() % max_range; 
        }
        radix_sort(data_03);
        data = data_01;
        data.insert(data.end(), data_02.begin(), data_02.end());
        data.insert(data.end(), data_03.begin(), data_03.end());
        return data;

    } else if (type == 3){
    // fully sorted array 
        for (int i = 0; i < size; i++) {
            data[i] = rand() % max_range; 
        }
        radix_sort(data);
        return data;

    } else if (type == 4){
    // reversed array 
        for (int i = 0; i < size; i++) {
            data[i] = rand() % max_range; 
        }
        radix_sort(data);
        reverse(data.begin(), data.end());
        return data;

    } else if (type == 5){
    // high numbers of duplicates
        for (int i = 0; i < size; i++) {
            data[i] = rand() % max_range; 
        }
        int num = rand() % size;
        // ensures that at least a quarter of the values are 
        // the duplciate value
        while (num < size*.25){
            num *= 2;
        }
        int dupe = rand() % max_range;
        for (int i = 0; i <num; i++){
            data[rand() % size] = dupe;
        }
        return data;

    } else {
        // error catching
        cout << "ERROR: Invalid Input. Try again. " << endl;
        return data;
    }
    
}

auto measure_function_time(void (*func)(vector<int>&), vector<int>& data) {
    // function measures the time it takes to run another function, and then returns the time in ms
    // void (*func)(vector<int>&) - function to time 
    // vector<int>& data - data to be sorted 
    auto start = high_resolution_clock::now();
    func(data);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

auto quicksort_time(vector<int>& data) {
    // function that measures the time it takes to run quicksort, since it takes different arguments 
    // vector<int>& data - data to be sorted 
    auto start = high_resolution_clock::now();
    quicksort(data, 0, data.size()-1);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

void run_sorts(vector<int>& data){
    // function that runs all of the sorting algorithms and outputs the sorting time
    // vector<int>& data - data to be sorted
    int size = data.size();
    vector<int> test = data;
    // if sorting array is larger than or equal to 10k, the bubble sort will not fire due to 
    // length of time taken to run the function
    if (size >= 10000){
        cout << "BUBBLE SORT TIME: "<< endl;
        cout << "   (Omitting bubble sort for array sizes 10,000 or over. It may take too long)" << endl;
    } else {
        test = data;
        cout << "BUBBLE SORT TIME: "<< endl;
        cout << "    " << measure_function_time(bubblesort, test) << " ms" << endl;
    }

    test = data;
    cout << "MERGE SORT TIME: "<< endl;
    cout << "    " << measure_function_time(mergesort, test) << " ms" << endl;

    test = data;
    cout << "RADIX SORT TIME: "<< endl;
    cout << "    " << measure_function_time(radix_sort, test) << " ms" << endl;

    // if sorting array is larger than or equal to 100k, the quick sort will not fire due to 
    // length of time taken to run the function
    if (size >= 100000){
        cout << "QUICKSORT TIME:" << endl;
        cout << "   (Omitting quick sort for array sizes 100,000 or over. It may take too long)" << endl;
    } else {
        test = data;
        cout << "QUICKSORT TIME:" << endl;
        cout << "    " << quicksort_time(test) << " ms" << endl;
    }
    test = data;
    cout << "HEAPSORT TIME: "<< endl;
    cout << "    " << measure_function_time(heapsort, test) << " ms" << endl;

    // if sorting array is larger than or equal to 10k, the insertion sort will not fire due to 
    // length of time taken to run the function
    if (size >= 10000){
        cout << "INSERTION SORT TIME:" << endl;
        cout << "   (Omitting insertion sort for array sizes 10,000 or over. It may take too long)" << endl;
    } else {
        test = data;
        cout << "INSERTION SORT TIME:" << endl;
        cout << "    " << measure_function_time(insertionsort, test) << " ms" << endl;
    }
   
    test = data;
    cout << "TIMSORT SORT TIME: "<< endl;
    cout << "    " << measure_function_time(timsort, test) << " ms" << endl;
}

int main(){
    cout << endl << endl << endl
    << "----------------======---------------" << endl
    << "       CSPB 2270 Data Structures     " << endl
    << "----------------======----------------" << endl
    << "This application will generate a variety of randomized data arrays " << endl
    << "and allow you to run timed tests with various sorting algorithms. " << endl << endl;

    vector<int> data;
    string input_val;
    string input_array_type;
    // Array type menu
    while (input_val != "q" || input_val != "Q"){
        cout << "   Enter q to exit" << endl << endl
        << " What sort of array would you like to test?" << endl
        << "1 - Fully randomized" << endl
        << "2 - Partially sorted" << endl
        << "3 - Fully sorted" << endl
        << "4 - Reversed sorted" << endl
        << "5 - High duplication incidence" << endl << endl
        << "Please enter an integer 1-5" << endl;
        // takes input on what type of array to make
        cin >> input_array_type;

        if (cin.fail()){
            // checks for invalid entry and clears errors if invalid 
            cin.clear();
            cout << "ERROR: Invalid input, please try again" << endl << endl;
            break;
        } else if (input_array_type == "q" || input_array_type == "Q"){
            cout << "Quitting... " << endl;
            input_val = "q";
            break;
        } else {
            try {
                int input_array_int;
                // checks that value in an integer in the valid range
                input_array_int = stoi(input_array_type);
                if (input_array_int<1 || input_array_int>5){
                    cout << "ERROR: Invalid input" << endl;
                } else {
                    string size_string;
                    string max_string;
                    int size = -1;
                    int max = -1;
                    // takes input for the size and maximum value in sorting array
                    while (size == -1 && max == -1){
                        cout << "Enter size of array:" << endl;
                        cin >> size_string;
                        if (cin.fail()){
                            // checks for invalid entry and clears errors if invalid 
                            cin.clear();
                            cout << "ERROR: Invalid input, please try again" << endl << endl;
                            break;
                        } else if (input_array_type == "q" || input_array_type == "Q"){
                            cout << "Quitting... " << endl;
                            input_val = "q";
                            break;
                        } else {
                            // checks that entered figure is an integer
                            try {
                                size = stoi(size_string);
                            } catch(exception& ex){
                                cout << endl <<  "ERROR: Invalid input, please try again" << endl << endl;
                                break;
                            }
                            cout << "Enter max value of array:" << endl;
                            cin >> max_string;
                            if (cin.fail()){
                                // checks for invalid entry and clears errors if invalid 
                                cin.clear();
                                cout << "ERROR: Invalid input, please try again" << endl << endl;
                                break;
                            } else if (input_array_type == "q" || input_array_type == "Q"){
                                cout << "Quitting... " << endl;
                                input_val = "q";
                                break;
                            } else {
                                try {
                                    size = stoi(size_string);
                                    max = stoi(max_string);
                                } catch (exception& ex){
                                    cout << endl <<  "ERROR: Invalid input, please try again" << endl << endl;
                                    break;
                                }
                            }
                            // generates the random array based on input data    
                            data = generate_random_vector(size, max, input_array_int);
                            cout << "Print generated array? Y/N? " << endl;
                            // takes input for if the user would like to print out the array
                            string print_output;
                            cin >> print_output;
                            if (cin.fail()){
                                // checks for invalid entry and clears errors if invalid 
                                cin.clear();
                                cout << "ERROR: Invalid input, please try again" << endl << endl;
                                break;
                            } else if (input_array_type == "q" || input_array_type == "Q"){
                                cout << "Quitting... " << endl;
                                input_val = "q";
                                break;
                            } else {
                                if (print_output == "y" || print_output == "Y"){
                                    switch (input_array_int) {
                                        case 1:
                                            cout << endl << "Fully Randomized Sequence: " << endl;
                                            break;
                                        case 2:
                                            cout << endl << "Paritally Sorted Sequence: " << endl;
                                            break;
                                        case 3:
                                            cout << endl << "Fully Sorted Sequence: " << endl;
                                            break;
                                        case 4:
                                            cout << endl << "Reverse Sorted Sequence: " << endl;
                                            break; 
                                        case 5:
                                            cout << endl << "High Duplication Sequence: " << endl;
                                            break;
                                    }
                                    print_vector(data);
                                    cout << endl;
                                } else if (print_output == "q" || print_output == "Q") {
                                    input_val = "q";
                                    break;
                                }
                            }
                        }
                        cout << endl 
                        << "-------------------------" << endl
                        << "   RUNNING SORT TESTS:" << endl 
                        << "-------------------------" << endl;
                        run_sorts(data);
                    }
                }
            } catch (exception& ex){
                cout << endl << "ERROR: Invalid input, please try again" << endl << endl;
            }

        }
        // takes input for if the user would like to run application again w/ new array
        string repeat;
        cout << endl << "Generate another array? Y/N?" << endl;
        cin >> repeat;
        if (cin.fail()){
            // checks for invalid entry and clears errors if invalid 
            cin.clear();
            cout << "ERROR: Invalid input, please try again" << endl << endl;
            break;
        } else if (input_array_type == "q" || input_array_type == "Q"){
            cout << "Quitting... " << endl;
            input_val = "q";
            break;
        } else {
            if (repeat != "y" && repeat != "Y"){
                cout << "Quitting... " << endl;
                input_val = "q";
                break;
            } else {
                cout << endl << endl;
            }
        }

    }

    return 0;
}

