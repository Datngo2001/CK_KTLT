//Name: Ngo Minh Dat
//Id: 19110115
//Birth date: 5/2/2001
//Class: PRTE230385E_20_2_01CLC
//Purpose: Chương trình nhập vào 2 số nguyên lớn (có tối đa 100 chữ số). Thực hiện các phép
//tính cộng, trừ, nhân và chia(lấy phần nguyên) đối với 2 số này và in kết quả tìm được
//ra màn hình

#include <iostream>
#include <conio.h>
using namespace std;

//Khai báo hằng
#define MAXDIGITS 100 /* maximum length */
#define PLUS 1		  /* positive sign bit */
#define MINUS -1	  /* negative sign bit */

//Khai báo cấu trúc
typedef struct
{
	char digits[MAXDIGITS]; /* the number */
	int signbit;			/* PLUS or MINUS */
	int lastdigit;			/*index of high-order digit*/
} bignum;

// nhap big num
void scan_bignum(bignum &n);

// in big num
void print_bignum(bignum n);

// kiem bignum co hop le ko
int kiemtra(char s[]);

// đưa 1 bignum ve gia trị 0
void initialize_bignum(bignum &n);

// Cộng
void add_bignum(bignum a, bignum b, bignum &c);
bignum add_bignum(bignum a, bignum b);

// Trừ
void subtract_bignum(bignum a, bignum b, bignum &c);
bignum subtract_bignum(bignum a, bignum b);

// bo các số 0 ko cần thiết
void zero_justify(bignum &n);

// so sánh
int compare_bignum(bignum a, bignum b);

void digit_shift(bignum &n, int d);
// nhân
void multiply_bignum(bignum a, bignum b, bignum &c);
bignum multiply_bignum(bignum a, bignum b);

// chia
void divide_bignum(bignum a, bignum b, bignum &c);
bignum divide_bignum(bignum a, bignum b);
bignum mod_bignum(bignum a, bignum b);

// convert int to bignum
void int_to_bignum(int s, bignum &n);
bignum int_to_bignum(int s);

void main()
{
	do
	{
		bignum a, b, c;

		initialize_bignum(a);
		initialize_bignum(b);
		initialize_bignum(c);

		cout << "Nhap a:";
		scan_bignum(a);
		cout << "Nhap b:";
		scan_bignum(b);

		add_bignum(a, b, c);
		cout << "a+b=";
		print_bignum(c);
		cout << endl;
		initialize_bignum(c);

		subtract_bignum(a, b, c);
		cout << "a-b=";
		print_bignum(c);
		cout << endl;
		initialize_bignum(c);

		multiply_bignum(a, b, c);
		cout << "a*b=";
		print_bignum(c);
		cout << endl;
		initialize_bignum(c);

		divide_bignum(a, b, c);
		cout << "a/b=";
		print_bignum(c);
		cout << endl;
		initialize_bignum(c);

		cout << "a%b=";
		print_bignum(mod_bignum(a, b));
		cout << endl;

		cout << "Nhan phim ESC de thoat...\n";
	} while (_getch() != 27);
}

void print_bignum(bignum n)
{
	int i;
	if (n.signbit == MINUS)
		cout << "-";
	for (i = n.lastdigit; i >= 0; i--)
		cout << int(n.digits[i]);
}

int kiemtra(char s[])
{
	//ktra ký tự đầu
	if (s[0] != '-' && !isdigit(s[0]))
		return 0;
	//ktra các ký tự tiếp theo
	int len = strlen(s);
	for (int i = 1; i < len; i++)
		if (!isdigit(s[i]))
			return 0;
	//không phát hiện vi phạm
	return 1;
}

void scan_bignum(bignum &n)
{
	//B1: Nhập chuỗi
	char temp[MAXDIGITS];
	cin.getline(temp, MAXDIGITS);
	//B2: Kiểm tra
	if (!kiemtra(temp))
	{ //không hợp lệ
		//gán bignum = 0
		n.signbit = PLUS;
		n.lastdigit = 0;
		n.digits[0] = 0;
	}
	else
	{ //hợp lệ. B3: chuyển thành số bignum
		//xét 2 trường hợp
		if (temp[0] != '-')
		{ //số dương
			n.signbit = PLUS;
			n.lastdigit = strlen(temp) - 1;
			for (int i = 0; i <= n.lastdigit; i++)
				n.digits[i] = temp[n.lastdigit - i] - 48;
		}
		else
		{ //số âm
			n.signbit = MINUS;
			n.lastdigit = strlen(temp) - 2;
			for (int i = 0; i <= n.lastdigit; i++)
				n.digits[i] = temp[n.lastdigit + 1 - i] - 48;
		}
	}
}

void initialize_bignum(bignum &n)
{
	for (int i = 0; i < MAXDIGITS; i++)
	{
		n.digits[i] = 0;
	}
	n.lastdigit = 0;
	n.signbit = PLUS;
}

void add_bignum(bignum a, bignum b, bignum &c)
{
	int carry; /* carry digit */
	int i;	   /* counter */
	initialize_bignum(c);
	if (a.signbit == b.signbit)
		c.signbit = a.signbit;
	else
	{
		if (a.signbit == MINUS)
		{
			a.signbit = PLUS;
			subtract_bignum(b, a, c);
			a.signbit = MINUS;
		}
		else
		{
			b.signbit = PLUS;
			subtract_bignum(a, b, c);
			b.signbit = MINUS;
		}
		return;
	}
	c.lastdigit = max(a.lastdigit, b.lastdigit) + 1;

	// tránh giá trị rác
	for (int i = a.lastdigit + 1; i <= c.lastdigit; i++)
		a.digits[i] = 0;
	for (int i = b.lastdigit + 1; i <= c.lastdigit; i++)
		b.digits[i] = 0;

	carry = 0;
	for (i = 0; i <= (c.lastdigit); i++)
	{
		c.digits[i] = (char)(carry + a.digits[i] + b.digits[i]) % 10;
		carry = (carry + a.digits[i] + b.digits[i]) / 10;
	}
	zero_justify(c);
}
bignum add_bignum(bignum a, bignum b)
{
	bignum c;
	initialize_bignum(c);
	add_bignum(a, b, c);
	return c;
}

void zero_justify(bignum &n) // 00001123 => 1123
{
	while ((n.lastdigit > 0) && (n.digits[n.lastdigit] == 0))
		n.lastdigit--;
	if ((n.lastdigit == 0) && (n.digits[0] == 0))
		n.signbit = PLUS; /* hack to avoid -0 */
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void subtract_bignum(bignum a, bignum b, bignum &c)
{
	int borrow; /* anything borrowed? */
	int v;		/* placeholder digit */
	int i;		/* counter */
	if ((a.signbit == MINUS) || (b.signbit == MINUS))
	{
		b.signbit = -1 * b.signbit;
		add_bignum(a, b, c);
		b.signbit = -1 * b.signbit;
		return;
	}
	if (compare_bignum(a, b) == PLUS)
	{
		subtract_bignum(b, a, c);
		c.signbit = MINUS;
		return;
	}
	c.lastdigit = max(a.lastdigit, b.lastdigit);

	// tránh giá trị rác
	for (int i = a.lastdigit + 1; i <= c.lastdigit; i++)
		a.digits[i] = 0;
	for (int i = b.lastdigit + 1; i <= c.lastdigit; i++)
		b.digits[i] = 0;

	borrow = 0;
	for (i = 0; i <= (c.lastdigit); i++)
	{
		v = (a.digits[i] - borrow - b.digits[i]);
		if (a.digits[i] > 0)
			borrow = 0;
		if (v < 0)
		{
			v = v + 10;
			borrow = 1;
		}
		c.digits[i] = (char)v % 10;
	}

	zero_justify(c);
}
bignum subtract_bignum(bignum a, bignum b)
{
	bignum c;
	initialize_bignum(c);
	subtract_bignum(a, b, c);
	return c;
}

int compare_bignum(bignum a, bignum b)
{
	// a < b return PLUS
	// a > b return MINUS
	// a = b return 0
	int i; /* counter */
	if ((a.signbit == MINUS) && (b.signbit == PLUS))
		return (PLUS);
	if ((a.signbit == PLUS) && (b.signbit == MINUS))
		return (MINUS);
	if (b.lastdigit > a.lastdigit)
		return (PLUS * a.signbit);
	if (a.lastdigit > b.lastdigit)
		return (MINUS * a.signbit);
	for (i = a.lastdigit; i >= 0; i--)
	{
		if (a.digits[i] > b.digits[i])
			return (MINUS * a.signbit);
		if (b.digits[i] > a.digits[i])
			return (PLUS * a.signbit);
	}
	return (0);
}

void multiply_bignum(bignum a, bignum b, bignum &c)
{
	bignum row; /* represent shifted row */
	bignum tmp; /* placeholder bignum */
	int i, j;	/* counters */
	initialize_bignum(c);
	row = a;
	for (i = 0; i <= b.lastdigit; i++)
	{
		for (j = 1; j <= b.digits[i]; j++)
		{
			add_bignum(c, row, tmp);
			c = tmp;
		}
		digit_shift(row, 1);
	}
	c.signbit = a.signbit * b.signbit;

	zero_justify(c);
}
bignum multiply_bignum(bignum a, bignum b)
{
	bignum c;
	initialize_bignum(c);
	multiply_bignum(a, b, c);
	return c;
}

void digit_shift(bignum &n, int d) /* multiply n by 10ˆd */
{
	int i; /* counter */
	if ((n.lastdigit == 0) && (n.digits[0] == 0))
		return;
	for (i = n.lastdigit; i >= 0; i--)
		n.digits[i + d] = n.digits[i];
	for (i = 0; i < d; i++)
		n.digits[i] = 0;
	n.lastdigit = n.lastdigit + d;
}

void int_to_bignum(int s, bignum &n)
{
	char temp[256];
	_itoa_s(s, temp, 10);
	if (temp[0] != '-')
	{ //số dương
		n.signbit = PLUS;
		n.lastdigit = strlen(temp) - 1;
		for (int i = 0; i <= n.lastdigit; i++)
			n.digits[i] = temp[n.lastdigit - i] - 48;
	}
	else
	{ //số âm
		n.signbit = MINUS;
		n.lastdigit = strlen(temp) - 2;
		for (int i = 0; i <= n.lastdigit; i++)
			n.digits[i] = temp[n.lastdigit + 1 - i] - 48;
	}
}
bignum int_to_bignum(int s)
{
	bignum n;
	int_to_bignum(s, n);
	return n;
}

void divide_bignum(bignum a, bignum b, bignum &c)
{
	bignum row;		  /* represent shifted row */
	bignum tmp;		  /* placeholder bignum */
	int asign, bsign; /* temporary signs */
	int i, j;		  /* counters */
	initialize_bignum(c);
	c.signbit = a.signbit * b.signbit;
	asign = a.signbit;
	bsign = b.signbit;
	a.signbit = PLUS;
	b.signbit = PLUS;
	initialize_bignum(row);
	initialize_bignum(tmp);
	c.lastdigit = a.lastdigit;
	for (i = a.lastdigit; i >= 0; i--)
	{
		digit_shift(row, 1);
		row.digits[0] = a.digits[i];
		c.digits[i] = 0;
		while (compare_bignum(row, b) != PLUS)
		{
			c.digits[i]++;
			subtract_bignum(row, b, tmp);
			row = tmp;
		}
	}
	zero_justify(c);
	a.signbit = asign;
	b.signbit = bsign;
}
bignum divide_bignum(bignum a, bignum b)
{
	bignum c;
	initialize_bignum(c);
	divide_bignum(a, b, c);
	return c;
}

bignum mod_bignum(bignum a, bignum b)
{
	bignum quotient;
	initialize_bignum(quotient);
	quotient = divide_bignum(a, b);
	bignum surplus;
	initialize_bignum(surplus);
	surplus = subtract_bignum(a, quotient);
	return surplus;
}
