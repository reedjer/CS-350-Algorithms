//     Reed, Jeremy  CS 350  Assignment #1
// valgrind --track-origins=yes --tool=memcheck --leak-check=full ./a.out
//
// Given an array of (N) unique positive integers in ascending order, the array 
// may be shifted to the right (N) times. The central task is to find the minimum
// value and return it to standard output, along with its index in the 'shifted' array.
// An added feature is to build a mechanism that tests mutliple arrays consecutively.
// 
//
#include <iostream>
#include <array>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

//#define BOOST_VARIANT_LIMIT_TYPES 40  // (if needed) Setting macro value above 20 adds to compile time

//int source_vals[] = {8, 11, 12, 14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000};

int array_empty[] = {};
int array_one_element [] = {5};
int array_original [] = {8, 11, 12, 14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000, 5054};
int array_shift_1 [] = {5054, 8, 11, 12, 14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000};
int array_shift_2 [] = {5000, 5054, 8, 11, 12, 14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400};
int array_shift_3 [] = {2400, 5000, 5054, 8, 11, 12, 14, 44, 59, 105, 2009, 2010, 2300, 2305};
int array_shift_4 [] = {2305, 2400, 5000, 5054, 8, 11, 12, 14, 44, 59, 105, 2009, 2010, 2300};
int array_shift_5 [] = {2300, 2305, 2400, 5000, 5054, 8, 11, 12, 14, 44, 59, 105, 2009, 2010};
int array_shift_6 [] = {2010, 2300, 2305, 2400, 5000, 5054, 8, 11, 12, 14, 44, 59, 105, 2009};
int array_shift_7 [] = {2009, 2010, 2300, 2305, 2400, 5000, 5054, 8, 11, 12, 14, 44, 59, 105};
int array_shift_8 [] = {105, 2009, 2010, 2300, 2305, 2400, 5000, 5054, 8, 11, 12, 14, 44, 59};
int array_shift_9 [] = {59, 105, 2009, 2010, 2300, 2305, 2400, 5000, 5054, 8, 11, 12, 14, 44};
int array_shift_10 [] = {44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000, 5054, 8, 11, 12, 14};
int array_shift_11 [] = {14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000, 5054, 8, 11, 12};
int array_shift_12 [] = {12, 14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000, 5054, 8, 11};
int array_shift_13 [] = {11, 12, 14, 44, 59, 105, 2009, 2010, 2300, 2305, 2400, 5000, 5054, 8};

// Function Declarations for this program
int find_minimum(int *array, int arr_length);

int main()
{
    int min_val_index = 0;
    int len = 13; 
    int **arr_ptr = new int* [16];
    arr_ptr[0] = array_empty;
    arr_ptr[1] = array_one_element;
    arr_ptr[2] = array_original;
    arr_ptr[3] = array_shift_1;
    arr_ptr[4] = array_shift_2;
    arr_ptr[5] = array_shift_3;
    arr_ptr[6] = array_shift_4;
    arr_ptr[7] = array_shift_5;
    arr_ptr[8] = array_shift_6;
    arr_ptr[9] = array_shift_7;
    arr_ptr[10] = array_shift_8;
    arr_ptr[11] = array_shift_9;
    arr_ptr[12] = array_shift_10;
    arr_ptr[13] = array_shift_11;
    arr_ptr[14] = array_shift_12;
    arr_ptr[15] = array_shift_13;
    
    for(int i = 0; i <= 15; ++i) // total of 15 different arrays
    {
	if(i == 0)
	{
	    arr_ptr[i] = array_empty;         // sending empty array to prove algo handles empty arrays
	    if( (min_val_index = find_minimum(arr_ptr[i], 0) == -5002) ) {
		cout << "\nThe input array is empty.\n" << endl; }
	    continue;
	}
	else if(i == 1)
	{
	    arr_ptr[i] = array_one_element;  // sending to demonstrate algo handles single element array
	    if( (min_val_index = find_minimum(arr_ptr[i], 1) == -5003) ) {
		cout << "\nThe array has only one number at index 0.\n" << endl; }
	    continue;
	}
	else if(i >= 2) 
	{
	    min_val_index = find_minimum(arr_ptr[i], len);
	    if(min_val_index > -5001) {
                cout << "...We found the lowest value at index " << min_val_index << endl; }
	    continue;
	}
	else 
	{
	    cout << "  **  Input Error  **\n" << endl;
	}
    }
    delete [] arr_ptr;

    return 0;
}  

int find_minimum(int *array, int arr_length)
{
    int left = 0;                          // starting index for first element
    int right = arr_length;                // starting index for last element 
    int mid_pt = ceil((left + right) /2);  // set value for mid-point index of input array
    int min = array[mid_pt];               // set the min to whatever is at middle of array
    int min_indx = mid_pt;                 // and the initial index of minimum at start of parsing procedure
    int L_counter = mid_pt;                // Left moving counter starts "end" of Left Half of array
    int R_counter = arr_length;            // Right moving counter starts at "end" of Right Half of array

    if(arr_length == 0) {
        return -5002; } 
    if(arr_length == 1) {
	cout << "\nThe minimum value was found as " << array[0] << endl;
        return -5003; }
    else
    {
        //  *  Diagnostic Output  *  // 
        cout << "\n Left: " << endl;
        for(int i = left; i <= mid_pt; ++i)
        {
	    cout << array[i] << " -> " ;
        }
        cout << "\n Right: " << endl;
        for(int i = mid_pt + 1; i <= arr_length; ++i)
        {
	    cout << array[i] << " -> " ;
        }

	// Finding minimum for Left side of array
	while(L_counter > 0) 
	{
	    --L_counter;
	    if(array[L_counter] < min) {
	        min = array[L_counter]; 
	        min_indx = L_counter; }
	    else {                 // when a larger value is to the left, 
	        break; }           // instead of unneccessarily parsing remaining elements 
        }
    
	// Finding minimum for Right side of array that is also less than min from Left
	while(R_counter > mid_pt) 
	{
	    if(array[R_counter] < min) {     
	        min = array[R_counter]; 
	        min_indx = R_counter;
	        --R_counter; }
	    else {
	        --R_counter; }
        }
    }
    cout << "\nThe minimum value is found as " << min << endl;
    return min_indx;
}





