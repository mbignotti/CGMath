#pragma once
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <initializer_list>
#include <utils.h>

namespace cgm {

	template <typename T, int nrows, int ncols>
	struct Matrix
	{
		// Attributes
		Shape shape{ nrows, ncols };

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
		friend std::ostream& operator << (std::ostream& out, const Matrix<T, nrows, ncols>& mat)
		{
			for (size_t row = 0; row < nrows; row++)
			{
				for (size_t col = 0; col < ncols; col++)
				{
					out << mat(row, col) << " ";
				}
				out << "\n";
			}
			return out;
		}
	};
}