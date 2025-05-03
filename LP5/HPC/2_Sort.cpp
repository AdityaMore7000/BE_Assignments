#include <iostream>
#include <vector>
#include <omp.h> // For OpenMP and omp_get_wtime()
#include <cstdlib> // For rand()

using namespace std;

// Sequential Bubble Sort
void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Merge two sorted subarrays
void merge(vector<int> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Sequential Merge Sort
void mergeSort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Bubble Sort using OpenMP
void parallelBubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main() {
    const int size = 10000;
    vector<int> arr(size), arr_copy(size);

    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    // Sequential Bubble Sort
    double start = omp_get_wtime();
    bubbleSort(arr_copy);
    double end = omp_get_wtime();
    cout << "Sequential Bubble Sort Time: " << (end - start) * 1000 << " ms" << endl;

    // Parallel Bubble Sort
    for (int i = 0; i < size; ++i) arr[i] = arr_copy[i];
    start = omp_get_wtime();
    parallelBubbleSort(arr);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << (end - start) * 1000 << " ms" << endl;

    // Sequential Merge Sort
    for (int i = 0; i < size; ++i) arr_copy[i] = rand() % 1000;
    start = omp_get_wtime();
    mergeSort(arr_copy, 0, size - 1);
    end = omp_get_wtime();
    cout << "Sequential Merge Sort Time: " << (end - start) * 1000 << " ms" << endl;

    // Parallel Merge Sort
    for (int i = 0; i < size; ++i) arr[i] = arr_copy[i];
    start = omp_get_wtime();
    parallelMergeSort(arr, 0, size - 1);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (end - start) * 1000 << " ms" << endl;

    return 0;
}

/**
g++ -fopenmp parallel_sorts.cpp -o parallel_sorts
./parallel_sorts
*/