//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose: Lập ma trận bãi mìn

#include <iostream>
using namespace std;

#define MAX 100

bool InMatran(const char fname[], int a[MAX][MAX], int m, int n);
bool DocMatran(const char fname[], int a[MAX][MAX], int& m, int& n);
void lapMatran(int a[MAX][MAX], int m, int n);

int main()
{
    int a[MAX][MAX];
    int n = 0;
    int m = 0;
    DocMatran("D:\BAI4.INP", a, m, n);
    lapMatran(a, m, n);
    InMatran("D:\BAI4.OUT", a, m, n);
    cout << "Complete! check D:\\BAI4.OUT for result." << '\n';
}

bool DocMatran(const char fname[], int a[MAX][MAX], int& m, int& n)
{
    char temp[100];
    FILE* fp;
    fopen_s(&fp, fname, "r");
    if (fp == NULL)
    {
        cout << "Khong mo duoc tep!";
        return false;
    }
    fscanf_s(fp, "%d", &m);
    fscanf_s(fp, "%d", &n);

    if (m < 0 || n > 100) {
        cout << "Sai kich thuoc!" << '\n';
        fclose(fp);
        return false;
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            fscanf_s(fp, "%d", &a[i][j]);
    fclose(fp);
}
bool InMatran(const char fname[], int a[MAX][MAX], int m, int n)
{
    char temp[100];
    FILE* fp;
    fopen_s(&fp, fname, "w");
    if (fp == NULL)
    {
        cout << "Khong mo duoc tep!";
        return false;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++)
            fprintf_s(fp, "%d ", a[i][j]);
        fprintf_s(fp, "%d\n", a[i][n - 1]);
    }
    fclose(fp);
}
void lapMatran(int a[MAX][MAX], int m, int n) {
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == 1) {
                a[i][j] = 9;
                continue;
            }

            int count = 0;
            // xét các ô xung quanh theo chiều kim đồng hồ bất đầu với ô hướng Bắc
            //Bắc
            if ((i - 1) > 0 && (a[i - 1][j] == 1 || a[i - 1][j] == 9)) {
                count++;
            }
            //Đông Bắc
            if ((i - 1) > 0 && (j + 1) < n && (a[i - 1][j + 1] == 1 || a[i - 1][j + 1] == 9)) {
                count++;
            }
            //Đông
            if ((j + 1) < n && (a[i][j + 1] == 1 || a[i][j + 1] == 9)) {
                count++;
            }
            //Đông Nam
            if ((i + 1) < n && (j + 1) < n && (a[i + 1][j + 1] == 1 || a[i + 1][j + 1] == 9)) {
                count++;
            }
            //Nam
            if ((i + 1) < n && (a[i + 1][j] == 1 || a[i + 1][j] == 9)) {
                count++;
            }
            //Tây Nam
            if ((i + 1) < n && (j - 1) > 0 && (a[i + 1][j - 1] == 1 || a[i + 1][j - 1] == 9)) {
                count++;
            }
            //Tây
            if ((j - 1) > 0 && (a[i][j - 1] == 1 || a[i][j - 1] == 9)) {
                count++;
            }
            //Tây Bắc
            if ((i - 1) > 0 && (j - 1) > 0 && (a[i - 1][j - 1] == 1 || a[i - 1][j - 1] == 9)) {
                count++;
            }

            a[i][j] = count;
        }
    }
}