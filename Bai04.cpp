//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose: chương đọc dữ liệu từ tập tin INPUT.TXT trên vào ma trận cấp NxN (N=9)
//và viết hàm cho biết khối 3x3 nào còn ít nhất 1 ô trống(có chứa giá trị 0) và có số lượng
//ô trống ít nhất.Hàm trả về số thứ tự của khối 3x3 tìm thấy, cùng với số lượng ô trống
//còn lại trong khối đó.

#include <iostream>
using namespace std;

#define MAX 100

struct Matrix
{
    int size;
    int cell[MAX][MAX];
};

struct result {
    int block;
    int amount;
};

bool DocMatran(char const filename[], Matrix& mt);
void InMatran(Matrix mt);
result check(Matrix mt);

int main()
{
    Matrix mt;
    DocMatran("D:\INPUT.TXT", mt);
    InMatran(mt);
    result rs = check(mt); // số lượng khối tìm được
    if (rs.block != -1) {
        cout << "\nBlock: " << rs.block << '\n';
        cout << "Amount of empty cell: " << rs.amount << '\n';
    }
    return 1;
}

bool DocMatran(char const filename[], Matrix& mt){
    char temp[100];
    FILE* fp;
    fopen_s(&fp, filename, "r");
    if (fp == NULL)
    {
        cout << "Khong mo duoc tep!";
        return false;
    }
    mt.size = 9;
    for (int i = 0; i < mt.size; i++)
        for (int j = 0; j < mt.size; j++)
            fscanf_s(fp, "%d", &mt.cell[i][j]);
    fclose(fp);
}

void InMatran(Matrix mt) {
    for (int i = 0; i < mt.size; i++)
    {
        for (int j = 0; j < mt.size; j++)
        {
            printf("%5d\t", mt.cell[i][j]);
        }
        printf("\n");
    }
}

result check(Matrix mt) {
    result rs;
    rs.amount = 100;
    rs.block = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int count = 0;
            //check từng ô trong khối
            for (int a = 0; a < 3; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    if (mt.cell[a + i * 3][b + j * 3] == 0) {
                        count++;
                    }
                }
            }
            if (count != 0 && count < rs.amount) {
                rs.block = i + j * 3;
                rs.amount = count;
            }
        }
    }
    return rs;
}