#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <random>
#include <time.h>

#include "Data.h"


//Bubble Sort from slides
template<typename T>
void bubbleSort(vector<T> &arr, int size) {
    int i, j;
    bool swapped;
    for (i = 0; i < size - 1; i++) {
        swapped = false;
        // Last i elements are already in place
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
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

//Quick Sort from ZyBooks
template<typename T>
int Partition(vector<T> &numbers, int i, int k) {
    int l;
    int h;
    int midpoint;
    T pivot;
    T temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers.at(midpoint);

    done = false;
    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (numbers.at(l) < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers.at(h)) {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        } else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers.at(l);
            numbers.at(l) = numbers.at(h);
            numbers.at(h) = temp;

            ++l;
            --h;
        }
    }

    return h;
}

template<typename T>
void Quicksort(vector<T> &numbers, int i, int k) {
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    Quicksort(numbers, i, j);
    Quicksort(numbers, j + 1, k);
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
    int N = 100000;  //sets the length of the vectors you want to sort
    int M = N-1;    //used for certain sorting algorithms that need the last position in the vector

   // for(int i = 0; i < 100; i++) {     //optional for loop to run the program many times

        vector<Data> dataV;     //creating vectors of Data

        vector<Data> dataV_B;
        vector<Data> dataV_S;
        vector<Data> dataV_Q;
        vector<Data> dataV_M;

        vector<int> intV;    //creating vectors of int

        vector<int> intV_B;
        vector<int> intV_S;
        vector<int> intV_Q;
        vector<int> intV_M;

        ifstream inputs;

        inputs.open("Air Data -cleaned 2 - Copy - Copy.csv");   //opening csv file


        if (!inputs.is_open()) {                     //checking to see if all files were opened correctly
            cout << "inputs isn't open" << endl;
            return -1;
        }

        string loc;       //creating strings for all of my inputs
        string pres;
        string temper;
        string humid;

        cout << "Reading ../dataset.csv…" << endl;

        for (int i = 0; i < N; ++i) {             //for the length of the data set
            //while(!inputs.eof()){
            getline(inputs, loc, ',');           //getting the inputs from the data set and storing them in the strings
            getline(inputs, pres, ',');
            getline(inputs, temper, ',');
            getline(inputs, humid);

            Data object(stoi(loc), stod(pres), stod(temper), stod(humid));   //creating a Data object by converting strings to double and storing them in the object

            dataV.emplace_back(object);     //placing the Data objects into the vectors
            dataV_B.emplace_back(object);
            dataV_S.emplace_back(object);
            dataV_Q.emplace_back(object);
            dataV_M.emplace_back(object);
        }

        cout << "done reading" << endl;

        srand(time(0));      //getting random numbers
        for (int i = 0; i < N; i++) {     //for the length of the array
            int r;
            r = rand() % N;      //making the random ints

            intV.emplace_back(r);     //placing the random ints in the vectors
            intV_B.emplace_back(r);
            intV_S.emplace_back(r);
            intV_Q.emplace_back(r);
            intV_M.emplace_back(r);

        }

        //following code starts a timer, runs the sorting algorithm, and ends the timer for all of the sorting algorithms twice

        clock_t start_dataBubbleSort1 = clock();
        bubbleSort(dataV_B, N);
        clock_t end_dataBubbleSort1 = clock();
        clock_t start_dataBubbleSort2 = clock();
        bubbleSort(dataV_B, N);
        clock_t end_dataBubbleSort2 = clock();

        clock_t start_intBubbleSort1 = clock();
        bubbleSort(intV_B, N);
        clock_t end_intBubbleSort1 = clock();
        clock_t start_intBubbleSort2 = clock();
        bubbleSort(intV_B, N);
        clock_t end_intBubbleSort2 = clock();

        clock_t start_dataQuickSort1 = clock();
        Quicksort(dataV_Q, 0, N-1);
        clock_t end_dataQuickSort1 = clock();
        clock_t start_dataQuickSort2 = clock();
        Quicksort(dataV_Q, 0, N-1);
        clock_t end_dataQuickSort2 = clock();

        clock_t start_intQuickSort1 = clock();
        Quicksort(intV_Q, 0, N-1);
        clock_t end_intQuickSort1 = clock();
        clock_t start_intQuickSort2 = clock();
        Quicksort(intV_Q, 0, N-1);
        clock_t end_intQuickSort2 = clock();

        clock_t start_dataSelectionSort1 = clock();
        SelectionSort(dataV_S, N);
        clock_t end_dataSelectionSort1 = clock();
        clock_t start_dataSelectionSort2 = clock();
        SelectionSort(dataV_S, N);
        clock_t end_dataSelectionSort2 = clock();

        clock_t start_intSelectionSort1 = clock();
        SelectionSort(intV_S, N);
        clock_t end_intSelectionSort1 = clock();
        clock_t start_intSelectionSort2 = clock();
        SelectionSort(intV_S, N);
        clock_t end_intSelectionSort2 = clock();

        vector<Data> t(N);
        clock_t start_dataMergeSort1 = clock();
        MergeSort(dataV_M, t, 0, M);
        clock_t end_dataMergeSort1 = clock();
        clock_t start_dataMergeSort2 = clock();
        MergeSort(dataV_M, t, 0, M);
        clock_t end_dataMergeSort2 = clock();

        vector<int> a(N);
        clock_t start_intMergeSort1 = clock();
        MergeSort(intV_M, a, 0, M);
        clock_t end_intMergeSort1 = clock();
        clock_t start_intMergeSort2 = clock();
        MergeSort(intV_M, a, 0, M);
        clock_t end_intMergeSort2 = clock();

        //calculating the time it took each sorting algorithm to run in seconds

        double elapsed_dataBubbleSort1 = double(end_dataBubbleSort1 - start_dataBubbleSort1) / CLOCKS_PER_SEC;
        double elapsed_dataBubbleSort2 = double(end_dataBubbleSort2 - start_dataBubbleSort2) / CLOCKS_PER_SEC;

        double elapsed_intBubbleSort1 = double(end_intBubbleSort1 - start_intBubbleSort1) / CLOCKS_PER_SEC;
        double elapsed_intBubbleSort2 = double(end_intBubbleSort2 - start_intBubbleSort2) / CLOCKS_PER_SEC;

        double elapsed_dataQuickSort1 = double(end_dataQuickSort1 - start_dataQuickSort1) / CLOCKS_PER_SEC;
        double elapsed_dataQuickSort2 = double(end_dataQuickSort2 - start_dataQuickSort2) / CLOCKS_PER_SEC;

        double elapsed_intQuickSort1 = double(end_intQuickSort1 - start_intQuickSort1) / CLOCKS_PER_SEC;
        double elapsed_intQuickSort2 = double(end_intQuickSort2 - start_intQuickSort2) / CLOCKS_PER_SEC;

        double elapsed_dataSelectionSort1 = double(end_dataSelectionSort1 - start_dataSelectionSort1) / CLOCKS_PER_SEC;
        double elapsed_dataSelectionSort2 = double(end_dataSelectionSort2 - start_dataSelectionSort2) / CLOCKS_PER_SEC;

        double elapsed_intSelectionSort1 = double(end_intSelectionSort1 - start_intSelectionSort1) / CLOCKS_PER_SEC;
        double elapsed_intSelectionSort2 = double(end_intSelectionSort2 - start_intSelectionSort2) / CLOCKS_PER_SEC;

        double elapsed_dataMergeSort1 = double(end_dataMergeSort1 - start_dataMergeSort1) / CLOCKS_PER_SEC;
        double elapsed_dataMergeSort2 = double(end_dataMergeSort2 - start_dataMergeSort2) / CLOCKS_PER_SEC;

        double elapsed_intMergeSort1 = double(end_intMergeSort1 - start_intMergeSort1) / CLOCKS_PER_SEC;
        double elapsed_intMergeSort2 = double(end_intMergeSort2 - start_intMergeSort2) / CLOCKS_PER_SEC;

        //printing out off of the data
        cout << elapsed_dataBubbleSort1 << " " << elapsed_dataBubbleSort2 << " " << elapsed_intBubbleSort1 << " "
             << elapsed_intBubbleSort2 << " "
             << elapsed_dataQuickSort1 << " " << elapsed_dataQuickSort2 << " " << elapsed_intQuickSort1 << " "
             << elapsed_intQuickSort2 << " "
             << elapsed_dataSelectionSort1 << " " << elapsed_dataSelectionSort2 << " " << elapsed_intSelectionSort1
             << " " << elapsed_intSelectionSort2 << " "
             << elapsed_dataMergeSort1 << " " << elapsed_dataMergeSort2 << " " << elapsed_intMergeSort1 << " "
             << elapsed_intMergeSort2 << endl;


        inputs.close();   //closing the inputs file

        //N = N+1000;    iterates N in the for loop
    //}
    return 0;
}