#include <iostream>
using namespace std;
#include "bigint.h"


//测试函数功能
void main()
{
	Bigint bt,bt1(1233431333),bt2(14567832);
	cout<<"bt1="<<bt1<<endl;
	cout<<"bt2="<<bt2<<endl;
	bt = bt1 + bt2;
	cout<<"bt1+bt2="<<bt<<endl;
	bt = bt1 - bt2;
	cout<<"bt1-bt2="<<bt<<endl;
	bt = bt1 * bt2;
	cout<<"bt1*bt2="<<bt<<endl;
	bt = bt1 / bt2;
	cout<<"bt1/bt2="<<bt<<endl;
}
/*
void main()
{
	Bigint bt,bt1(10000000),bt2(8);
	Bigint::Div(bt,bt1,bt2);
	cout<<bt<<endl;
}
/*
void main()
{
	Bigint bt,bt1(21452626),bt2(1);
	bt1 -= bt2;
	cout<<bt1<<endl;
}
/*
void main()
{
	Bigint bt,bt1,bt2;
	bt1.clear();
	bt2.clear();
	bt.clear();
	bt1.loadData(10);
	cout<<"bt1="<<bt1<<endl;
	bt2.loadData(8);
	cout<<"bt2="<<bt2<<endl;
	Bigint::Mul(bt,bt1,bt2);
	cout<<"bt="<<bt<<endl;
}
/*
void main()
{
	Bigint bt,bt1(74),bt2(8);
	Bigint::Mul(bt,bt1,bt2);
	cout<<bt<<endl;
}
/*

/*
void main()
{
	Bigint i=2;
	Bigint v=i--;
	cout<<i<<endl;   //重载++(--)运算符
	cout<<v<<endl;
}
/*
void main()
{
	Bigint bt,bt1(1010),bt2(1);
	Bigint::Sub(bt,bt1,bt2);
	cout<<bt<<endl;
}
/*
int main()
{
	Bigint bt,bt1(2789920),bt2(2287654);
	cout<<bt<<" "<<bt1<<" "<<bt2<<endl;  //重载输出运算符
	//bt = bt1 + bt2;
	return 0;
}
/*
int main()
{
	Bigint bt,bt1(115618),bt2(4618);
	bt1.showData();
	bt2.showData();
	Bigint::Sub(bt,bt1,bt2);
	bt.showData();
	return 0;
}
/*
int main()
{
	Bigint bt,bt1,bt2;
	bt1.loadData(10);
	//cout<<bt1.size()<<endl;
	Sleep(1000);  //引入windows.h
	bt2.loadData(10);
	cout<<"bt1=";
	bt1.showData();
	cout<<"bt2=";
	bt2.showData();
	Bigint::Add(bt,bt1,bt2);
	cout<<"bt=";
	bt.showData();
	return 0;
}
*/
