#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(vector<int> &arr, int l, int m, int r) // Merge 2 sorted subarrays
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int> &arr, int l, int r) // Recursive Merge Sort
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
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

int main()
{
    const int size = 10000; // Size of the array
    vector<int> arr(size), arr_copy(size);

    for (int i = 0; i < size; ++i) // Initialize array with random values
    {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    // Measure sequential Bubble Sort execution time using clock()
    clock_t start = clock();
    bubbleSort(arr_copy);
    clock_t stop = clock();
    double seq_duration_bubble = double(stop - start) * 1000 / CLOCKS_PER_SEC;

    // Measure parallel Bubble Sort execution time using clock()
    start = clock();
    parallelBubbleSort(arr);
    stop = clock();
    double par_duration_bubble = double(stop - start) * 1000 / CLOCKS_PER_SEC;

    // Measure sequential Merge Sort execution time using clock()
    start = clock();
    mergeSort(arr_copy, 0, size - 1);
    stop = clock();
    double seq_duration_merge = double(stop - start) * 1000 / CLOCKS_PER_SEC;

    // Measure parallel Merge Sort execution time using clock()
    start = clock();
    parallelMergeSort(arr, 0, size - 1);
    stop = clock();
    double par_duration_merge = double(stop - start) * 1000 / CLOCKS_PER_SEC;

    cout << "Sequential Bubble Sort Time: " << seq_duration_bubble << " milliseconds" << endl;
    cout << "Parallel Bubble Sort Time: " << par_duration_bubble << " milliseconds" << endl;
    cout << "Sequential Merge Sort Time: " << seq_duration_merge << " milliseconds" << endl;
    cout << "Parallel Merge Sort Time: " << par_duration_merge << " milliseconds" << endl;

    return 0;
}

/* To Run Execute the following commands:
g++ -fopenmp Assignment2.cpp -o Assignment2
./Assignment2
*/
