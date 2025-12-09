#include<iostream>
using namespace std;
#define max 10
#define bookname 20
#define username 20
#define record 100
typedef struct {
	char Name[bookname];
	int Quantity;
	bool YN1;
	bool YN2;
}Book;

typedef struct {
	char Name[username];
	int BookName;
	bool YN1;
}Person;

typedef struct {
	char Name[username];
	char BookName[bookname];
	bool YN1;
}Record;

Book Library[max] = {0};
Person Users[max] = {0};
Record History[record] = { 0 };

//添加图书
void AddBook(void)
{
	int i,j;
	bool yn = 0;//是否拥有空位
	for (i = 0; i < max; i++)
		if (Library[i].YN1 == 0)
		{
			yn = 1;
			break;
		}
	if (yn == 0)
	{
		cout << "图书馆已无空位" ;
		return;
	}
	else
	{
		Library[i].YN1= 1;
		cout << "请输入要添加的书的名字（英文）:";
		cin >> Library[i].Name;
		cout << "请输入要添加的书的数量:";
		cin >> j;
		Library[i].Quantity+=j;
		cout << "添加成功" << endl;
	}
}

//显示全部图书
void DisplayAllBooks(void)
{
	int i;
	bool yn = 0;
	for (i = 0; i < max; i++)
		if (Library[i].YN1 == 0)
		{
			yn = 1;
			break;
		}
	for (int j = 0; j < i; j++)
	{
		cout << "书名：" << Library[j].Name << "  数量：" << Library[j].Quantity << endl;
	}
}

//搜索图书
void SearchForBooks(void)
{
	int i = 0, j = 0, k = 0, m = 0, n = 0, z = 0;
	char a[bookname] = { 0 };
	cout << "请输入要搜索的书名：";
	cin >> a;
	while (a[n] != '\0')
		n++;
	for (i = 0; i < max; i++)
	{
		m = 0;
		k = 0;
		for (j = 0; j < bookname; j++)
		{
			if (Library[i].Name[j] == a[k])
			{
				k++;
				m++;
			}
			else
			{
				if (m != 0)
					break;
				else
					continue;
			}
			if (m == n)
			{
				cout << "书名：" << Library[i].Name << "  数量：" << Library[i].Quantity << endl;
				z = 1;
			}
		}
	}
	if (z == 0)
		cout << "未查询到有关书籍";
}

//添加用户
void AddUser(void)
{
	int i;
	bool yn = 0;//是否拥有空位
	for (i = 0; i < max; i++)
		if (Users[i].YN1 == 0)
		{
			yn = 1;
			break;
		}
	if (yn == 0)
	{
		cout << "已无可注册用户";
		return;
	}
	else
	{
		Users[i].YN1 = 1;
		cout << "请输入用户名：";
		cin >> Users[i].Name;
		cout << "添加成功" << endl;
	}
}

//借阅图书
void BorrowBooks(void)
{
	int i = 0, j = 0, z = 0, y = 0, n = 0, m = 0;
	char a[username] = { 0 },b[bookname] = { 0 };
	cout << "请输入用户名：";
	cin >> a;
	for (i = 0; i < max; i++)
	{
		int q = 0;
		z = 0;
		while(a[q]!='\0'|| Users[i].Name[q]!='\0')
		{
			if (a[q] != Users[i].Name[q])
			{
				z = 1;
				break;
			}
			q++;
		}
		if (z == 0)
			break;
	}
	if (z == 1)
	{
		cout << "此用户不存在" << endl;
		return;
	}
	cout << "请输入书籍名：";
	cin >> b;
	for (j = 0; j < max; j++)
	{
		int q = 0;
		y = 0;
		while (b[q] != '\0' || Library[i].Name[q] != '\0')
		{
			if (b[q] != Library[j].Name[q])
			{
				y = 1;
				break;
			}
			q++;
		}
		if (y == 0)
			break;
	}
	if (y == 1 || j == max)
	{
		cout << "此书籍不存在" << endl;
		return;
	}
	else if(Library[j].Quantity==0)
	{
		cout << "此书籍无库存" << endl;
		return;
	}

	int p = 0;
	if (Users[i].BookName == record)
	{
		cout << "此用户借阅书籍已达上限"<<endl;
		return;
	}
	Library[j].Quantity--;
	Users[i].BookName++;
	for (p = 0; p < max; p++)
		if (History[p].YN1 == 0)
		{
			History[p].YN1 = 1;
			break;
		}
	for (int e = 0; e < username; e++)
		History[p].Name[e] = a[e];
	for (int e = 0; e < bookname; e++)
	{
		History[p].BookName[e] = b[e];
	}
	cout << "借书成功！" << endl;
}

//归还图书
void ReturnBooks(void)
{
	int i = 0, y = 0, z = 0, k = 0, d = 0;
	char a[username] = { 0 }, b[bookname] = { 0 };
	cout << "请输入用户名：";
	cin >> a;
	cout << "请输入要归还的书籍名：";
	cin >> b;
	for (i = 0;i<record ; i++)
	{
		int q = 0;
		z = 0;
		while (a[q] != '\0' || History[i].Name[q] != '\0')
		{
			if ((a[q] != History[i].Name[q])||(b[q]!=History[i].BookName[q]))
			{
				z = 1;
				break;
			}
			q++;
		}
		if (z == 0)
			break;
	}
	if (z == 1)
	{
		cout << "无此借阅记录" << endl;
		return;
	}

	for (k = 0; k < max; k++)
	{
		int q = 0;
		z = 0;
		while (a[q] != '\0' || Users[k].Name[q] != '\0')
		{
			if (a[q] != Users[k].Name[q])
			{
				z = 1;
				break;
			}
			q++;
		}
		if (z == 0)
			break;
	}

	History[i] = { 0 };
	for (int j = 0; j < record; j++)
	{
		if (History[j].Name[0] == '\0')
		{
			for (int e = 0; e < username; e++)
			{
				History[j].Name[e] = History[j + 1].Name[e];
				History[j].YN1 = History[j + 1].YN1;
			}
			for (int e = 0; e < bookname; e++)
				History[j].BookName[e] = History[j + 1].BookName[e];
			History[j + 1] = { 0 };
		}
	}

	for (d = 0; d < max; d++)
	{
		int q = 0;
		z = 0;
		while (a[q] != '\0' || Library[d].Name[q] != '\0')
		{
			if (a[q] != Library[d].Name[q])
			{
				z = 1;
				break;
			}
			q++;
		}
		if (z == 0)
			break;
	}

	Library[d].Quantity++;
	Users[i].BookName--;
	cout << "还书成功" << endl;

}

//查看借阅记录
//查看用户的借阅记录
void ViewBorrowingRecords1(void)
{
	int i = 0, z = 0;
	char a[username];
	cout << "请输入用户名：";
	cin >> a;
	cout << "用户名          书籍名"<<endl;
	for (i = 0; i < max; i++)
	{
		int q = 0;
		z = 0;
		while (a[q] != '\0' || History[i].Name[q] != '\0')
		{
			if (a[q] != History[i].Name[q])
			{
				z = 1;
				break;
			}
			q++;
		}
		if (z == 0)
		{
			cout << History[i].Name << "          " << History[i].BookName<<endl;
		}
	}

}
//查看当前的借阅情况
void ViewBorrowingRecords2(void)
{
	cout << "用户名          书籍名" << endl;
	for(int i=0;i<max;i++)
		if(History[i].Name[0]!='\0')
		cout << History[i].Name << "          " << History[i].BookName << endl;
}

void ViewBorrowingRecords(void)
{
	int i;
	cout << "1.查看用户的借阅记录" << endl;
	cout << "2.查看当前的借阅情况" << endl;
	cout << "3.退出系统" << endl;
	cin >> i;
	if (i > 3 || i < 1)
	{
		cout << "输入不合法" << endl;
		return;
	}
	switch (i)
	{
	case 1:ViewBorrowingRecords1();
		break;
	case 2:ViewBorrowingRecords2();
		break;
	case 3:return;
	}

}

	int main()
{
	int i;
	while (1)
	{
		cout << "请选择：" << endl;
		cout << "1.添加图书" << endl;
		cout << "2.显示全部图书" << endl;
		cout << "3.搜索图书" << endl;
		cout << "4.添加用户" << endl;
		cout << "5.借阅图书" << endl;
		cout << "6.归还图书" << endl;
		cout << "7.查看借阅记录" << endl;
		cout << "8.退出系统" << endl;
		cin >> i;
		if (i > 8 || i < 1)
		{
			cout << "输入不合法" << endl;
			continue;
		}
		switch (i) 
		{
		case 1:AddBook();
			break;
		case 2:DisplayAllBooks();
			break;
		case 3:SearchForBooks();
			break;
		case 4:AddUser();
			break;
		case 5:BorrowBooks();
			break;
		case 6:ReturnBooks();
			break;
		case 7:ViewBorrowingRecords();
			break;
		case 8:return 0;
		}
	}
	return 0;
}