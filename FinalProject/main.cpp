#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Flights.h"
#include "TextureManager.h"
#include "constants.h"
#include <iomanip>
using namespace std;

//merge function for mergesort... time complexity is O(n)
void merge(vector<Flights*>& flights, int left, int middle, int right, string parameter)
{
    int leftSize = middle - left + 1;
    int rightSize = right - middle;


    vector<Flights*> leftArr(leftSize);
    vector<Flights*> rightArr(rightSize);


    //fill the right and left vectors with the corresponding data
    for (int i = 0; i < leftSize; i++)
        leftArr[i] = flights[left + i];
    for (int j = 0; j < rightSize; j++)
        rightArr[j] = flights[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    //compare data from left and right sub arrays and merge in the new sorted order
    while (i < leftSize && j < rightSize)
    {
        if (parameter == "efficiency") {
            if (leftArr[i]->efficiency >= rightArr[j]->efficiency)
            {
                flights[k] = leftArr[i];
                i++;
            }
            else
            {
                flights[k] = rightArr[j];
                j++;
            }
            k++;
        }
        if (parameter == "distance") {
            if (leftArr[i]->distance >= rightArr[j]->distance)
            {
                flights[k] = leftArr[i];
                i++;
            }
            else
            {
                flights[k] = rightArr[j];
                j++;
            }
            k++;
        }
        if (parameter == "passengers") {
            if (leftArr[i]->passengers >= rightArr[j]->passengers)
            {
                flights[k] = leftArr[i];
                i++;
            }
            else
            {
                flights[k] = rightArr[j];
                j++;
            }
            k++;
        }
        if (parameter == "seats") {
            if (leftArr[i]->seats >= rightArr[j]->seats)
            {
                flights[k] = leftArr[i];
                i++;
            }
            else
            {
                flights[k] = rightArr[j];
                j++;
            }
            k++;
        }
    }

    //copy remaining elements from left array
    while (i < leftSize)
    {
        flights[k] = leftArr[i];
        i++;
        k++;
    }

    //copy remaining elements from right array
    while (j < rightSize)
    {
        flights[k] = rightArr[j];
        j++;
        k++;
    }
}

//mergesort function... time complexity is O(nlog(n))
void mergeSort(vector<Flights*>& flights, int left, int right, string parameter)
{
    if (left < right)
    {
        int middle = (left + right) / 2;

        //recursively split the vector in half until base case
        mergeSort(flights, left, middle, parameter);
        mergeSort(flights, middle + 1, right, parameter);

        //merge the split vectors together
        merge(flights, left, middle, right, parameter);
    }
}

void PullData(vector<Flights*>& flights) {

    ifstream input("flightdata.csv");
    if (!input.is_open())
    {
        cout << "Error: File not detected." << endl;
        return; 
    }
    string line;
    getline(input, line);
    while (getline(input, line))
    {
        istringstream stream(line);
        //anytime get line is used with token it is just to skip past that piece of data
        string token;
        string departures;
        string seats;
        string passengers;
        string distance;
        string name;

        getline(stream, token, ',');
        getline(stream, departures, ',');
        getline(stream, token, ',');
        getline(stream, seats, ',');
        getline(stream, passengers, ',');

        for (int i = 0; i < 7; i++)
        {
            if (i == 2) {
                getline(stream, distance, ',');
            }
            else {
                getline(stream, token, ',');
            }
        }
        getline(stream, name, ',');
        Flights* newFlight = new Flights(stof(seats), stof(passengers), name, stof(distance)); 
        flights.push_back(newFlight);
    }
}

int main()
{

    vector<Flights*> data;
    PullData(data);

    bool menu = true; 

    while (menu) {
        cout << "Welcome to the Airline Sorter 1000. What would you like to do?" << endl << endl; 
        cout << "1. Sort by efficiency." << endl; 
        cout << "2. Sort by seats." << endl; 
        cout << "3. Sort by passengers." << endl; 
        cout << "4. Sort by distance." << endl; 
        cout << "0. Exit" << endl; 
        int input; 
        cin >> input; 

        if (input == 1) {
            mergeSort(data, 0, data.size() - 1, "efficiency");
            for (int i = 0; i < 20; i++) {
                cout << i + 1 << ". " << "Airline: " << data[i]->name << " Efficiency: " << data[i]->efficiency << endl;
            }
        }
        if (input == 2) {
            mergeSort(data, 0, data.size() - 1, "seats");
            for (int i = 0; i < 20; i++) {
                cout << i + 1 << ". " << "Airline: " << data[i]->name << " Seats: " << data[i]->seats << endl;
            }
        }
        if (input == 3) {
            mergeSort(data, 0, data.size() - 1, "passengers");
            int field_one_width = 0; 
            int field_two_width = 0; 
            for (int i = 0; i < 20; i++) {
                if (data[i]->name.length() > field_one_width) {
                    field_one_width = data[i]->name.length(); 
                }
                if (to_string(data[i]->passengers).length() > field_two_width) {
                    field_two_width = to_string(data[i]->passengers).length();
                }
            }
            for (int i = 0; i < 20; i++) {
                cout << setw(2) << right << i + 1 << ". " << "Airline: " << setw(field_one_width) << left << data[i]->name << "|" << " Passengers: " << setw(5) << data[i]->passengers << endl;
            }
        }
        if (input == 4) {
            mergeSort(data, 0, data.size() - 1, "distance");
            for (int i = 0; i < 20; i++) {
                cout << i + 1 << ". " << "Airline: " << data[i]->name << " Distance: " << data[i]->distance << endl;
            }
        }
        cout << endl; 
        if (input == 0) {
            "Airline Sorter 1000 logging off. Goodbye."; 
            menu = false; 
        }

    }
    

    return 0; 
}

