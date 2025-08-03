#include <iostream>
#include <vector>
using namespace std;

void Swap(int* ele1, int* ele2) {
    int temp = *ele1;
    *ele1 = *ele2;
    *ele2 = temp;
}

vector<int> BubbleSort(vector<int> arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - (i + 1); j++) {
            if (arr[j] > arr[j + 1]) {
                Swap(&arr[j], &arr[j+1]);
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
    return arr;
}

vector<int> SelectionSort(vector<int> arr, int n) {
    for (int i = 0; i < n; i++) {
        int smallest = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[smallest]) {
                smallest = j;
            };
        }
        Swap(&arr[i], &arr[smallest]);
    }
    return arr;
}

vector<int> CountSort(vector<int> inputArray, int n) {
    // finding the largest element in the array
    int largest = inputArray[0];
    for (int i = 0; i < n; ++i) {
        if (largest < inputArray[i]) {
            largest = inputArray[i];
        }
    }
    // declaring countArray, outputArray and initalizing to 0
    vector<int> countArray(largest + 1,0);
    vector<int> outputArray(n, 0);

    // counting the values from inputArray into countArray
    for (int i = 0; i < n; ++i) countArray[inputArray[i]] += 1;

    // adding the values up in countArray
    for (int i = 0; i < largest; ++i) {
        countArray[i + 1] += countArray[i];
    }

    // adding elements back into output array
    for (int i = 0; i < n; ++i) {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }
    return outputArray;
}

void QuickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int pivot = arr[high - 1];
    int i = low - 1;

    for (int j = low; j < high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high - 1]); 

    QuickSort(arr, low, i + 1);  
    QuickSort(arr, i + 2, high);
}


void PrintArray(vector<int> arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void LinearSearch(vector<int> arr, int size, int goal) {
    for (int i = 0; i < size; i++) {
        if (arr.at(i) == goal) {
            cout << goal << " found at index " << i << endl;
            return;
        }
    }
    cout << "Error: " << goal << " not found." << endl;
    return;
}

int BinarySearch(const vector<int>& arr, int size, int goal) {
    int min = 0;
    int max = size - 1;

    while (min <= max) {
        int mid = min + (max - min) / 2;

        if (arr.at(mid) == goal) {
            cout << goal << " found at index " << mid << "." << endl;
            return mid;
        }

        if (arr.at(mid) > goal) {
            max = mid - 1;
        }
        else {
            min = mid + 1;
        }
    }
    cout << "Error: " << goal << " not found." << endl;
}


int main()
{
    vector<int> arr;
    int n = 0;
    int input;
    bool current = true;
    while (current) {
        cout << "Please enter element to array to be sorted. Enter -1 to when done: ";
        cin >> input;
        if (input == -1) {
            cout << "Press 1 to sort via bubble sort " << endl << "Press 2 to sort via selection sort " << endl << "Press 3 to sort via count sort" << endl << "Press 4 to sort via quick sort" << endl << "Press -1 to quit" << endl;
            cout << "Choose option here: ";
            cin >> input;
            n = arr.size();
            switch (input) {
            case -1:
                current = false;
                break;
            case 1:
                PrintArray(BubbleSort(arr, n), n);
                break;
            case 2:
                PrintArray(SelectionSort(arr, n), n);
                break;
            case 3:
                PrintArray(CountSort(arr, n), n);
                break;
            case 4:
                QuickSort(arr, 0, n), n;
                PrintArray(arr, n);
                break;
            }
            if (current == true) {
                cout << "Enter a node to search for: ";
                cin >> input;
                cout << endl << "Search for " << input << " by:" << endl;
                cout << "Binary search, press 1: " << endl;
                cout << "Linear search, press 2: " << endl;
                int temp;
                cin >> temp;
                if (temp == 1) {
                    BinarySearch(arr, n, input);
                }
                else if (temp == 2) {
                    LinearSearch(arr, n, input);
                }
            }
        }
        else arr.push_back(input);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
