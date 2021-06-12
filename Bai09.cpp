//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose:  chương trình mở và đọc dữ liệu từ tập tin INPUT.TXT trên, lưu vào biến N và
//mảng 2 chiều(ma trận).Áp dụng phương pháp tham lam(Greedy) để tìm một con
//đường đi từ ô(0, 0) sang cột cuối cùng của ma trận, sao cho tổng giá trị các phần tử
//nằm trên đường đi là lớn nhất(ví dụ đường đi in đậm 2348 trong ma trận ở
//trên).Nguyên tắc đi như sau : khi ta đang ở ô(i, j), có thể di chuyển ngang sang các ô
//tiếp theo là(i - 1, j + 1), (i, j + 1) hoặc(i + 1, j + 1).Xuất kết quả(tổng lớn nhất và các vị trí
//nằm trên đường đi) ra màn hình.

#include <iostream>
using namespace std;

#define MAX 100

void InMatran(int a[MAX][MAX], int n);
bool DocMatran(const char fname[], int a[MAX][MAX], int &n);
int thamlam(int a[MAX][MAX], int n, int path[]);

int main()
{
    int a[MAX][MAX];
    int n = 0;
    if (DocMatran("D:\INPUT.txt", a, n) == false)
    {
        return 0;
    }
    InMatran(a, n);

    int path[MAX];
    int sum = thamlam(a, n, path);

    cout << "Tong: " << sum << '\n';
    cout << "Duong di: ";
    for (int i = 0; i < n - 1; i++)
    {
        cout << path[i] << "-->";
    }
    cout << path[n - 1] << '\n';
}
bool DocMatran(const char fname[], int a[MAX][MAX], int &n)
{
    char temp[100];
    FILE *fp;
    fopen_s(&fp, fname, "r");
    if (fp == NULL)
    {
        cout << "Khong mo duoc tep!";
        return false;
    }
    fscanf_s(fp, "%d", &n);
    if (n <= 0 || n > 20)
    {
        cout << "ma tran qua lon!" << '\n';
        fclose(fp);
        return false;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf_s(fp, "%d", &a[i][j]);
    fclose(fp);
    return true;
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
int thamlam(int a[MAX][MAX], int n, int path[])
{
    int sum = 0;
    int node = 0; // index of path
    sum += a[0][0];
    path[node] = a[0][0];
    node++;

    int pos = 0; //vi tri duoc chon trong hang dang xet
    for (int i = 1; i < n; i++)
    {
        int next = pos;
        // top
        if ((pos - 1) > 0 && a[pos - 1][i] > a[pos][i])
        {
            next = pos - 1;
        }
        // bottom
        if ((pos + 1) < n && a[pos + 1][i] > a[next][i])
        {
            next = pos + 1;
        }
        //neu duong tren va duoi ko lon hon duong giua thi pos giu nguyen
        pos = next;
        sum += a[next][i];
        path[node] = a[next][i];
        node++;
    }

    return sum;
}