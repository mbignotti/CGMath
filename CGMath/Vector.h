#pragma once
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <initializer_list>
#include <Utils.h>

namespace cgm {

	template <typename T, size_t n, bool ColumnMajor = true>
	struct Vector
	{

		// Attributes
		T data[n];

		// Constructors
		Vector() : data{ } { }

		Vector(std::initializer_list<T> init_list)
			: data{ }
		{
			int count{ 0 };
			for (T element : init_list)
			{
				data[count] = element;
				++count;
			}
		}

		Vector(T xx) : data{ }
		{
			for (int i = 0; i < n; i++)
			{
				data[i] = xx;
			}

		}

		Vector(Vector<T, n-1> other, T scalar) :
			data{ }
		{
			std::copy(other.data, other.data + n - 1, data);
			data[n-1] = scalar;
		}

		// Destructor
		~Vector() { }

		// Operators
		// Access operators
		T& operator[](const size_t i)
		{
			assert(i < n); return data[i];
		}

		T operator[](const size_t i) const
		{
			assert(i < n); return data[i];
		}

		// Algebraic Operators
		Vector<T, n, ColumnMajor> Add(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] + v[i];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Add(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] + scalar;
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Subtract(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] - v[i];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Subtract(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] - scalar;
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Multiply(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] * v[i];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Multiply(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] * scalar;
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Divide(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] / v[i];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Divide(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			T factor = 1 / scalar;
			for (int i = 0; i < n; i++)
			{
				vec[i] = data[i] * factor;
			}
			return vec;
		}

		// Methods
		friend std::ostream& operator << (std::ostream& out, const Vector<T, n, ColumnMajor>& vec)
		{
			for (size_t i = 0; i < n; i++)
			{
				out << vec[i] << " ";
			}
			return out;
		}

		constexpr int size() { return n; }

		Shape shape()
		{
			if (!ColumnMajor)
			{
				Shape s(1, n);
				return s;
			}
			else
			{
				Shape s(n, 1);
				return s;
			}
		}

		T norm2() { return dot(*this, *this); }

		float norm() { return std::sqrt(norm2()); }

		void normalized()
		{
			float length = norm();
			if (length > 0)
			{
				float factor = 1 / length;
				*this = *this * factor;
			}
		}
	};


	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator + (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Add(rhs);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator + (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Add(scalar);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator - (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Subtract(rhs);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator - (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Subtract(scalar);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator * (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Multiply(rhs);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator * (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Multiply(scalar);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator / (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		return lhs.Divide(rhs);
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> operator / (const Vector<T, n>& vec, const T scalar)
	{
		return vec.Divide(scalar);
	}

	template <typename T, size_t n>
	bool operator == (const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		bool equality{ true };
		for (size_t i = 0; i < n; i++)
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

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<bool, n, ColumnMajor> operator == (const Vector<T, n>& lhs, const T scalar)
	{
		Vector<bool, n> equality(true);
		for (size_t i = 0; i < n; i++)
		{
			equality[i] = lhs[i] == scalar;
		}
		return equality;
	}

	template <size_t n>
	bool any(const Vector<bool, n>& vec)
	{
		bool trueCondition{ false };
		for (size_t i = 0; i < n; i++)
		{
			if (vec[i])
			{
				trueCondition = true;
				break;
			}
		}
		return trueCondition;
	}

	template <size_t n>
	bool all(const Vector<bool, n>& vec)
	{
		bool trueCondition{ true };
		for (size_t i = 0; i < n; i++)
		{
			if (!vec[i])
			{
				trueCondition = false;
				break;
			}
		}
		return trueCondition;
	}

	template <typename T, size_t n>
	T sum(Vector<T, n> vec)
	{
		T ret{ 0 };
		for (int i = 0; i < n; i++)
		{
			ret += vec[i];
		}
		return ret;
	}

	template <typename T, size_t n>
	T dot(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
	{
		T ret{ 0 };
		for (size_t i = 0; i < n; i++)
		{
			ret += lhs[i] * rhs[i];
		}
		return ret;
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> normalize(Vector<T, n> vec)
	{
		vec.normalized();
		return vec;
	}

	template <typename T, size_t n, bool ColumnMajor = true>
	Vector<T, n, ColumnMajor> transpose(Vector<T, n, false>& vec)
	{
		Vector<T, n, ColumnMajor> vecT;
		for (size_t i = 0; i < n; i++)
		{
			vecT[i] = vec[i];
		}
		return vecT;
	}

	template <typename T, size_t n, bool ColumnMajor = false>
	Vector<T, n, ColumnMajor> transpose(Vector<T, n, true>& vec)
	{
		Vector<T, n, ColumnMajor> vecT;
		for (size_t i = 0; i < n; i++)
		{
			vecT[i] = vec[i];
		}
		return vecT;
	}

	template <typename T, bool ColumnMajor = true>
	Vector<T, 3, ColumnMajor> cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		Vector<T, 3> vec
		{
			lhs[1] * rhs[2] - lhs[2] * rhs[1],
			lhs[2] * rhs[0] - lhs[0] * rhs[2],
			lhs[0] * rhs[1] - lhs[1] * rhs[0]
		};
		return vec;
	}

	template<typename T, int n1, int n2>
	Vector<T, n1> embed(const Vector<T, n2>& v, T fill = 1)
	{
		Vector<T, n1> ret;
		for (int i = n1; i--; ret[i] = (i < n2 ? v[i] : fill));
		return ret;
	}

	template<typename T, int n1, int n2>
	Vector<T, n1> proj(const Vector<T, n2>& v)
	{
		Vector<T, n1> ret;
		for (int i = n1; i--; ret[i] = v[i]);
		return ret;
	}
}