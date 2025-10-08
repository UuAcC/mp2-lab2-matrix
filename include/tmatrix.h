// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef TDynamicMatrix_H
#define TDynamicMatrix_H

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
//typedef double T;
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
		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("Vector size should be equal or less than maximum");
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
		for (size_t i = 0; i < sz; i++)
			pMem[i] = v.pMem[i];
	}
	TDynamicVector(TDynamicVector&& v) noexcept
		: sz(v.sz), pMem(v.pMem)
	{
		v.sz = 0;
		v.pMem = nullptr;
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (*this == v) return *this;
		delete[] pMem;
		sz = v.sz; pMem = new T[sz];
		for (size_t i = 0; i < sz; i++)
			pMem[i] = v.pMem[i];
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		if (this == &v) return *this;
		delete[] pMem;
		sz = v.sz;
		pMem = v.pMem;
		v.sz = 0;
		v.pMem = nullptr;
		return *this;
	}

	size_t size() const noexcept { return sz; }
	T* get_pMem() noexcept { return this->pMem; }

	// индексация
	T& operator[](size_t ind)
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index should be between 0 and vector size - 1");
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index should be between 0 and vector size - 1");
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index should be between 0 and vector size - 1");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind < 0 || ind >= sz) throw out_of_range("Index should be between 0 and vector size - 1");
		return pMem[ind];
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
		TDynamicVector res = TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] = res[i] + val; }
		return res;
	}
	TDynamicVector operator-(T val)
	{
		TDynamicVector res = TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] = res[i] - val; }
		return res;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector res = TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] = res[i] * val; }
		return res;
	}

	TDynamicVector operator+=(T val) { return *this + val; }
	TDynamicVector operator-=(T val) { return *this - val; }
	TDynamicVector operator*=(T val) { return *this * val; }

	friend TDynamicVector operator*(T val, const TDynamicVector& v) 
	{ 
		TDynamicVector res = TDynamicVector(v);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] = res[i] * val; }
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz) 
			throw invalid_argument("Vector sizes must be equal");
		TDynamicVector res = TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] = res[i] + v[i]; }
		return res;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz) 
			throw invalid_argument("Vector sizes must be equal");
		TDynamicVector res = TDynamicVector(*this);
		size_t size = res.sz;
		for (size_t i = 0; i < size; i++) { res[i] = res[i] - v[i]; }
		return res;
	}
	T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
	{
		if (sz != v.sz) 
			throw invalid_argument("Vector sizes must be equal");
		T res = 0;
		size_t size = sz;
		for (size_t i = 0; i < size; i++)
			res = res + this->at(i) * v[i];
		return res;
	}

	TDynamicVector operator+=(const TDynamicVector& v) { return *this + v; }
	TDynamicVector operator-=(const TDynamicVector& v) { return *this - v; }
	T operator*=(const TDynamicVector& v) { return *this * v; }

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
//typedef double T;
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s > MAX_MATRIX_SIZE)
			throw out_of_range("Matrix size should be equal or less than maximum");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];
	using TDynamicVector<TDynamicVector<T>>::size;
	using TDynamicVector<TDynamicVector<T>>::get_pMem;

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (sz != m.sz) return false;
		for (size_t i = 0; i < sz; i++)
			if ((*this)[i] != m[i]) return false;
		return true;
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix res(*this);
		return res * val;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		size_t size = sz;
		TDynamicVector<T> res(size);
		for (size_t i = 0; i < size; i++)
			res[i] = (*this)[i] * v;
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz) throw invalid_argument("Matrix sizes must be equal");
		TDynamicMatrix res(sz);
		for (size_t i = 0; i < sz; i++) {
			res[i] = (*this)[i] + m[i];
		}
		return res;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz) throw invalid_argument("Matrix sizes must be equal");
		TDynamicMatrix res(sz);
		for (size_t i = 0; i < sz; i++) {
			res[i] = (*this)[i] - m[i];
		}
		return res;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw invalid_argument("Matrix sizes must be equal");

		TDynamicMatrix res(sz);
		const size_t n = sz;
		for (size_t i = 0; i < n; ++i) {
			T* c_row = &res[i][0];
			for (size_t j = 0; j < n; ++j)
				c_row[j] = T();
			for (size_t k = 0; k < n; ++k) {
				T a_val = (*this)[i][k];
				const T* b_row = &m[k][0];
				for (size_t j = 0; j < n; ++j)
					c_row[j] += a_val * b_row[j];
			}
		}
		return res;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++) {
			for (size_t j = 0; j < v.sz; j++) {
				istr >> v[i][j];
			}
		}
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		ostr << "Matrix size: " << v.sz << ";\nMatrix itself:\n";
		for (size_t i = 0; i < v.sz; i++) {
			ostr << "( ";
			for (size_t j = 0; j < v.sz; j++) {
				ostr << v[i][j] << ' ';
			}
			ostr << ")\n";
		}
		return ostr;
	}
};

#endif
