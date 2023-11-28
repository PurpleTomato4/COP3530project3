#include <iostream>
#include <vector>
#include "Sort.h"
using namespace std;

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
    int pivot = data[low];
    int up = low;
    int down = high;

    while (up < down) {
        for (int j = up; j < high; j++) {
            if (data[up] > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (data[down] < pivot)
                break;
            down--;
        }
        if (up < down)
            swap(&data[up], &data[down]);
    }
    swap(&data[low], &data[high]);
    return down;
}

template <typename T>
void Sort<T>::swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}
