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

// Selection sort implementation
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
    srand(static_cast<unsigned int>(time(0)));

    int size = 1000;
    double elapsedSeconds = 0.0;

    do {
        int* data = new int[size];

        // Fill array with random numbers (0–100)
        for (int i = 0; i < size; i++) {
            data[i] = rand() % 101;
        }

        // Display list only for small arrays
        if (size <= 1000) {
            cout << "\nFirst 20 elements BEFORE sort:\n";
            for (int i = 0; i < 20; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }

        // Time the sort
        clock_t start = clock();
        SelectionSort(data, size);
        clock_t end = clock();

        elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;

        // Display list only for small arrays
        if (size <= 1000) {
            cout << "First 20 elements AFTER sort:\n";
            for (int i = 0; i < 20; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }

        cout << "Array size: " << size
             << " | Sort time: " << elapsedSeconds << " seconds\n";

        delete[] data;
        size *= 10;

    } while (elapsedSeconds < 1.0);

    return EXIT_SUCCESS;
}