//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose: chương trình đọc dữ liệu từ tập tin INPUT.TXT trên vào ma trận vuông cấp
//NxN và cho biết ma trận đọc được có phải là ma phương cấp N hay không.

#include <iostream>
using namespace std;

#define MAX 100

void InMatran(int a[MAX][MAX], int n);
bool DocMatran(const char fname[], int a[MAX][MAX], int& n);

bool CheckValue(int a[MAX][MAX], int n);

bool isDuplicate(int arr[MAX][MAX], int n);

bool CheckMagic(int arr[MAX][MAX], int n);

int main()
{
    int a[MAX][MAX];
    int n = 0;
    DocMatran("D:\INPUT.TXT", a, n);
    InMatran(a, n);

    if (CheckValue(a, n) == true)
    {
        cout << "Matrix is ok" << '\n';
    }
    else
    {
        cout << "Matrix have sum invalid" << '\n';
        return 0;
    }
    if (isDuplicate(a, n) == true)
    {
        cout << "Matrix is dup" << '\n';
        return 0;
    }
    else
    {
        cout << "Matrix is not dup" << '\n';
    }
    if (CheckMagic(a, n) == true)
    {
        cout << "Matrix is magic" << '\n';
    }
    else
    {
        cout << "Matrix is not magic" << '\n';
    }
}

bool DocMatran(const char fname[], int a[MAX][MAX], int& n)
{
    char temp[100];
    FILE* fp;
    fopen_s(&fp, fname, "r");
    if (fp == NULL)
    {
        cout << "Khong mo duoc tep!";
        return false;
    }
    fscanf_s(fp, "%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf_s(fp, "%d", &a[i][j]);
    fclose(fp);
}
void InMatran(int a[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d\t", a[i][j]);
        }
        printf("\n");
    }
}
bool CheckValue(int a[MAX][MAX], int n)
{
    int max = pow(n, 2);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] >= 1 && a[i][j] <= max)
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}
bool isDuplicate(int arr[MAX][MAX], int n)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int key = arr[i][j];
            // search for key
            for (int a = i; a < n; a++)
            {
                for (int b = j + 1; b < n; b++)
                {
                    if (arr[a][b] == key)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool CheckMagic(int arr[MAX][MAX], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[0][i];
    }

    // check row
    int tempSum = 0;
    for (int i = 0; i < n; i++)
    {
        tempSum = 0;
        for (int j = 0; j < n; j++)
        {
            tempSum += arr[i][j];
        }
        if (tempSum != sum)
            return false;
    }
    // check column
    for (int j = 0; j < n; j++)
    {
        tempSum = 0;
        for (int i = 0; i < n; i++)
        {
            tempSum += arr[i][j];
        }
        if (tempSum != sum)
            return false;
    }
    // check cross
    int i = 0;
    int j = 0;
    tempSum = 0;
    while (i < n && j < n)
    {
        tempSum += arr[i][j];
        i++;
        j++;
    }
    if (tempSum != sum)
        return false;

    i = 0;
    j = n - 1;
    tempSum = 0;
    while (i < n && j >= 0)
    {
        tempSum += arr[i][j];
        i++;
        j--;
    }
    if (tempSum != sum)
        return false;

    return true;
}


