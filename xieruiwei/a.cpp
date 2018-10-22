// 平均值.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
using namespace std;

int main(void)
{
	int n=0;
	double x=0,a[10];
	for(int i=0;i<10;i++)
	{
		cin >> a[i];
		x = x + a[i];
	}
	x = x / 10;
	for(int i=0;i<10;i++)
	{
		if(a[i]>x)
			n++;
	}
	cout << n;
	return 0;
}

