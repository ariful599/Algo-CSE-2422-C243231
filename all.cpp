#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for(int i = 0; i < n1; i++) L[i] = arr[left + i];
    for(int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right)
{
    if(left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generateArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000;
    }
}

int main()
{
    srand(time(0));

    int sizes[] = {10, 100, 1000, 10000, 100000};

    cout << "Student Name: Md Ariful Islam Siam" << endl;
    cout << "Student ID: C243231" << endl << endl;

    for(int i = 0; i < 5; i++)
    {
        int n = sizes[i];


        int* original = new int[n];
        generateArray(original, n);


        int* arr1 = new int[n];
        int* arr2 = new int[n];
        int* arr3 = new int[n];

        copy(original, original + n, arr1);
        copy(original, original + n, arr2);
        copy(original, original + n, arr3);


        auto start1 = high_resolution_clock::now();
        insertionSort(arr1, n);
        auto end1 = high_resolution_clock::now();


        auto start2 = high_resolution_clock::now();
        mergeSort(arr2, 0, n - 1);
        auto end2 = high_resolution_clock::now();


        auto start3 = high_resolution_clock::now();
        quickSort(arr3, 0, n - 1);
        auto end3 = high_resolution_clock::now();


        auto t1 = duration_cast<microseconds>(end1 - start1);
        auto t2 = duration_cast<microseconds>(end2 - start2);
        auto t3 = duration_cast<microseconds>(end3 - start3);


        cout << "Input Size: " << n << endl;
        cout << "Insertion Sort Time: " << t1.count() << " microseconds" << endl;
        cout << "Merge Sort Time:     " << t2.count() << " microseconds" << endl;
        cout << "Quick Sort Time:     " << t3.count() << " microseconds" << endl;


        delete[] original;
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
    }

    return 0;
}
