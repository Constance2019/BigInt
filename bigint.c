#include "bigint.h"


Bigint::Bigint(u_long data)
{
	if(data == 0)
		big.push_back(0);
	while(data)
	{
		big.push_back(data%10);
		data /= 10;
	}
}

void Bigint::loadData(size_t sz)
{
	//时间作为随机准则,数据看起来真正随机
	srand(time(NULL));
	for(int i=0;i<sz;i++)
	{
		big.push_back(rand()%10);
	}
}

void Bigint::showData()const
{
	for(int i=size();i>0;--i)
		cout<<(int)big[i];
	cout<<endl;
}

size_t Bigint::size()const
{
	return big.size();
}

void Bigint::push_back(const u_char &v)
{
	big.push_back(v);
}

void Bigint::clear()
{
	big.clear();
}

void Bigint::clear_head_zero()
{
	if(*this == 0)
		return;
	else
	{
		while(big.back() == 0)
			big.pop_back();
	}
}

u_char& Bigint::back()
{
	return big.back();
}

void Bigint::pop_back()
{
	big.pop_back();
}


////////////重载运算符
void Bigint::operator=(u_long data)
{
	clear();  //先清除原来的数据
	if(data == 0)
		big.push_back(0);
	else
	{
		while(data)
		{
			big.push_back(data%10);
			data/=10;
		}
	}
}

u_char& Bigint::operator[](int i)const
{
	return big[i];
}

bool Bigint::operator>=(const Bigint& bt1)const
{
	if(size() > bt1.size()) 
	{
		return true;
	}
	if(size() < bt1.size())
	{
		return false;
	}
	else
	{
		u_long i=size();
		while(i>0)
		{
			if((*this)[i] > bt1[i])
				return true;
			if((*this)[i] < bt1[i])
				return false;
			i--;
		}
	}
	return true;
}

bool Bigint::operator<(const Bigint& bt1)const
{
	return !((*this) >= bt1);
}

bool Bigint::operator<=(const Bigint &bt)const
{
	if(size() > bt.size())
		return false;
	else if(size() < bt.size())
		return true;
	else
	{
		u_long i=size();
		while(i>0)
		{
			if((*this)[i] < bt[i])
				return true;
			else if((*this)[i] > bt[i])
				return false;
			i--;
		}
	}	
	return true;
}

bool Bigint::operator>(const Bigint &bt)const
{
	return !((*this)<=bt);
}

bool Bigint::operator==(const Bigint &bt)const
{
	if(size() != bt.size())
		return false;
	u_long i =1;
	while(i <= size())
	{
		if((*this)[i] != bt[i])
			return false;
		i++;
	}
	return true;
}

bool Bigint::operator!=(const Bigint& bt)const
{
	return !((*this)==bt);
}

ostream& operator<<(ostream& out,const Bigint &bt)
{
	for(int i=bt.size();i>0;i--)
		out<<(int)bt[i];    //重载方括号==bt[i]
	return out;
}

Bigint& Bigint::operator+=(const Bigint &bt)
{
	u_long i,j;
	i =j =1;
	u_char sign=0;           //sign初始化
	while(i<=size() && j<=bt.size())
	{
		big[i] = Add_Item(big[i], bt[j], sign);
		i++;
		j++;
	}
	while(i<=size() && sign>0)  //第一个大整数比第二个大整数位数长，并且有进位，就加进位
	{
		big[i] =Add_Item(big[i], 0, sign);  //////big[i]==(*this)[i]==this->big[i]
		i++;
	}
	u_char sum;
	while(j<=bt.size())
	{
		sum = Add_Item(0, bt[j], sign);
		big.push_back(sum);
		j++;
	}
	if(sign>0)
		big.push_back(sign);
	return *this;
}

Bigint& Bigint::operator++()
{
	u_long i = 1;
	u_char sign =1;
	while(i<=size() && sign>0)
	{
		big[i] = Add_Item(big[i],0,sign);
		i++;
	}
	if(sign > 0)
		big.push_back(sign);
	return (*this);
}

Bigint Bigint::operator++(int)
{
	Bigint temp = (*this);
	++(*this);
	return temp;
}

Bigint& Bigint::operator--()
{
	assert((*this) >= 1);
	u_long i =1;
	u_char sign =1;
	while(i<=size() && sign>0)
	{
		big[i] = Sub_Item(big[i], 0, sign);
		i++;
	}
	return *this;
}

Bigint Bigint::operator--(int)
{
	Bigint temp=(*this);
	--(*this);
	return temp;
}


Bigint& Bigint::operator-=(const Bigint &bt)
{
	assert((*this)>=bt);     //要实现减的条件是被减数大于等于减数
	u_long i, j;
	i = j= 1;
	u_char sign = 0;
	while(i<=size() && j<=bt.size())
	{
		big[i] = Sub_Item(big[i], bt[j], sign); 
		i++;
		j++;
	}
	while(i<=size() && sign>0)
	{
		big[i] = Sub_Item(big[i], 0, sign);
		i++;
	}
	return *this;
}

Bigint Bigint::operator+(const Bigint &bt)
{
	Bigint tmp;
	tmp.clear();
	Add(tmp, *this, bt);
	return tmp;
}

Bigint Bigint::operator-(const Bigint &bt)
{
	Bigint tmp;
	tmp.clear();
	Sub(tmp, *this, bt);
	return tmp;
}

Bigint Bigint::operator*(const Bigint &bt)
{
	Bigint tmp;
	tmp.clear();
	Mul(tmp, *this, bt);
	return tmp;
}

Bigint Bigint::operator/(const Bigint &bt)
{
	Bigint tmp;
	tmp.clear();
	Div(tmp, *this, bt);
	return tmp;
}


u_char Bigint::Add_Item(u_char a,u_char b,u_char &sign)
{
	u_char sum =a+b+sign;
	if(sum >= 10)
	{
		sum -= 10;
		sign = 1;
	}
	else 
		sign = 0;
	return sum;
}

void Bigint::Add(Bigint &bt,const Bigint& bt1,const Bigint& bt2)
{
	u_long i,j;
	i= j= 1;
	u_char sum,sign =0;
	while(i<=bt1.size() && j<=bt2.size())
	{
		sum = Add_Item(bt1[i], bt2[j], sign);
		bt.push_back(sum);
		i++;
		j++;
	}
	while(i<=bt1.size())
	{
		sum = Add_Item(bt1[i], 0, sign);
		bt.push_back(sum);
		i++;
	}
	while(j<=bt2.size())
	{
		sum = Add_Item(0, bt2[j], sign);
		bt.push_back(sum);
		j++;
	}
	if(sign > 0)
		bt.push_back(sign);
}

u_char Bigint::Sub_Item(u_char a, u_char b, u_char &sign)
{
	u_char sub;
	if(a >= b+sign)
	{
		sub = a-b-sign;
		sign = 0;
	}
	else
	{
		sub = a+10-b-sign;
		sign = 1;
	}
	return sub;
}

void Bigint::Sub(Bigint &bt,const Bigint &bt1,const Bigint &bt2)
{
	bt.clear();
	u_long i,j;
	i = j =1;
	u_char sub,sign=0;
	assert(bt1 >= bt2);
	if(bt1 == bt2)
	{
		bt = 0;       //=运算符重载
		return;
	}
	while(i<=bt1.size() && j<=bt2.size())
	{
		//if(bt1[i] >= (bt2[j]+sign))  //=========> bt1[i]-sign >= bt2[j]
		//sub = bt1[i]-bt2[j]-sign;   //没有借位
		sub = Sub_Item(bt1[i], bt2[j],sign);
		bt.push_back(sub);
		i++;
		j++;
	}
	while(i<=bt1.size())
	{
		sub = Sub_Item(bt1[i],0,sign);
		bt.push_back(sub);
		i++;
	}
	bt.clear_head_zero();
}


void Bigint::Mul_Item(Bigint &bt,const Bigint &bt1, u_char x)
{
	u_long i =1;
	u_char mul,sign = 0;
	while(i<=bt1.size())
	{
		mul = bt1[i] * x +sign;
		bt.push_back(mul%10);
		sign = mul/10;
		i++;
	}
	if(sign>0)
		bt.push_back(sign);
}

void Bigint::AddMove(Bigint& bt1,const Bigint& bt2,u_long pos)
{
	u_long i,j;
	i=pos;
	j=1;
	u_char sign=0;
	while(i<=bt1.size() && j<=bt2.size())
	{  
		bt1[i] = Add_Item(bt1[i], bt2[j], sign);
		i++;
		j++;
	}
	while(i<=bt1.size() && sign>0)
	{
		bt1[i]  = Add_Item(bt1[i], 0, sign);
		i++;
	}
	u_char sum;
	while(j<=bt2.size())
	{
		sum = Add_Item(0, bt2[j], sign);
		bt1.push_back(sum);
		j++;
	}
	if(sign>0)
		bt1.push_back(sign);
}


void Bigint::Mul(Bigint& bt,const Bigint& bt1,const Bigint& bt2)
{
	bt.clear();
	Bigint tmp;
	tmp.clear();
	/*Bigint i=bt2;
	while(i>0)   //效率低
	{
		bt += bt1;
		i--;
	}*/
	for(u_long i=1; i<=bt2.size();++i)
	{
		Mul_Item(tmp,bt1,bt2[i]);  //按位想成
		AddMove(bt, tmp, i);       //错位相加
		tmp.clear();
	}

}



void Bigint::Div(Bigint& bt,const Bigint& bt1,const Bigint& bt2)
{
	if(bt1 < bt2)
		bt = 0;
	else if(bt1 == bt2)
		bt = 1;
	else
	{
		bt = 0;
		Bigint tmp = bt1;
		while(tmp >= bt2)   
		{
			tmp -= bt2;			//重载-=
			++bt;
			tmp.clear_head_zero();
		}
	}
}



