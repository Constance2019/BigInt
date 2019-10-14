#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include "utili.h"
#define SEQLIST_DEFAULT_SIZE 20
#define SEQLIST_INC_SIZE 10
template<class T>
class Seqlist
{
public:
	Seqlist(int sz = SEQLIST_DEFAULT_SIZE )
	{
		capacity = sz >SEQLIST_DEFAULT_SIZE ? sz:SEQLIST_DEFAULT_SIZE;
		base = new T[capacity+1];   
		len = 0;
	}
	Seqlist(const Seqlist<T>& sq)
	{
		base = new T[sizeof(T)*(sq.capacity+1)];  //new T[sq.capacity+1];
		assert(base != NULL);
		memcpy(base,sq.base,sizeof(T)*(sq.capacity+1));
		capacity = sq.capacity;
		len = sq.len;
	}
	Seqlist& operator=(const Seqlist<T> &sq)
	{
		if(this != &sq)
		{
			delete []base;
			base = new T[sizeof(T)*(sq.capacity+1)];
			assert(base != NULL);
			memcpy(base, sq.base, sizeof(T)*(sq.capacity+1));
			capacity = sq.capacity;
			len =sq.len;
		}
		return *this;
	}
	~Seqlist()
	{
		delete []base;
		base = NULL;
		capacity = 0;
	}
public:
	bool isfull()const
	{ return len >= capacity; }
	bool isempty()const
	{ return len==0?true:false; }
public:
	void push_back(const T &v);
	void push_front(const T &v);
	size_t length()const;
	size_t size()const
	{ return len; }
	void clear()
	{ len=0; }
	size_t Capacity()const;
	void pop_back()
	{ --len; }
	void pop_front();
	T& back()
	{ return base[len]; }
	T& front();
	void sort();
	void reverse();
	void erase(const T &key);
	int find(const T &key);
	T& operator[](int sz)const
	{
		assert(sz>=0 && sz<=len);//有效位置
		return base[sz];
	}
private:
	T* base;
	size_t capacity;
	size_t len;
	bool Inc(int size=SEQLIST_INC_SIZE);
};

template<class T>
bool Seqlist<T>::Inc(int size)
{
	int inc_size = size>SEQLIST_INC_SIZE ? size:SEQLIST_INC_SIZE;
	T *new_base = new T[capacity+inc_size+1];
	 //assert(new_base != NULL);
	if(new_base == NULL) return false;
	memcpy(new_base,base,sizeof(T)*(capacity+1));
	delete []base; 
	base = new_base;
	capacity += inc_size;
	return true;
}


template<class T>
void Seqlist<T>::push_back(const T &v)
{
	if(isfull() && !Inc())
	{
		cout<<"Seqlist memory out of"<<endl;
		exit(1);
	}
	base[++len] =v;
}


#endif
