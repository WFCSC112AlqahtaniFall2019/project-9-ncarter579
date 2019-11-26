#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <random>
#include <time.h>

#include "Data.h"

//bubblesort from slides from class 22
template
<typename T> void bubbleSort(vector <T>& arr, int size){
    int i, j;
    bool swapped;
    for (i = 0; i < size-1; i++){
        swapped=false;
        for (j = 0; j < size-i-1; j++){
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
            //if there wasn't any swap in the inner loop, stop
            if(!swapped) {
                break;
            }
        }
    }
}

//minSort from slides from class 22
template
<typename T>void MinSort(vector <T>& arr, int size) {
    int min;
    for (int i = 0; i < size - 1; ++i){
        // Find index of smallest remaining element
        min = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i],arr[min]);
    }
}


//selection sort from zybooks 15.6
template
<typename T>void SelectionSort(int numbers[], int numbersSize) {
    int i;
    int j;
    int indexSmallest;
    int temp;      // Temporary variable for swap
    for (i = 0; i < numbersSize - 1; ++i) {
        // Find index of smallest remaining element
        indexSmallest = i;
        for (j = i + 1; j < numbersSize; ++j) {
            if ( numbers[j] < numbers[indexSmallest] ) {
                indexSmallest = j;
            }
        }
        // Swap numbers[i] and numbers[indexSmallest]
        temp = numbers[i];
        numbers[i] = numbers[indexSmallest];
        numbers[indexSmallest] = temp;
    }
}

//mergeSort from zybooks 15.9
template
<typename T>void Merge(T numbers[], int i, int j, int k) {
    int mergedSize;                            // Size of merged partition
    int mergePos;                              // Position to insert merged number
    int leftPos;                               // Position of elements in left partition
    int rightPos;                              // Position of elements in right partition
    int* mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                               // Initialize left partition position
    rightPos = j + 1;                          // Initialize right partition position
    mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
    // for merged numbers

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (numbers[leftPos] < numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;

        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
    delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}






int main() {
    vector<Data> dataV;

    vector<Data> dataV_B;
    vector<Data> dataV_S;
    vector<Data> dataV_Q;
    vector<Data> dataV_M;

    vector<int> intV;

    vector<int> intV_B;
    vector<int> intV_S;
    vector<int> intV_Q;
    vector<int> intV_M;

    ifstream inputs;

    inputs.open ("Air Data cleaned.csv");


    if (!inputs.is_open()){                     //checking to see if all files were opened correctly
        cout << "inputs isn't open" << endl;
        return -1;
    }

    string loc;       //creating strings for all of my inputs
    string pres;
    string temper;
    string humid;

    cout << "Reading ../dataset.csv…" << endl;

    for(int i = 0; i < 100500; i++){             //for the length of the data set
        //while(!inputs.eof()){
        getline(inputs, loc, ',');           //getting the inputs from the data set and storing them in the strings
        getline(inputs, pres, ',');
        getline(inputs, temper, ',');
        getline(inputs, humid);

        Data object (stoi(loc), stod(pres), stod(temper), stod(humid));   //creating a Data object by converting strings to double and storing them in the object

        dataV.emplace_back(object);
        dataV_B.emplace_back(object);
        dataV_S.emplace_back(object);
        dataV_Q.emplace_back(object);
        dataV_M.emplace_back(object);
    }

    srand(time(0));
    for(int i = 0; i < 100500; i++){
        int r;
        r = rand() % 10000;

        intV.emplace_back(r);
        intV_B.emplace_back(r);
        intV_S.emplace_back(r);
        intV_Q.emplace_back(r);
        intV_M.emplace_back(r);

    }






    inputs.close ();
    return 0;
}