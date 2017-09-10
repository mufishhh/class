// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<ctime>
#include<sstream>
#include<fstream>
#include<cstdlib>
#pragma warning(disable:4996)

using namespace std;

int sudoku[10][10];
bool find(int i, int j)//搜索(i,j)可以存储的数字
{
	int vi[10];
	for (int i1 = 1; i1 <= 9; ++i1)
		vi[i1] = i1;
	random_shuffle(&(vi[1]), &(vi[10]));//vi一维数组打乱1-9

	for (int s = 1; s <= 9; s++)//循环数组取数字
	{
		int k = vi[s];//取k为数组中第一位数
		bool sign = true;//sign标记能否将k放在(i,j)处

		for (int m = 1; m < i; m++)
			if (sudoku[m][j] == k)//检查同一列是否出现过数字k
			{
				sign = false;
				break;
			}

		if (sign == true)
		{
			for (int n = 1; n < j; n++)
				if (sudoku[i][n] == k)//检查同一行是否出现过数字k
				{
					sign = false;
					break;
				}

		}

		if (sign == true)
		{
			int imax = (i / 3) * 3 + 3;//(i,j)所在的3x3小方格的最大行数
			int jmax = (j / 3) * 3 + 3;//(i,j)所在的3x3小方格的最大列数

			if (i % 3 == 0)
				imax = i;
			if (j % 3 == 0)
				jmax = j;

			for (int p = imax - 2; p <= imax; p++)//检查3x3小方格
			{
				if (sign == false)
					break;

				for (int q = jmax - 2; q <= jmax; q++)
					if (sudoku[p][q] == k)
					{
						sign = false;
						break;
					}
			}
		}

		if (sign == true)
		{
			sudoku[i][j] = k;
			if (j < 9)
			{
				if (find(i, j + 1) == true)//搜索本行右边的位置
					return true;
			}
			else
			{
				if (i < 9)
				{
					if (find(i + 1, 1) == true)//搜索下一行
						return true;
				}
				else
					return true;//i>=9，j>=9，搜索结束

			}
			sudoku[i][j] = 0;//找不到要清0
		}
	}
	return false;//本位置1-9都不能填，返回上一步
}

bool isNUM(string str)
	{
		stringstream sin(str);
		double d;
		char c;
		if (!(sin >> d))
		{
			return false;
		}
		if (sin >> c)
		{
			return false;
		}
		return true;
	}
int main(int argc, char*argv[])
{
	//ofstream fout;
	//fout.open("./sudoku.txt");
	string p = argv[1];
	if (argc != 3)
	{
		cout << "Please input correct order!!!!" << endl;
	}
	else
	{
		if (p == "-c")
		{
			string q = argv[2];
			if (isNUM(q))
			{
				int r = atoi(q.c_str());
				if (r == 0)
				{
					cout << "error" << endl;
					return 0;
				}
				srand(unsigned(time(NULL)));//循环体内短时间取到的随机数种子几乎是一样的 所以要放在循环体外不能多次取
                freopen("./sudoku.txt", "w", stdout);
				for (int x = 1; x <= r; x++)
				{
					for (int i = 1; i <= 9; i++)//初始化矩阵
					{
						for (int j = 1; j <= 9; j++)
							sudoku[i][j] = 0;
					}
					sudoku[1][1] = 4;
					find(1, 2);
					
					for (int i = 1; i <= 9; i++)
					{
						for (int j = 1; j <= 9; j++)
						{
							char num = '0' + sudoku[i][j];
							putchar(num);
							putchar(' ');
						}
						puts("");
					}
					puts("");
				}

			}
			else
				cout << "Please input an integer!" << endl;
		}
		else
			cout << "Please input correct order!" << endl;
	}


	//fout.close();
	return 0;
}

