#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <chrono> 
#include <map>
#include "Flights.h"
#include "Sort.h"
#include "constants.h"
using namespace std;
using namespace std::chrono; 

//O(1) time worst case
bool compare (Flights*& f1, Flights*& f2, string dataType, bool ascending)
{
    if (dataType == "efficiency")
    {
        if(ascending) {
            return f1->efficiency > f2->efficiency;
        } else {
            return f1->efficiency < f2->efficiency;
        }

    } else if (dataType == "seats") {

        if(ascending) {
            return f1->seats > f2->seats;
        } else {
            return f1->seats < f2->seats;
        }

    } else if (dataType == "passengers") {

        if(ascending) {
            return f1->passengers > f2->passengers;
        } else {
            return f1->passengers < f2->passengers;
        }

    } else if (dataType == "distance") {

        if(ascending) {
            return f1->distance > f2->distance;
        } else {
            return f1->distance < f2->distance;
        }
    }
}

//O(1) time worst case
bool mergeCompare (Flights*& f1, Flights*& f2, string dataType, bool ascending)
{
    if (dataType == "efficiency")
    {
        if(ascending) {
            return f1->efficiency <= f2->efficiency;
        } else {
            return f1->efficiency >= f2->efficiency;
        }

    } else if (dataType == "seats") {

        if(ascending) {
            return f1->seats <= f2->seats;
        } else {
            return f1->seats >= f2->seats;
        }

    } else if (dataType == "passengers") {

        if(ascending) {
            return f1->passengers <= f2->passengers;
        } else {
            return f1->passengers >= f2->passengers;
        }

    } else if (dataType == "distance") {

        if(ascending) {
            return f1->distance <= f2->distance;
        } else {
            return f1->distance >= f2->distance;
        }
    }
}

//shellsort function... average time complexity is O(n^5/4)
void shellSort(vector<Flights*>& flights, int gap, string dataType, bool ascending)
{
    int n = flights.size();

    while (gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            Flights* temp = flights[i];
            int j = i;

            while (j >= gap && compare(flights[j-gap], temp, dataType, ascending))
            {
                flights[j] = flights[j-gap];
                j -= gap;
            }
            flights[j] = temp;
        }
        gap/=2.2;
    }
}

//merge function for mergesort... time complexity is O(n)
void merge(vector<Flights*>& flights, int left, int middle, int right, string dataType, bool ascending)
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
        if (mergeCompare(leftArr[i], rightArr[j], dataType, ascending))
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

//mergesort function... average time complexity is O(nlog(n))
void mergeSort(vector<Flights*>& flights, int left, int right, string dataType, bool ascending)
{
    if (left < right)
    {
        int middle = (left + right) / 2;

        //recursively split the vector in half until base case
        mergeSort(flights, left, middle, dataType, ascending);
        mergeSort(flights, middle + 1, right, dataType, ascending);

        //merge the split vectors together
        merge(flights, left, middle, right, dataType, ascending);
    }
}

void PullData(vector<Flights*>& flights) {

    ifstream input("flightdata.csv");

    map <string, Flights*> flightsMap;

    if (!input.is_open()) {
        cout << "Error: File not detected." << endl;
    } else {

        string line;
        getline(input, line);

        while (getline(input, line)) {

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

            for (int i = 0; i < 7; i++) {
                if (i == 2) {
                    getline(stream, distance, ',');
                } else {
                    getline(stream, token, ',');
                }
            }

            getline(stream, name, ',');
            Flights* newFlight = new Flights(stof(seats), stof(passengers), name, stof(distance));

            if (flightsMap.find(name) == flightsMap.end()) {
                flightsMap[name] = newFlight;
            } else {
                flightsMap[name]->Increment(stof(seats), stof(passengers), stof(distance));
            }
        }

        for (auto iter = flightsMap.begin(); iter != flightsMap.end(); iter++) {
            flights.push_back(iter->second);
        }
    }
}

int main()
{
    cout << "Loading flight database..." << endl << endl; 

    vector<Flights*> data;
    PullData(data);

    cout << "Welcome to the Airline Sorter 1000. What would you like to do?" << endl << endl;

    bool menu = true;
    int counter = 0;

    while (menu) {
        if (counter > 0) {
            cout << "Would you like to do anything else?" << endl << endl; 
        }
        cout << "1. Sort by efficiency." << endl; 
        cout << "2. Sort by seats." << endl; 
        cout << "3. Sort by passengers." << endl; 
        cout << "4. Sort by distance." << endl; 
        cout << "0. Exit" << endl << endl; 
        counter += 1; 

        int input; 
        cin >> input;
        cout << endl; 

        if (input == 1) {
            auto start = high_resolution_clock::now();
            mergeSort(data, 0, data.size() - 1, "efficiency", false);
            //Sort<Flights*> sorter(Flights::EfficiencyCompGT);
            //sorter.QuickSort(data, 0, data.size() - 1);
            auto stop = high_resolution_clock::now(); 
            auto duration = duration_cast<microseconds>(stop - start); 

            int field_one_width = 0;
            int field_two_width = 0;

            for (int i = 0; i < 20; i++) {
                if (data[i]->name.length() > field_one_width) {
                    field_one_width = data[i]->name.length();
                }
                if (to_string(data[i]->efficiency).length() > field_two_width) {
                    field_two_width = to_string(data[i]->efficiency).length();
                }
            }
            for (int i = 0; i < 20; i++) {
                cout << setw(2) << right << i + 1 << ". " << "Airline: " <<
                    setw(field_one_width) << left << data[i]->name <<
                    "|" << " Efficiency: " << setw(6) << data[i]->efficiency << endl;
            }
            cout << endl << "Merge sort time to completion: " << duration.count() << " microseconds" << endl;
        }
        if (input == 2) {
            auto start = high_resolution_clock::now();
            mergeSort(data, 0, data.size() - 1, "seats", true);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            int field_one_width = 0;
            int field_two_width = 0;
            for (int i = 0; i < 20; i++) {
                if (data[i]->name.length() > field_one_width) {
                    field_one_width = data[i]->name.length();
                }
                if (to_string(data[i]->seats).length() > field_two_width) {
                    field_two_width = to_string(data[i]->seats).length();
                }
            }
            for (int i = 0; i < 20; i++) {
                cout << setw(2) << right << i + 1 << ". " << "Airline: " <<
                    setw(field_one_width) << left << data[i]->name <<
                    "|" << " Seats: " << setw(5) << data[i]->seats << endl;
            }
            cout << endl << "Merge sort time to completion: " << duration.count() << " microseconds" << endl;
        }
        if (input == 3) {
            auto start = high_resolution_clock::now();
            mergeSort(data, 0, data.size() - 1, "passengers", true);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

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
                cout << setw(2) << right << i + 1 << ". " << "Airline: " << 
                    setw(field_one_width) << left << data[i]->name << 
                    "|" << " Passengers: " << setw(5) << data[i]->passengers << endl;
            }
            cout << endl << "Merge sort time to completion: " << duration.count() << " microseconds" << endl;
        }
        if (input == 4) {
            auto start = high_resolution_clock::now();
            mergeSort(data, 0, data.size() - 1, "distance", true);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            int field_one_width = 0;
            int field_two_width = 0;
            for (int i = 0; i < 20; i++) {
                if (data[i]->name.length() > field_one_width) {
                    field_one_width = data[i]->name.length();
                }
                if (to_string(data[i]->distance).length() > field_two_width) {
                    field_two_width = to_string(data[i]->distance).length();
                }
            }
            for (int i = 0; i < 20; i++) {
                cout << setw(2) << right << i + 1 << ". " << "Airline: " <<
                    setw(field_one_width) << left << data[i]->name <<
                    "|" << " Distance: " << setw(5) << data[i]->distance << endl;
            }
            cout << endl << "Merge sort time to completion: " << duration.count() << " microseconds" << endl;
        }
        cout << endl; 
        if (input == 0) {
            cout << "Airline Sorter 1000 logging off. Goodbye." << endl; 
            menu = false; 
        }
        if (input < 0 || input > 4) {
            cout << "Invalid input. Please try again." << endl; 
        }
    }
    

    return 0; 
}

