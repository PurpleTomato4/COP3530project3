/** COP3530 Project 3 - Airline Sorter 1000
 ** University of Florida - Fall 2023
 ** Authors: Jack Goldstein, Benjamin Uppgard, Ryan Wilson
 ** Date: 12/07/2023
 ** Atributions: QuickSort Hoare's partition function inspired by
 **              https://www.geeksforgeeks.org/hoares-vs-lomuto
 **              -partition-scheme-quicksort/
 **              ShellSort inspired by https://www.geeksforgeeks.org/shellsort/
 **              Other functions based on COP3530 lecture notes
 **/

#pragma once
#include <string>
#include <vector>
#include <functional>
using namespace std;

template <typename T>

class Sort {
private:
    std::function<bool(T, T, bool ascending)> _comp;
    bool _ascending;

public:
    Sort();
    Sort(function<bool(T, T, bool ascending)> comp, bool asc);
    void SetSortFunction(function<bool(T, T, bool ascending)> comp);
    void SetSortDirection(bool asc);

    // Quick Sort Functions
    void QuickSort(vector<T>& data, int low, int high);
private:
    void swap(vector<T>& data, int a, int b);
    int partition(vector<T>& data, int low, int high);

    // Merge Sort Functions
public:
    void MergeSort(vector<T>& data, int left, int right);
private:
    void merge(vector<T>& data, int left, int middle, int right);

    // Shell Sort Functions
public:
    void ShellSort(vector<T>& data);

};

template <typename T>
Sort<T>::Sort() {}

template <typename T>
Sort<T>::Sort(function<bool(T, T, bool ascending)> comp, bool asc) {
    _ascending = asc;
    _comp = comp;
}

template <typename T>
void Sort<T>::SetSortFunction(function<bool(T, T, bool ascending)> comp) {
    _comp = comp;
}

template <typename T>
void Sort<T>::SetSortDirection(bool asc) {
    _ascending = asc;
}

/*** Quick Sort ***/
template <typename T>
void Sort<T>::QuickSort(vector<T>& data, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(data, low, high);
        QuickSort(data, low, pivotIndex);
        QuickSort(data, pivotIndex + 1, high);
    }
}

template <typename T>
int Sort<T>::partition(vector<T>& data, int low, int high) {
    T pivot = data[low + (high - low) / 2];
    int i = low;
    int j = high;

    while (i < j) {
        // Scan from the left, find the first element greater than the pivot
        while (_comp(pivot, data[i], _ascending)) {
            i++;
        }
        // Scan from the right, find the first element less than the pivot
        while (_comp(pivot, data[j], !_ascending)) {
            j--;
        }
        // Swap the elements if they're on the wrong side of the pivot
        if (i < j) {
            swap(data, i, j);
            i++;
            j--;
        }
    }
    return j;
}

template <typename T>
void Sort<T>::swap(vector<T>& data, int a, int b) {
    T temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

/*** Merge Sort ***/
template <typename T>
void Sort<T>::MergeSort(vector<T>& data, int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;

        // Recursively split the vector in half until base case
        MergeSort(data, left, middle);
        MergeSort(data, middle + 1, right);

        // Merge the split vectors together
        merge(data, left, middle, right);
    }
}

template <typename T>
void Sort<T>::merge(vector<T> &data, int left, int middle, int right) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    vector<T> leftArr(leftSize);
    vector<T> rightArr(rightSize);

    // Fill the right and left vectors with the corresponding data
    for (int i = 0; i < leftSize; i++)
        leftArr[i] = data[left + i];
    for (int j = 0; j < rightSize; j++)
        rightArr[j] = data[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    // Compare data from left and right sub arrays and merge in the new sorted
    // order
    while (i < leftSize && j < rightSize) {
        if (_comp(leftArr[i], rightArr[j], _ascending)) {
            data[k] = rightArr[j];
            j++;
        } else {
            data[k] = leftArr[i];
            i++;
        }
        k++;
    }

    // Copy remaining elements from left array
    while (i < leftSize) {
        data[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements from right array
    while (j < rightSize) {
        data[k] = rightArr[j];
        j++;
        k++;
    }
}

/*** Shell Sort ***/
template <typename T>
void Sort<T>::ShellSort(vector<T>& data) {
    int n = data.size();
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            T temp = data[i];
            int j = i;
            while (j >= gap && _comp(data[j - gap], temp, _ascending)) {
                data[j] = data[j - gap];
                j -= gap;
            }
            data[j] = temp;
        }
        gap /= 2.2;
    }
}