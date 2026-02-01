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

// Selection sort (reference only)
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

// Enhanced bubble sort
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

        // Elements after last swap are already sorted
        n = lastSwapIndex;

    } while (lastSwapIndex != 0);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int size = 1000;
    double elapsedSeconds = 0.0;

    do {
        int* bigData = new int[size];

        // Fill array with random numbers (0–100)
        for (int i = 0; i < size; i++) {
            bigData[i] = rand() % 101;
        }

        if (size <= 1000) {
            cout << "\nFirst 20 elements BEFORE sort:\n";
            for (int i = 0; i < 20; i++) {
                cout << bigData[i] << " ";
            }
            cout << endl;
        }

        clock_t start = clock();

        // BubbleSort(bigData, size);          // ← commented out
        EnhancedBubbleSort(bigData, size);    // ← enhanced version used

        clock_t end = clock();
        elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;

        if (size <= 1000) {
            cout << "First 20 elements AFTER sort:\n";
            for (int i = 0; i < 20; i++) {
                cout << bigData[i] << " ";
            }
            cout << endl;
        }

        cout << "Array size: " << size
             << " | Enhanced Bubble Sort time: "
             << elapsedSeconds << " seconds\n";

        delete[] bigData;
        size *= 10;

    } while (elapsedSeconds < 1.0);

    return EXIT_SUCCESS;
}