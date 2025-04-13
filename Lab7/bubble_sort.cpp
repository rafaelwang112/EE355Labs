#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    ifstream inputFile("input.txt");
    ofstream out("output_bubble.txt");
    int n;
    inputFile >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        inputFile >> arr[i];
    }

    inputFile.close();

    bubble_sort(arr, n);
    print_array(arr, n);
    for (int i = 0; i < n; ++i)
    {
        out << arr[i] << " ";
    }
    out << endl;
    out.close();
}