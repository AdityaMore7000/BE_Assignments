#include <bits/stdc++.h>
#include <omp.h>  // For OpenMP functions

using namespace std;

int minval_sequential(int arr[], int n) {
    int minval = arr[0];
    for(int i = 0; i < n; i++) {
        if(arr[i] < minval) minval = arr[i];
    }
    return minval;
}

int maxval_sequential(int arr[], int n) {
    int maxval = arr[0];
    for(int i = 0; i < n; i++) {
        if(arr[i] > maxval) maxval = arr[i];
    }
    return maxval;
}

int sum_sequential(int arr[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

double average_sequential(int arr[], int n) {
    return (double)sum_sequential(arr, n) / n;
}

int minval_parallel(int arr[], int n) {
    int minval = arr[0];
    #pragma omp parallel for reduction(min:minval)
    for(int i = 0; i < n; i++) {
        if(arr[i] < minval) minval = arr[i];
    }
    return minval;
}

int maxval_parallel(int arr[], int n) {
    int maxval = arr[0];
    #pragma omp parallel for reduction(max:maxval)
    for(int i = 0; i < n; i++) {
        if(arr[i] > maxval) maxval = arr[i];
    }
    return maxval;
}

int sum_parallel(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

double average_parallel(int arr[], int n) {
    return (double)sum_parallel(arr, n) / n;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    double start, end;

    start = omp_get_wtime();
    cout << "\n🔵 Minimum value (sequential): " << minval_sequential(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🔵 Maximum value (sequential): " << maxval_sequential(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🔵 Summation (sequential): " << sum_sequential(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🔵 Average (sequential): " << average_sequential(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🟢 Minimum value (parallel): " << minval_parallel(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🟢 Maximum value (parallel): " << maxval_parallel(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🟢 Summation (parallel): " << sum_parallel(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    start = omp_get_wtime();
    cout << "\n🟢 Average (parallel): " << average_parallel(arr, n) << '\n';
    end = omp_get_wtime();
    cout << "⏱ Time: " << (end - start) * 1e6 << " microseconds\n";

    return 0;
}

/**
g++ -fopenmp filename.cpp -o program
./program
*/