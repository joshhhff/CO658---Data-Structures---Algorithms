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

// Enhanced Bubble Sort (used to prepare data for binary search)
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

// Binary Search (iterative)
// Returns index if found, -1 if not found
int BinarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
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

    // Time the binary search ONLY
    clock_t start = clock();
    
    // Sort array BEFORE binary search
    EnhancedBubbleSort(bigData, size);

    int index = BinarySearch(bigData, size, target);
    clock_t end = clock();

    double elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;

    if (index != -1) {
        cout << "Value found at index: " << index << endl;
    } else {
        cout << "Value not found in array." << endl;
    }

    cout << "Binary search time: "
         << elapsedSeconds << " seconds" << endl;

    delete[] bigData;
    return EXIT_SUCCESS;
}