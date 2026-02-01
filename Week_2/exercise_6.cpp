#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Swap two integers using pointers
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection sort (kept for reference, NOT used)
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

// Basic bubble sort (reference only)
void BubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Enhanced Bubble Sort (from previous step)
void EnhancedBubbleSort(int arr[], int size) {
    int lastSwapIndex;
    int n = size;

    do {
        lastSwapIndex = 0;

        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                Swap(&arr[i], &arr[i + 1]);
                lastSwapIndex = i + 1;
            }
        }

        n = lastSwapIndex;

    } while (lastSwapIndex != 0);
}

// Sequential (Linear) Search
// Returns index if found, -1 if not found
int SequentialSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int size = 100000;
    int* bigData = new int[size];

    // Fill array with random numbers (0–100)
    for (int i = 0; i < size; i++) {
        bigData[i] = rand() % 101;
    }

    // Choose a value to search for
    int target = rand() % 101;

    cout << "Searching for value: " << target << endl;

    // Time the sequential search
    clock_t start = clock();
    int index = SequentialSearch(bigData, size, target);
    clock_t end = clock();

    double elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;

    if (index != -1) {
        cout << "Value found at index: " << index << endl;
    } else {
        cout << "Value not found in array." << endl;
    }

    cout << "Sequential search time: "
         << elapsedSeconds << " seconds" << endl;

    delete[] bigData;
    return EXIT_SUCCESS;
}