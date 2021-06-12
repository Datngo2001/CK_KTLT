//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose: chương trình đọc dữ liệu từ tập tin INPUT.TXT trên, lưu vào biến N và mảng
//2 chiều(ma trận), cho biết ma trận vừa đọc được có phải là ma trận tam giác dưới hay
//không

#include <iostream>
using namespace std;

#define MAX 100

void InMatran(int a[MAX][MAX], int n);
bool DocMatran(const char fname[], int a[MAX][MAX], int& n);

bool isLowerTri(int a[MAX][MAX], int n);

int main()
{
    int a[MAX][MAX];
    int n = 0;
    
    DocMatran("D:\INPUT.txt", a, n);
    InMatran(a, n);
    cout << '\n';
    
    if (isLowerTri(a, n) == true) {
        cout << "Maxtrix is lower triagular! " << '\n';
    }
    else {
        cout << "Maxtrix is not lower triagular! " << '\n';
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

bool isLowerTri(int a[MAX][MAX], int n) {
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i < j) {
                if (a[i][j] != 0) return false;
            }
            else {
                if (a[i][j] == 0) return false;
            }
        }
    }
    return true;
}
