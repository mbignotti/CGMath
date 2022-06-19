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
#ifndef ROW_MAJOR

		Shape shape{ n, m };
		Strides strides{ sizeof(T) * m, sizeof(T) };

#else
		Shape shape{ m, n };
		Strides strides{ sizeof(T), sizeof(T) * n };

#endif // ROW_MAJOR

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
			for (const auto val : init_list)
			{
				data[i] = val;
				++i;
			}
		}

		Matrix(std::initializer_list<std::initializer_list<T>> init_list) : data{}
		{
			assert(init_list.size() == n);

			int i = 0, j = 0;
			for (const auto l : init_list)
			{
				assert(l.size() == m);
				for (const auto v : l)
				{
					int offset = i * strides.dimOne + j * strides.dimTwo;
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
			return *(data + offset);
		}

		T operator()(const int i, const int j) const
		{
			int offset = i * strides.dimOne + j * strides.dimTwo;
			return *(data + offset);
		}

	};
}