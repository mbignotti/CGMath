#pragma once
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <initializer_list>
#include "utils.h"

namespace cgm {

	// Defaults to column major. Declare ROW_MAJOR to use a row major layout.
	// ROW_MAJOR mainly influences dot products and default matrices (e.g. perspective transform matrix).
	template <typename T, int n>
	struct Vector
	{
		// Attributes
		T data[n];

		// Constructors
		Vector() : data{ } { }

		explicit Vector(T value) : data{ }
		{
			for (int i = 0; i < n; i++)
			{
				data[i] = value;
			}
		}

		Vector(std::initializer_list<T> init_list) : data{ }
		{
			assert(init_list.size() == n);

			int i = 0;
			for (const auto val : init_list)
			{
				data[i] = val;
				++i;
			}
			
		}

		Vector(Vector<T, n - 1> other, T scalar) : data{ }
		{
			std::copy(other.data, other.data + n - 1, data);
			data[n - 1] = scalar;
		}

		// Destructor
		~Vector() { }

		// Operators
		// Access operators
		T& operator[](const int i)
		{
			return data[i];
		}

		T operator[](const int i) const
		{
			return data[i];
		}

		// Assignment Operator
		Vector<T, n>& operator=(const Vector<T, n>& vec)
		{
			data = vec.data;
			return *this;
		}

		// Methods
		constexpr Shape shape()
		{
#ifndef ROW_MAJOR

			Shape s(1, n);
			return s;

#else

			Shape s(n, 1);
			return s;

#endif // !ROW_MAJOR

		}

		friend std::ostream& operator << (std::ostream& out, const Vector<T, n>& vec)
		{
			for (int i = 0; i < n; i++)
			{
				out << vec[i] << " ";
			}
			return out;
		}

		constexpr int size() { return n; }

		T norm2() { return dot(*this, *this); }

		float norm() { return std::sqrt(norm2()); }

		void normalize()
		{
			float length = norm();
			if (length > 0)
			{
				float factor = 1 / length;
				*this = *this * factor;
			}
		}

		// Algebraic Operators
		Vector<T, n> Add(const Vector<T, n>& v) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] + v[i];
			}
			return vec;
		}

		Vector<T, n> Add(const T scalar) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] + scalar;
			}
			return vec;
		}

		Vector<T, n> Subtract(const Vector<T, n>& v) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] - v[i];
			}
			return vec;
		}

		Vector<T, n> Subtract(const T scalar) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] - scalar;
			}
			return vec;
		}

		Vector<T, n> Multiply(const Vector<T, n>& v) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] * v[i];
			}
			return vec;
		}

		Vector<T, n> Multiply(const T scalar) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] * scalar;
			}
			return vec;
		}

		Vector<T, n> Divide(const Vector<T, n>& v) const
		{
			Vector<T, n> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] / v[i];
			}
			return vec;
		}

		Vector<T, n> Divide(const T scalar) const
		{
			Vector<T, n> vec;
			T factor = 1 / scalar;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] * factor;
			}
			return vec;
		}

	};

	template <typename T, int n>
	Vector<T, n> operator + (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Add(rhs);
	}

	template <typename T, int n>
	Vector<T, n> operator + (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Add(scalar);
	}

	template <typename T, int n>
	Vector<T, n> operator - (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Subtract(rhs);
	}

	template <typename T, int n>
	Vector<T, n> operator - (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Subtract(scalar);
	}

	template <typename T, int n>
	Vector<T, n> operator * (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Multiply(rhs);
	}

	template <typename T, int n>
	Vector<T, n> operator * (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Multiply(scalar);
	}

	template <typename T, int n>
	Vector<T, n> operator / (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Divide(rhs);
	}

	template <typename T, int n>
	Vector<T, n> operator / (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Divide(scalar);
	}

	template <typename T, int n>
	bool operator == (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		bool equality = true;
		for (int i = 0; i < n; i++)
		{
			if (equality)
			{
				equality = lhs[i] == rhs[i];
			}
			else
			{
				return false;
			}
		}
		return equality;
	}

	template <typename T, int n>
	Vector<bool, n> operator == (const Vector<T, n>& lhs, const T scalar)
	{
		Vector<bool, n> equality(true);
		for (int i = 0; i < n; i++)
		{
			equality[i] = lhs[i] == scalar;
		}
		return equality;
	}

	template <int n>
	bool any(const Vector<bool, n>& vec)
	{
		bool trueCondition = false;
		for (int i = 0; i < n; i++)
		{
			if (vec[i])
			{
				trueCondition = true;
				break;
			}
		}
		return trueCondition;
	}

	template <int n>
	bool all(const Vector<bool, n>& vec)
	{
		bool trueCondition = true;
		for (int i = 0; i < n; i++)
		{
			if (!vec[i])
			{
				trueCondition = false;
				break;
			}
		}
		return trueCondition;
	}

	template <typename T, int n>
	T sum(Vector<T, n> vec)
	{
		T result = 0;
		for (int i = 0; i < n; i++)
		{
			result += vec[i];
		}
		return result;
	}

	template <typename T, int n>
	T dot(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		T result = 0;
		for (int i = 0; i < n; i++)
		{
			result += lhs[i] * rhs[i];
		}
		return result;
	}

	template <typename T, int n>
	Vector<T, n> normalized(const Vector<T, n>& vec)
	{
		Vector<T, n> result = vec;
		result.normalize();
		return result;
	}

	template<typename T, int n1, int n2>
	Vector<T, n1> embed(const Vector<T, n2>& v, T fill = 1)
	{
		Vector<T, n1> result;
		for (int i = n1; i--; result[i] = (i < n2 ? v[i] : fill));
		return result;
	}

	template<typename T, int n1, int n2>
	Vector<T, n1> proj(const Vector<T, n2>& v)
	{
		Vector<T, n1> result;
		for (int i = n1; i--; result[i] = v[i]);
		return result;
	}
}
