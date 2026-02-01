#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Swap function - takes addresses of two integers and swaps their values
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// SelectionSort function - sorts an array using selection sort algorithm
void SelectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Swap(&arr[i], &arr[minIndex]);
        }
    }
}

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create dynamic array with 1000 random numbers between 0 and 100
    int bigSize = 1000;
    int* bigData = new int[bigSize];
    for (int i = 0; i < bigSize; i++) {
        bigData[i] = rand() % 101; // 0 to 100 inclusive
    }

    // Display first 20 elements of original bigData
    cout << "First 20 elements of original bigData: ";
    for (int i = 0; i < 20; i++) {
        cout << bigData[i] << " ";
    }
    cout << endl;

    // Sort bigData
    SelectionSort(bigData, bigSize);

    // Display first 20 elements of sorted bigData
    cout << "First 20 elements of sorted bigData: ";
    for (int i = 0; i < 20; i++) {
        cout << bigData[i] << " ";
    }
    cout << endl;

    // Clean up dynamic memory
    delete[] bigData;

    return EXIT_SUCCESS;
}