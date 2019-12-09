#pragma once
#include "vector.h"
#include<iostream>
#include "Exception.h"

using namespace std;

template <class T>
class Matrix
{
	int size;
	vector<T>* mas;

public:
	Matrix(int _size);
	Matrix();
	~Matrix();
	int Getsize();
	Matrix<T> operator +(const Matrix<T>& w);
	Matrix(const Matrix<T>& v);
	friend ostream& operator <<(ostream& os, const Matrix<T>& v)
	{

		for (int i = 0; i < v.size; i++)
		{
			os << v.mas[i] << endl;
		}

		return os;
	}
	friend istream& operator >>(istream& is, Matrix<T>& v)
	{
		for (int i = 0; i < v.size; i++)
		{
			is >> v.mas[i];
		}
		return is;
	}
};

template <class T>

Matrix<T>::Matrix(int _size)
{
	size = _size;
	mas = new vector<T>[size];
	vector<T> v(_size);
	for (int i = 0; i < size; i++)
	{
		mas[i] = v;
	}
}

template <class T>
Matrix<T>::Matrix()
{
	size = 5;
	mas = new vector<T>[size];

}
template <class T>
Matrix<T>::~Matrix()
{
	delete[]mas;
}

template <class T>
int Matrix<T>::Getsize()
{
	return size;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
	size = m.size;
	mas = new vector<T>[size];
	for (int i = 0; i < size; i++)
	{
		mas[i] = m.mas[i];
	}
}
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& w)
{
	if (size == w.size)
	{
		Matrix<T> res(w);
		for (int i = 0; i < size; i++)
		{
			res.mas[i] = mas[i] + w.mas[i];
		}
		return res;
	}
	else
	{
		throw Exception(__LINE__, __FILE__, __FUNCTION__, "Different array sizes");
	}
}