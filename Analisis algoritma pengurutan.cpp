#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

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

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        std::swap(arr[min_idx], arr[i]);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
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
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template <typename Func, typename... Args>
void measureSortTime(Func sortFunc, int arr[], int n, const char* sortName, Args... args) {
    int* copy = new int[n];
    std::copy(arr, arr + n, copy);
    auto start = high_resolution_clock::now();
    sortFunc(copy, args...);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << setw(12) << sortName << ": " << setw(10) << duration.count() << " microseconds" << endl;
    delete[] copy;
}

int main() {
    const int sizes[] = {10, 100, 500, 1000, 10000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int* arr = new int[n];

        cout << "Array size: " << n << endl;

        for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
        cout << "Random data:" << endl;
        measureSortTime(bubbleSort, arr, n, "Bubble Sort", n);
        measureSortTime(insertionSort, arr, n, "Insertion Sort", n);
        measureSortTime(selectionSort, arr, n, "Selection Sort", n);
        measureSortTime(mergeSort, arr, n, "Merge Sort", 0, n - 1);
        measureSortTime(quickSort, arr, n, "Quick Sort", 0, n - 1);

        cout << string(40, '-') << endl;

        for (int i = 0; i < n; i++) arr[i] = n - i;
        cout << "Reversed data:" << endl;
        measureSortTime(bubbleSort, arr, n, "Bubble Sort", n);
        measureSortTime(insertionSort, arr, n, "Insertion Sort", n);
        measureSortTime(selectionSort, arr, n, "Selection Sort", n);
        measureSortTime(mergeSort, arr, n, "Merge Sort", 0, n - 1);
        measureSortTime(quickSort, arr, n, "Quick Sort", 0, n - 1);

        cout << string(40, '-') << endl;
        
        for (int i = 0; i < n; i++) arr[i] = i;
        cout << "Sorted data:" << endl;
        measureSortTime(bubbleSort, arr, n, "Bubble Sort", n);
        measureSortTime(insertionSort, arr, n, "Insertion Sort", n);
        measureSortTime(selectionSort, arr, n, "Selection Sort", n);
        measureSortTime(mergeSort, arr, n, "Merge Sort", 0, n - 1);
        measureSortTime(quickSort, arr, n, "Quick Sort", 0, n - 1);

        delete[] arr;
        cout << string(40, '=') << endl;
    }

    return 0;
}

