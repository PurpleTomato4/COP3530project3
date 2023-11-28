#pragma once
#include <string>
#include <vector>
#include <functional>
using namespace std;

template <typename T>

class Sort {
private:
    std::function<bool(T, T)> _comp;
    void swap(vector<T>& data, int a, int b);
    int partition(vector<T>& data, int low, int high);
public:
    Sort(function<bool(T, T)> comp);
    void QuickSort(vector<T>& data, int low, int high);
};

template <typename T>
Sort<T>::Sort(function<bool(T, T)> comp) {
    _comp = comp;
}

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
    T pivot = data[low];
    int up = low;
    int down = high;

    while (up < down) {
        for (int j = up; j < high; j++) {
            if (_comp(data[up], pivot)) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (!_comp(data[down], pivot)) {
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
