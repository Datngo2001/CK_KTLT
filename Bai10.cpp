//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose:  Trò chơi cắt chữ 

#include <iostream>
#include <string>
using namespace std;

string copyStr(string a, int start, int end) {
	string temp = "";
	for (int i = start; i <= end; i++)
	{
		temp += a[i];
	}
	return temp;
}

int main()
{
	string a = "";
	cout << "Nhap chuoi: ";
	cin >> a;
	if (a.length() >= 200) {
		cout << "Chuoi qua dai!" << '\n';
		return 0;
	}

	int n = a.length();
	int inc[200]; // bang 1 neu tang và -1 neu giam
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] < a[i+1]) {
			inc[i] = 1;
		}
		else {
			inc[i] = -1;
		}
	}
	
	string max = "";
	max += a[0];
	int start = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int count = 1;
		while (inc[i] == 1) {
			count++;
			i++;
		}
		if (count > max.length()) {
			max = copyStr(a, start, i);
			start = i + 1;
			continue;
		}
		start++;
	}
	
	cout << "Ket qua: " << max << '\n';
	return 1;
}
