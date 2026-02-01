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

// Bubble sort implementation
void BubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                Swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // Optimization: stop early if already sorted
        if (!swapped) {
            break;
        }
    }
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

        // Show data only for small arrays
        if (size <= 1000) {
            cout << "\nFirst 20 elements BEFORE sort:\n";
            for (int i = 0; i < 20; i++) {
                cout << bigData[i] << " ";
            }
            cout << endl;
        }

        clock_t start = clock();

        // SelectionSort(bigData, size);  // ← commented out as requested
        BubbleSort(bigData, size);        // ← bubble sort used instead

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
             << " | Bubble sort time: " << elapsedSeconds << " seconds\n";

        delete[] bigData;
        size *= 10;

    } while (elapsedSeconds < 1.0);

    return EXIT_SUCCESS;
}