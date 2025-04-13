#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

void binary_search_recursive(int arr[], int left, int right, int target, ofstream &out)
{
    if (left > right)
    {
        out << "No Found" << endl;
        return;
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target)
    {
        out << mid << endl;
        return;
    }
    else if (arr[mid] > target)
    {
        binary_search_recursive(arr, left, mid - 1, target, out);
    }
    else
    {
        binary_search_recursive(arr, mid + 1, right, target, out);
    }
}

int main()
{
    ifstream inputFile("input.txt");
    ofstream out("output_rec.txt");
    int n;
    inputFile >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        inputFile >> arr[i];
    }

    int target;
    inputFile >> target;

    inputFile.close();

    sort(arr, arr + n); 
    binary_search_recursive(arr, 0, n - 1, target, out);
}