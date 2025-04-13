#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

void binary_search_iterative(int arr[], int n, int target, ofstream &out)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            out << mid << endl;
            return;
        }
        else if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    out << "No Found" << endl;
}

int main()
{
    ifstream inputFile("input.txt");
    ofstream out("output_bsiterative.txt");
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
    binary_search_iterative(arr, n , target, out);
    out.close();
}