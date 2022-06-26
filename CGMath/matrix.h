#pragma once
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <initializer_list>
#include <utils.h>

namespace cgm {

	template <typename T, int n, int m>
	struct Matrix
	{
		// Attributes
		Shape shape{ n, m };

#ifndef ROW_MAJOR

		Strides strides{ sizeof(T) * m, sizeof(T) };

#else

		Strides strides{ sizeof(T), sizeof(T) * n };

#endif // !ROW_MAJOR

		static const int size = n * m;
		T data[size];

		// Constructors
		Matrix() : data{ } { }

		Matrix(T value) : data{ }
		{
			for (int i = 0; i < n; i++)
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

		Matrix(std::initializer_list<std::initializer_list<T>> init_list) : data{ }
		{
			assert(init_list.size() == n);

			int i = 0, j = 0;
			for (const auto l : init_list)
			{
				assert(l.size() == m);
				for (const auto v : l)
				{
					int offset = i * strides.dimOne + j * strides.dimTwo; //Strides logic must be reviewed
					*(data + offset) = v;
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
		T& operator()(const int i, const int j)
		{
			int offset = i * strides.dimOne + j * strides.dimTwo;
			T result = *(data + offset);
			return result;
		}

		T operator()(const int i, const int j) const
		{
			int offset = i * strides.dimOne + j * strides.dimTwo;
			T result = *(data + offset);
			return result;
		}

		Vector<T, m> row(int idx) const
		{
			assert(idx < n);
			Vector<T, m> vec;
			for (int col = 0; col < m; col++)
			{
				vec[col] = (*this)(idx, col);
			}
			return vec;
		}

		Vector<T, n> column(int idx) const
		{
			assert(idx < m);
			Vector<T, n> vec;
			for (int row = 0; row < n; row++)
			{
				vec[row] = (*this)(row, idx);
			}
			return vec;
		}


	};
}