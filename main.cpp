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
                swap(arr[j], arr[j + 1]);
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
<typename T>void SelectionSort(vector <T>& arr, int numbersSize) {
    int i;
    int j;
    int indexSmallest;
    int temp;      // Temporary variable for swap
    for (i = 0; i < numbersSize - 1; ++i) {
        // Find index of smallest remaining element
        indexSmallest = i;
        for (j = i + 1; j < numbersSize; ++j) {
            if ( arr[j] < arr[indexSmallest] ) {
                indexSmallest = j;
            }
        }
        // Swap numbers[i] and numbers[indexSmallest]
        swap(arr[i],arr[indexSmallest]);
    }
}

//mergeSort from zybooks 15.9
template
<typename T>void Merge(vector<T>& v,vector<T>& t, int left, int middle,  int right){
    int temp = left;                                //setting up a temp value that is initialised to the leftmost value in the vector
    int tempL = left;                           //setting up a temp value that will be used as the left side of each vector we're working with
    int tempR = middle + 1;                         //setting up a temp value that will be used as the right side of each vector we're working with
    while(tempL <= middle && tempR <= right ){      //will correct one side of the vector first
        if(v.at(tempL) > v.at(tempR)){          //if the left value is greater then the right value do this
            t.at(temp) = v.at(tempR);           //setting the temporary vector with the correct number
            temp = temp + 1;                    //iterating the variables used
            tempR = tempR + 1;
        }
        else{
            t.at(temp) = v.at(tempL);       //setting the temporary vector with the correct number
            temp = temp + 1;            //iterating the variables used
            tempL = tempL + 1;
        }
    }
    while(tempR <= right){          //checking the right side
        t.at(temp) = v.at(tempR);       //setting the temporary vector with the correct number
        temp = temp + 1;            //iterating the variables used
        tempR = tempR + 1;
    }
    while(tempL <= middle){         //checking the left side
        t.at(temp) = v.at(tempL);       //setting the temporary vector with the correct number
        temp = temp + 1;            //iterating the variables used
        tempL = tempL + 1;
    }
    for(int i = left; i <= right; i++ ){        //resetting vector v with the correct values that had been stored in vector t
        v.at(i) = t.at(i);
    }
}

template
<typename T>void MergeSort(vector <T>& numbers,vector<T>& t,int left,int right) {  //calling mergeSort with the real vectors this time
    int center;             //setting up a center variable so that we can find the center of each vector were working in every time we call the function
    if(right <= left){      //checking to see if its in the correct order
        return;             //if its in the right order we can return because no further action is needed
    }
    else{
        center = (left + right)/2;                          //finding center of the vector
        MergeSort(numbers,t,left,center);                 //calls mergeSort recursively the first time to get the left side of the split
        MergeSort(numbers,t,center + 1,right);        //calls mergeSort recursively the second time to get the right side
        Merge(numbers,t,left,center,right);     //calls Merge to combine the vectors after they are broken down

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

    for(int i = 0; i < 149999; i++){             //for the length of the data set
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
    for(int i = 0; i < 149999; i++){
        int r;
        r = rand() % 10000;

        intV.emplace_back(r);
        intV_B.emplace_back(r);
        intV_S.emplace_back(r);
        intV_Q.emplace_back(r);
        intV_M.emplace_back(r);

    }

    clock_t start_dataBubbleSort1 = clock();
    bubbleSort(dataV_B,149999);
    clock_t end_dataBubbleSort1 = clock();
    clock_t start_dataBubbleSort2 = clock();
    bubbleSort(dataV_B,149999);
    clock_t end_dataBubbleSort2 = clock();

    clock_t start_intBubbleSort1 = clock();
    bubbleSort(intV_B,149999);
    clock_t end_intBubbleSort1 = clock();
    clock_t start_intBubbleSort2 = clock();
    bubbleSort(intV_B,149999);
    clock_t end_intBubbleSort2 = clock();

    clock_t start_dataMinSort1 = clock();
    MinSort(dataV_M,149999);
    clock_t end_dataMinSort1 = clock();
    clock_t start_dataMinSort2 = clock();
    MinSort(dataV_M,149999);
    clock_t end_dataMinSort2 = clock();

    clock_t start_intMinSort1 = clock();
    MinSort(intV_M,149999);
    clock_t end_intMinSort1 = clock();
    clock_t start_intMinSort2 = clock();
    MinSort(intV_M,149999);
    clock_t end_intMinSort2 = clock();

    clock_t start_dataSelectionSort1 = clock();
    SelectionSort(dataV_S,149999);
    clock_t end_dataSelectionSort1 = clock();
    clock_t start_dataSelectionSort2 = clock();
    SelectionSort(dataV_S,149999);
    clock_t end_dataSelectionSort2 = clock();

    clock_t start_intSelectionSort1 = clock();
    SelectionSort(intV_S,149999);
    clock_t end_intSelectionSort1 = clock();
    clock_t start_intSelectionSort2 = clock();
    SelectionSort(intV_S,149999);
    clock_t end_intSelectionSort2 = clock();

    vector<Data> t(149999);
    clock_t start_dataMergeSort1 = clock();
    MergeSort(dataV_Q,t, 0, 149998);
    clock_t end_dataMergeSort1 = clock();
    clock_t start_dataMergeSort2 = clock();
    MergeSort(dataV_Q,t, 0, 149998);
    clock_t end_dataMergeSort2 = clock();

    vector<int> a(149999);
    clock_t start_intMergeSort1 = clock();
    MergeSort(intV_Q,a, 0, 149998);
    clock_t end_intMergeSort1 = clock();
    clock_t start_intMergeSort2 = clock();
    MergeSort(intV_Q,a, 0, 149998);
    clock_t end_intMergeSort2 = clock();














    inputs.close ();
    return 0;
}