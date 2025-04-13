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
void quick_sort(int arr[], int left, int right)
{
    if (left >= right)
        return;

    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (i <= j)
    {
        while (i <= j && arr[i] <= pivot)
            i++;
        while (i <= j && arr[j] > pivot)
            j--;

        if (i < j)
            swap(arr[i], arr[j]);
    }

    swap(arr[left], arr[j]);

    quick_sort(arr, left, j - 1);
    quick_sort(arr, j + 1, right);
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
    ofstream out("output_qs.txt");
    int n;
    inputFile >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        inputFile >> arr[i];
    }

    inputFile.close();

    quick_sort(arr, 0, n - 1);
    print_array(arr, n);
    for (int i = 0; i < n; ++i)
    {
        out << arr[i] << " ";
    }
    out << endl;
    out.close();
}