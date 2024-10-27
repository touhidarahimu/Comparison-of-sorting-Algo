#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[index]) {
                index = j;
            }
        }
        swap(arr[i], arr[index]);
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort
int quick(int arr[], int low, int high) {
    int sort = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < sort) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = quick(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to generate random array
void randomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

// Function to measure execution time of sorting algorithms
void executionTime(void (*sortFunction)(int[], int), int arr[], int n, const string &algorithmName) {
    int* tempArr = new int[n];
    copy(arr, arr + n, tempArr);

    clock_t start = clock();
    sortFunction(tempArr, n);
    clock_t end = clock();

    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    cout << algorithmName << " Time " << timeTaken << " seconds." << endl;

    delete[] tempArr;
}

// Overloaded function for Merge Sort and Quick Sort, requiring additional parameters
void executionTime(void (*sortFunction)(int[], int, int), int arr[], int n, const string &algorithmName) {
    int* tempArr = new int[n];
    copy(arr, arr + n, tempArr);

    clock_t start = clock();
    sortFunction(tempArr, 0, n - 1);
    clock_t end = clock();

    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    cout << algorithmName << "  Time  " << timeTaken << " seconds." << endl;

    delete[] tempArr;
}

int main() {
    srand(time(0));  // Seed for random number generation

    const int sizes[] = {100, 2000, 40000, 100000};
    for (int size : sizes) {
        cout << "\nDataset Size: " << size << endl;
        int* dataset = new int[size];
        randomArray(dataset, size);

        executionTime(bubbleSort, dataset, size, "Bubble Sort");
        executionTime(selectionSort, dataset, size, "Selection Sort");
        executionTime(insertionSort, dataset, size, "Insertion Sort");
        executionTime(mergeSort, dataset, size, "Merge Sort");
        executionTime(quickSort, dataset, size, "Quick Sort");

        delete[] dataset;
    }

    return 0;
}
