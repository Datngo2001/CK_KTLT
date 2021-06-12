//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose: chương trình đọc dữ liệu từ tập tin INPUT.TXT trên vào ma trận cấp NxN và
//kiểm tra xem ma trận đọc được có phải là ma trận xoắn ốc cấp N tăng dần thuận chiều
//kim đồng hồ hay không

#include <iostream>
using namespace std;
#define MAX 100

void InMatran(int a[MAX][MAX], int n);
bool DocMatran(const char fname[], int a[MAX][MAX], int& n);
bool ktXoanOc(int a[MAX][MAX], int n); // hàm kiểm tra xoắn ốc

int main()
{
    int a[MAX][MAX];
    int n = 0;
    DocMatran("D:\INPUT.TXT", a, n);
    InMatran(a, n);

    if (ktXoanOc(a, n) == true) {
        cout << "La ma tran xoan oc!" << '\n';
    }
    else {
        cout << "Khong la ma tran xoan oc!" << '\n';
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
bool ktXoanOc(int a[MAX][MAX], int n) {
    int d = 0, i, count = 1;
    int hang = n - 1, cot = n - 1;
    int pre = -1; // biến tạm để so sánh
    while (count <= n * n) {
        // check tu trai sang phai  
        for (i = d; i <= cot; i++) {
            if (a[d][i] <= pre) return false;
            pre = a[d][i];
            count++;           
        }
        for (i = d + 1; i <= hang; i++) {
            // check tu tren xuong duoi
            if (a[i][cot] <= pre) return false;
            pre = a[i][cot];
            count++; 
        }
        for (i = cot - 1; i >= d && count <= n * n; i--) {
            // check tu phai sang trai
            if (a[hang][i] <= pre) return false;
            pre = a[hang][i];
            count++;
        }
        for (i = hang - 1; i > d && count <= n * n; i--) {
            // check tu duoi len 
            if (a[i][d] <= pre) return false;
            pre = a[i][d];
            count++;  
        }
        // thu nho xoan oc
        d++; hang--; cot--;
    }
    return true;
}