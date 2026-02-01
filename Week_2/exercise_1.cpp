#include <iostream>
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
        // Find the minimum element in unsorted array
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the first element
        if (minIndex != i) {
            Swap(&arr[i], &arr[minIndex]);
        }
    }
}

int main() {
    // Create array with specified values
    int data[] = {4, 5, 6, 1, 3, 9, 4, 8, 2, 7};
    int size = sizeof(data) / sizeof(data[0]);
    
    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
    
    // Sort the array
    SelectionSort(data, size);
    
    // Display sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
    
    return EXIT_SUCCESS;
}