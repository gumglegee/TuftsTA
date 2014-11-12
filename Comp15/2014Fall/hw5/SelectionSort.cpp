//
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm


#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

// reads in a list of integers from stdin and returns an arrayWithLength
void SelectionSort::readList(){
        int currentCapacity = 10;
        sortArray.arr = new int[currentCapacity];
        
        while (cin >> sortArray.arr[sortArray.length]) {
                ++sortArray.length;
                if (sortArray.length==currentCapacity) {
                        int *temp = new int[currentCapacity*2];
                        for (int i=0;i<currentCapacity;i++) {
                                temp[i] = sortArray.arr[i];
                        }
                        delete [] sortArray.arr;
                        sortArray.arr = temp;
                        currentCapacity *= 2;
                }
        }
}

void SelectionSort::sort(){
        // selection sort on sortArray

	for (int i = 1; i < sortArray.length; i++) {
		for (int j = i; j > 0; j--) {
			if (sortArray.arr[j-1] > sortArray.arr[j]) {
				int temp = sortArray.arr[j];
				sortArray.arr[j] = sortArray.arr[j-1];
				sortArray.arr[j-1] = temp;
			}
		}
	}
}

void SelectionSort::printArray(){
        // prints out the integers in sorted order
	for (int i = 0; i < sortArray.length; i++) {
		cout << sortArray.arr[i] << " ";
	}
	cout << "\n" << endl;
}


