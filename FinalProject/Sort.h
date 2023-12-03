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
        int pivot = partition(data, low, high);
        QuickSort(data, low, pivot - 1);
        QuickSort(data, pivot + 1, high);
    }
}

template <typename T>
int Sort<T>::partition(vector<T>& data, int low, int high) {
    int mid = low + (high - low) / 2;
    T piv1 = data[low];
    T piv2 = data[mid];
    T piv3 = data[high];
    T pivot; 
    if ((piv1 >= piv2 && piv1 <= piv3) || (piv1 <= piv2 && piv1 >= piv3)) {
        pivot = piv1;
    }
    else if ((piv2 >= piv1 && piv2 <= piv3) || (piv2 <= piv1 && piv2 >= piv3)) {
        pivot = piv2;
    }
    else {
        pivot = piv3;
    }
    int up = low;
    int down = high;

    while (up < down) {
        for (int j = up; j < high; j++) {
            if (_comp(data[up], pivot, _ascending)) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (!_comp(data[down], pivot, _ascending)) {
                break;
            }
            down--;
        }
        if (up < down)
            swap(data, up, down);
    }
    swap(data, low, down);
    return down;
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

    // Compare data from left and right sub arrays and merge in the new sorted order
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

