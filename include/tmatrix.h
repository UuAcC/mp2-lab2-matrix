// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef TDynamicMatrix_H
#define TDynamicMatrix_H

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz == 0)
			throw out_of_range("Vector size should be greater than zero");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v) : sz(v.sz)
	{
		pMem = new T[sz];
		memcpy(pMem, v.pMem, sz * sizeof(T));
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == *v) return *this;
		delete[] pMem;
		sz = v.sz;
		pMem = new T[sz];
		memcpy(pMem, v.pMem, sz * sizeof(T));
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		if (std::move(*this) == v)
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index should be between 0 and vector size - 1");
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return this->at(ind);
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index should be between 0 and vector size - 1");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		this->at(ind);
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz) return false;
		for (size_t i = 0; i < sz; i++)
		{
			if (this->at(i) != v[i]) return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector res = new TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] += val; }
		return res;
	}
	TDynamicVector operator-(T val)
	{
		TDynamicVector res = new TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] -= val; }
		return res;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector res = new TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] *= val; }
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz) throw - 1;
		TDynamicVector res = new TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] += v[i]; }
		return res;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz) throw - 1;
		TDynamicVector res = new TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] -= v[i]; }
		return res;
	}
	T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
	{
		T res = 0;
		size_t size = sz;
		for (size_t i = 0; i < size; i++) {
			res += this->at(i) * v[i];
		}
		return res;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};
// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return pMem == m.pMem;
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix res = new TDynamicMatrix(*this);
		return res * val;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		size_t size = sz;
		TDynamicVector<T> res = new TDynamicVector<T>(size);
		for (size_t i = 0; i < size; i++) {
			res[i] = this->operator[](i) * v;
		}
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		return *this + m;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		return *this - m;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
	}
};

#endif
