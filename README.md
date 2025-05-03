# timsort Comparison
This C++ program aims to implement timsort and compare it with other sorting algorithms. 

We will aim to compare Timsort with:
- Merge Sort
- Insertion Sort
- Radix Sort 
- Bubble Sort
- Quicksort
- Heapsort

When running the application, it will generate a number of different kinds of arrays, sort them with these sorting methods, and return the time required to finish sorting. This will allow the user to compare and contrast the strengths and weaknesses of the different types of sorting algorithms. 

## Project Description 
The goal of this project is to allow the user to explore the strengths and weaknesses of different sorting algorithms.

The main function will take input from the user regarding what type of array they would like to see sorted, and what sorting methods they would like to see used to sort that array. 

It will then sort the array with all of the chosen methods, and return the time taken for each sort to complete. In some instances, if the chosen array is too large, it will omit those arrays for time constraints. 

## Project Layout
### Main 
This contains the main function for running this application. It has some basic menu functions, and takes input to generate various arrays to be sorted and timed.
### Sorting
This contains all of the non timsort sorting functions
### Timsort 
This contains the functions needed to run timsort, however, it does use the insertion sort function from the previous section.


