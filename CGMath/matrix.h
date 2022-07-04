#pragma once
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <initializer_list>
#include "utils.h"
#include "vector.h"

namespace cgm {

	template <typename T, int nrows, int ncols>
	struct Matrix
	{
		// Attributes
		static const int size = nrows * ncols;
		T data[size];

		// Constructors
		Matrix() : data{ } { }

		Matrix(T value) : data{ }
		{
			for (int i = 0; i < size; i++)
			{
				data[i] = value;
			}
		}

		Matrix(std::initializer_list<T> init_list) : data{ }
		{
			assert(init_list.size() == size);

			int i = 0;
			for (const auto value : init_list)
			{
				data[i] = value;
				++i;
			}
		}

		Matrix(std::initializer_list<std::initializer_list<T>> init_list) :
			data{}
		{
			assert(init_list.size() == nrows);

			int i = 0, j = 0;
			for (const auto l : init_list)
			{
				assert(l.size() == ncols);
				for (const auto v : l)
				{
					data[i * ncols + j] = v;
					++j;
				}
				j = 0;
				++i;
			}
		}

		// Destructor
		~Matrix() { }

		// Operators
		// Access operators
		T& operator()(int row, int col)
		{
			return data[row * ncols + col];
		}

		T operator()(int row, int col) const
		{
			return data[row * ncols + col];
		}

		T* row(int idx) const
		{
			assert(idx < nrows);
			T row[ncols]{ };
			std::copy(data + (idx * ncols), data + (idx * ncols) + ncols, row);
			return row;
		}

		T* column(int idx) const
		{
			assert(idx < ncols);
			T column[ncols]{ };
			for (int i = 0; i < nrows; i++)
			{
				column[i] = data[i * ncols + idx];
			}
			return column;
		}

		Vector<T, ncols> row2Vec(int idx) const
		{
			assert(idx < nrows);
			Vector<T, ncols> vec;
			for (int col = 0; col < ncols; col++)
			{
				vec[col] = (*this)(idx, col);
			}
			return vec;
		}

		Vector<T, nrows> col2Vec(int idx) const
		{
			assert(idx < ncols);
			Vector<T, nrows> vec;
			for (int row = 0; row < nrows; row++)
			{
				vec[row] = (*this)(row, idx);
			}
			return vec;
		}

		void set_row(int idx, const T* row)
		{
			assert(idx < nrows);
			std::copy(row, row + ncols, data + (idx * ncols));
		}

		void set_col(int idx, const T* column)
		{
			assert(idx < ncols);
			for (int i = 0; i < nrows; i++)
			{
				data[i * nrows + idx] = column[i];
			}
		}

		// Algebraic Operators
		Matrix<T, nrows, ncols> Add(const T scalar) const
		{
			Matrix<T, nrows, ncols> mat = *this;
			for (int i = 0; i < size; i++)
			{
				mat.data[i] = data[i] + scalar;
			}
			return mat;
		}

		Matrix<T, nrows, ncols> Subtract(const T scalar) const
		{
			Matrix<T, nrows, ncols> mat = *this;
			for (int i = 0; i < size; i++)
			{
				mat.data[i] = data[i] - scalar;
			}
			return mat;
		}

		Matrix<T, nrows, ncols> Multiply(const T scalar) const
		{
			Matrix<T, nrows, ncols> mat = *this;
			for (int i = 0; i < size; i++)
			{
				mat.data[i] = data[i] * scalar;
			}
			return mat;
		}

		Matrix<T, nrows, ncols> Divide(const T scalar) const
		{
			T factor = 1 / scalar;
			if (factor > 0)
			{
				Matrix<T, nrows, ncols> mat = *this;
				for (int i = 0; i < size; i++)
				{
					mat.data[i] = data[i] * factor;
				}
				return mat;
			}
			else
			{
				throw("Cannot divide by zero.");
			}
		}

		// Methods
		constexpr Shape shape()
		{
			Shape s(nrows, ncols);
			return s;
		}

		friend std::ostream& operator << (std::ostream& out, const Matrix<T, nrows, ncols>& mat)
		{
			for (int row = 0; row < nrows; row++)
			{
				for (int col = 0; col < ncols; col++)
				{
					out << mat(row, col) << " ";
				}
				out << "\n";
			}
			return out;
		}
	};

	template <typename T, int nrows, int ncols, int ncolsB>
	Matrix<T, nrows, ncolsB> dot(const Matrix<T, nrows, ncols>& lhs, const Matrix<T, ncols, ncolsB>& rhs)
	{
		Matrix<T, nrows, ncolsB> mat;
		for (int row = 0; row < nrows; row++)
		{
			for (int col = 0; col < ncolsB; col++)
			{
				for (int idx = 0; idx < ncols; idx++)
				{
					mat(row, col) += lhs(row, idx) * rhs(idx, col);
				}
			}
		}
		return mat;
	}

	template <typename T, int nrows, int ncols, int ncolsB>
	Matrix<T, nrows, ncolsB> dot(const Matrix<T, nrows, ncols>& lhs, const Matrix<T, ncols, ncolsB>& rhs)
	{
		Matrix<T, nrows, ncolsB> mat;

		for

		
		return mat;
	}

#ifndef ROW_MAJOR

	template <typename T, int nrows, int ncols>
	Vector<T, nrows> dot(const Matrix<T, nrows, ncols>& lhs, const Vector<T, ncols>& rhs)
	{
		Vector<T, nrows, true> vec;
		for (int row = 0; row < nrows; row++)
		{
			for (int col = 0; col < ncols; col++)
			{
				vec[row] += lhs(row, col) * rhs[col];
			}
		}
		return vec;
	}

#else

	template <typename T, int nrows, int ncols>
	Vector<T, ncols> dot(const Vector<T, nrows>& lhs, const Matrix<T, nrows, ncols>& rhs)
	{
		Vector<T, ncols, false> vec;
		for (int col = 0; col < ncols; col++)
		{
			for (int row = 0; row < nrows; row++)
			{
				vec[col] += rhs(row, col) * lhs[row];
			}
		}
		return vec;
	}

#endif // !ROW_MAJOR

	// TODO: rewrite based on Shape and move to vector.h
	template <typename T, int n>
	Matrix<T, n, n> dot(const Vector<T, n, true>& lhs, const Vector<T, n, false>& rhs)
	{
		Matrix<T, n, n> mat;
		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{
				mat(row, col) = lhs[row] * rhs[col];
			}
		}
		return mat;
	}

	template <typename T, int nrows, int ncols>
	Matrix<T, nrows, ncols> operator + (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Add(scalar);
	}

	template <typename T, int nrows, int ncols>
	Matrix<T, nrows, ncols> operator - (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Subtract(scalar);
	}

	template <typename T, int nrows, int ncols>
	Matrix<T, nrows, ncols> operator / (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Divide(scalar);
	}

	template <typename T, int nrows, int ncols>
	Matrix<T, nrows, ncols> operator * (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Multiply(scalar);
	}

	template <typename T, int nrows, int ncols, int ncolsB>
	Matrix<T, nrows, ncolsB> operator * (const Matrix<T, nrows, ncols>& lhs, const Matrix<T, ncols, ncolsB>& rhs)
	{
		return dot(lhs, rhs);
	}

#ifndef ROW_MAJOR

	template <typename T, int nrows, int ncols>
	Vector<T, nrows> operator * (const Matrix<T, nrows, ncols>& lhs, const Vector<T, ncols, true>& rhs)
	{
		return dot(lhs, rhs);
	}

#else

	template <typename T, int nrows, int ncols>
	Vector<T, ncols> operator * (const Vector<T, nrows>& lhs, const Matrix<T, nrows, ncols>& rhs)
	{
		return dot(lhs, rhs);
	}

#endif // !ROW_MAJOR

	// TODO rewrite based on Shape and move to vector.h
	template <typename T, int n>
	Matrix<T, n, n> operator * (const Vector<T, n, true>& lhs, const Vector<T, n, false>& rhs)
	{
		return dot(lhs, rhs);
	}

	template <typename T, int nrows, int ncols>
	Matrix<T, ncols, nrows> transpose(const Matrix<T, nrows, ncols>& mat)
	{
		Matrix<T, ncols, nrows> matrixTransposed;
		for (int row = 1; row <= nrows; row++)
		{
			for (int col = 1; col <= ncols; col++)
			{
				matrixTransposed.data()[(col - 1) * nrows + row - 1] = mat.data()[(row - 1) * ncols + col - 1];
			}
		}
		return matrixTransposed;
	}

	template <typename T, int nrows, int ncols>
	Matrix<T, nrows, ncols> identity()
	{
		Matrix<T, nrows, ncols> mat;
		for (int row = 0; row < nrows; row++)
		{
			for (int col = 0; col < ncols; col++)
			{
				if (row == col) { mat(row, col) = 1; }
			}
		}
		return mat;
	}

	typedef Matrix<int, 2, 2> Matrix2i;
	typedef Matrix<int, 3, 3> Matrix3i;
	typedef Matrix<int, 4, 4> Matrix4i;

	typedef Matrix<float, 2, 2> Matrix2f;
	typedef Matrix<float, 3, 3> Matrix3f;
	typedef Matrix<float, 4, 4> Matrix4f;
}