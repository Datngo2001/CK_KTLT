//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose:  chương trình mở và đọc dữ liệu từ tập tin INPUT.TXT trên, lưu vào biến N và
//mảng 2 chiều(ma trận).Sử dụng phương pháp vét cạn để tìm một đường đi từ phần
//tử ở giữa của dòng đầu của ma trận A ở trên(phần tử A[0][N - 1]) xuống dòng
//cuối cùng của ma trận, sao cho tổng các phần tử trên đường đi đạt giá trị lớn nhất.
//Nguyên tắc đi như sau : từ vị trí(i, j), ta chỉ có thể đi đến các vị trí(i + 1, j - 1), (i + 1, j) hoặc(i + 1, j + 1).

#include <iostream>
using namespace std;

#define MAX 100

void InMatran(int a[MAX][MAX], int n);
bool DocMatran(const char fname[], int a[MAX][MAX], int& n);
void travel(int a[MAX][MAX], int n, int startRow, int startCol, int& sum, string& path);

int main()
{
    int a[MAX][MAX];
    int n = 0;
    if (DocMatran("D:\INPUT.txt", a, n) == false) {
        return 0;
    }
    InMatran(a, n);
    
    int sum = 0;
    string path = "";
    travel(a, n, 0, n - 1, sum, path);

    cout << "\nDuong di: " << path << '\n';
    cout << "Tong: " << sum << '\n';
    cout << "\n\n\n";
    cout << "Chu thich: " << '\n';
    cout << "L: di sang trai" << '\n';
    cout << "R: di sang phai" << '\n';
    cout << "M: di giua" << '\n';
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
    if (n <= 0 || n > 20) {
        cout << "ma tran qua lon!" << '\n';
        fclose(fp);
        return false;
    }
    int m = 2 * n - 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf_s(fp, "%d", &a[i][j]);
    fclose(fp);
    return true;
}
void InMatran(int a[MAX][MAX], int n)
{
    int m = 2 * n - 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%5d\t", a[i][j]);
        }
        printf("\n");
    }
}
void travel(int a[MAX][MAX], int n, int startRow, int startCol, int& sum, string& path) {

    sum += a[startRow][startCol];

    if (startRow == n - 1) {
        // đã đạt tới đáy
        return;
    }
    //Check Left Mid Right
    int sumL = 0;
    int sumM = 0;
    int sumR = 0;
    string pathL = "";
    string pathM = "";
    string pathR = "";

    //left
    pathL += "L ";
    travel(a, n, startRow + 1, startCol - 1, sumL, pathL);
    //mid
    pathM += "M ";
    travel(a, n, startRow + 1, startCol, sumM, pathM);
    //right
    pathR += "R ";
    travel(a, n, startRow + 1, startCol + 1, sumR, pathR);

    if (sumL >= sumR && sumL >= sumM) {
        //left max
        sum += sumL;
        path += pathL;
    }
    else if (sumM >= sumL && sumM >= sumR) {
        //mid max
        sum += sumM;
        path += pathM;
    }
    else if (sumR >= sumM && sumR >= sumL) {
        //right max
        sum += sumR;
        path += pathR;
    }
}