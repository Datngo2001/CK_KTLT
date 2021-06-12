// Author: Ngô Minh Dat
// ID: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
// Purpose: Cài đặt thuật
//toán sắp xếp mảng a tăng dần bằng phương pháp sắp xếp dựa trên phân hoạch
//PartitionSort(hay còn gọi là phương pháp sắp xếp nhanh QuickSort) theo 2 cách: sử
//dụng đệ quy và không sử dụng đệ quy.

#include <iostream>

#define MAX 100

using namespace std;

int partition(int arr[], int left, int right);

void quickSort(int arr[], int left, int right);

void output(int arr[], int n);

int main()
{
    int arr[MAX];
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Nhap phan tu thu " << i << " : ";
        cin >> arr[i];
    }
    cout << "Array after sorting: ";
    quickSort(arr, 0, n - 1);
    output(arr, n);
    return 0;
}

int partition(int arr[], int left, int right)
{
    int i = left - 1;
    int j = right + 1;
    int pivot = left + 1;

    while (true)
    {
        do
        {
            i++;
        } while (arr[i] < arr[pivot]);
        do
        {
            j--;
        } while (arr[j] > arr[pivot]);

        if (i >= j)
        {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

void quickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int pi = partition(arr, left, right);
        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}

void output(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
