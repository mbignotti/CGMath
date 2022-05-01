#pragma once
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <initializer_list>

namespace CGMath {

	struct Shape
	{
		size_t nrows;
		size_t ncols;
		Shape(size_t rows, size_t cols)
			: nrows(rows), ncols(cols) { }

		friend std::ostream& operator << (std::ostream& out, const Shape s)
		{
			out << "(" << s.nrows << ", " << s.ncols << ")" << "\n";
			return out;
		}
	};


	/********************************************************/
	/*                        VECTOR                        */
	/********************************************************/

	template <typename T, size_t n, bool ColumnMajor = true>
	class Vector
	{

	private:
		// Attributes
		T m_Data[n];

	public:
		// Constructors
		Vector() : m_Data{ } { }

		Vector(std::initializer_list<T> init_list)
			: m_Data{ }
		{
			int count{ 0 };
			for (T element : init_list)
			{
				m_Data[count] = element;
				++count;
			}
		}

		Vector(T xx) : m_Data{ }
		{
			for (int dim = 0; dim < n; dim++)
			{
				m_Data[dim] = xx;
			}

		}

		// Destructor
		~Vector() { }

	public:
		// Operators
		// Access operators
		T& operator[](const size_t i)
		{
			assert(i < n); return m_Data[i];
		}

		T operator[](const size_t i) const
		{
			assert(i < n); return m_Data[i];
		}

		T* data() { return m_Data; }

		const T* data() const { return m_Data; }

		// Algebraic Operators
		Vector<T, n, ColumnMajor> Add(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] + v[dim];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Add(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] + scalar;
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Subtract(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] - v[dim];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Subtract(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] - scalar;
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Multiply(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] * v[dim];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Multiply(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] * scalar;
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Divide(const Vector<T, n>& v) const
		{
			Vector<T, n, ColumnMajor> vec;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] / v[dim];
			}
			return vec;
		}

		Vector<T, n, ColumnMajor> Divide(const T scalar) const
		{
			Vector<T, n, ColumnMajor> vec;
			T factor = 1 / scalar;
			for (int dim = 0; dim < n; dim++)
			{
				vec[dim] = m_Data[dim] * factor;
			}
			return vec;
		}

	public:
		// Methods

		friend std::ostream& operator << (std::ostream& out, const Vector<T, n, ColumnMajor>& vec)
		{
			for (size_t dim = 0; dim < n; dim++)
			{
				out << vec[dim] << " ";
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
		for (size_t dim = 0; dim < n; dim++)
		{
			if (equality)
			{
				equality = lhs[dim] == rhs[dim];
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
		for (size_t dim = 0; dim < n; dim++)
		{
			equality[dim] = lhs[dim] == scalar;
		}
		return equality;
	}

	template <size_t n>
	bool any(const Vector<bool, n>& vec)
	{
		bool trueCondition{ false };
		for (size_t dim = 0; dim < n; dim++)
		{
			if (vec[dim])
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
		for (size_t dim = 0; dim < n; dim++)
		{
			if (!vec[dim])
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
		for (int dim = 0; dim < n; dim++)
		{
			ret += vec[dim];
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
		for (size_t dim = 0; dim < n; dim++)
		{
			vecT[dim] = vec[dim];
		}
		return vecT;
	}

	template <typename T, size_t n, bool ColumnMajor = false>
	Vector<T, n, ColumnMajor> transpose(Vector<T, n, true>& vec)
	{
		Vector<T, n, ColumnMajor> vecT;
		for (size_t dim = 0; dim < n; dim++)
		{
			vecT[dim] = vec[dim];
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

	typedef Vector<int, 2> Vec2i;
	typedef Vector<int, 3> Vec3i;
	typedef Vector<int, 4> Vec4i;

	typedef Vector<float, 2> Vec2f;
	typedef Vector<float, 3> Vec3f;
	typedef Vector<float, 4> Vec4f;

	typedef Vector<float, 2, false> Vec2fT;
	typedef Vector<float, 3, false> Vec3fT;
	typedef Vector<float, 4, false> Vec4fT;



	/*************************************************************/
	/*                           MATRIX                          */
	/*************************************************************/

	template <typename T, size_t nrows, size_t ncols>
	class Matrix
	{

	private:
		// Attributes
		static const size_t m_Size = nrows * ncols;
		T m_Data[m_Size];

	public:
		// Constructors
		Matrix() : m_Data{} {}

		Matrix(T xx)
			: m_Data{}
		{
			for (size_t dim = 0; dim < m_Size; dim++)
			{
				m_Data[dim] = xx;
			}
		}

		Matrix(std::initializer_list<std::initializer_list<T>> init_list) :
			m_Data{}
		{
			assert(init_list.size() == nrows);

			int i = 0, j = 0;
			for (const auto l : init_list)
			{
				assert(l.size() == ncols);
				for (const auto v : l)
				{
					m_Data[i * ncols + j] = v;
					++j;
				}
				j = 0;
				++i;
			}
		}

		// Destructor
		~Matrix() { }

	public:
		// Access operators
		T& operator()(size_t row, size_t col)
		{
			assert(row < nrows);
			assert(col < ncols);
			return m_Data[row * ncols + col];
		}

		T operator()(size_t row, size_t col) const
		{
			assert(row < nrows);
			assert(col < ncols);
			return m_Data[row * ncols + col];
		}

		T* data() { return m_Data; }

		const T* data() const { return m_Data; }

		T* row(size_t idx) const
		{
			assert(idx < nrows);
			T row[ncols]{ };
			std::copy(m_Data + (idx * ncols), m_Data + (idx * ncols) + ncols, row);
			return row;
		}

		T* column(size_t idx) const
		{
			assert(idx < ncols);
			T column[ncols] { };
			for (size_t i = 0; i < nrows; i++)
			{
				column[i] = m_Data[i * ncols + idx];
			}
			return column;
		}

		Vector<T, ncols> row2Vec(size_t idx) const
		{
			assert(idx < nrows);
			Vector<T, ncols> vec;
			for (size_t col = 0; col < ncols; col++)
			{
				vec[col] = (*this)(idx, col);
			}
			return vec;
		}

		Vector<T, nrows> col2Vec(size_t idx) const
		{
			assert(idx < ncols);
			Vector<T, nrows> vec;
			for (size_t row = 0; row < nrows; row++)
			{
				vec[row] = (*this)(row, idx);
			}
			return vec;
		}

		void set_row(size_t idx, const T* row)
		{
			assert(idx < nrows);
			std::copy(row, row + ncols, m_Data + (idx * ncols));
		}

		void set_col(size_t idx, const T* column)
		{
			assert(idx < ncols);
			for (size_t i = 0; i < nrows; i++)
			{
				m_Data[i * nrows + idx] = column[i];
			}
		}

		// Algebraic Operators
		Matrix<T, nrows, ncols> Add(const T scalar) const
		{
			Matrix<T, nrows, ncols> mat = *this;
			for (size_t row = 0; row < nrows; row++)
			{
				for (size_t col = 0; col < ncols; col++)
				{
					mat(row, col) += scalar;
				}
			}
			return mat;
		}

		Matrix<T, nrows, ncols> Subtract(const T scalar) const
		{
			Matrix<T, nrows, ncols> mat = *this;
			for (size_t row = 0; row < nrows; row++)
			{
				for (size_t col = 0; col < ncols; col++)
				{
					mat(row, col) -= scalar;
				}
			}
			return mat;
		}

		Matrix<T, nrows, ncols> Multiply(const T scalar) const
		{
			Matrix<T, nrows, ncols> mat = *this;
			for (size_t row = 0; row < nrows; row++)
			{
				for (size_t col = 0; col < ncols; col++)
				{
					mat(row, col) *= scalar;
				}
			}
			return mat;
		}

		Matrix<T, nrows, ncols> Divide(const T scalar) const
		{
			T factor = 1 / scalar;
			if (factor > 0)
			{
				Matrix<T, nrows, ncols> mat = *this;
				for (size_t row = 0; row < nrows; row++)
				{
					for (size_t col = 0; col < ncols; col++)
					{
						mat(row, col) *= factor;
					}
				}
				return mat;
			}
			else
			{
				throw("Cannot divide by zero.");
			}
		}

	public:
		// Methods
		constexpr Shape shape()
		{
			Shape s(nrows, ncols);
			return s;
		}


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

	template <typename T, size_t nrows, size_t ncols, size_t ncolsB>
	Matrix<T, nrows, ncolsB> dot(const Matrix<T, nrows, ncols>& lhs, const Matrix<T, ncols, ncolsB>& rhs)
	{
		Matrix<T, nrows, ncolsB> mat;
		for (size_t row = 0; row < nrows; row++)
		{
			for (size_t col = 0; col < ncolsB; col++)
			{
				for (size_t idx = 0; idx < ncols; idx++)
				{
					mat(row, col) += lhs(row, idx) * rhs(idx, col);
				}
			}
		}
		return mat;
	}

	template <typename T, size_t nrows, size_t ncols>
	Vector<T, nrows> dot(const Matrix<T, nrows, ncols>& lhs, const Vector<T, ncols, true>& rhs)
	{
		Vector<T, nrows, true> vec;
		for (size_t row = 0; row < nrows; row++)
		{
			for (size_t col = 0; col < ncols; col++)
			{
				vec[row] += lhs(row, col) * rhs[col];
			}
		}
		return vec;
	}

	template <typename T, size_t nrows, size_t ncols>
	Vector<T, ncols, false> dot(const Vector<T, nrows, false>& lhs, const Matrix<T, nrows, ncols>& rhs)
	{
		Vector<T, ncols, false> vec;
		for (size_t col = 0; col < ncols; col++)
		{
			for (size_t row = 0; row < nrows; row++)
			{
				vec[col] += rhs(row, col) * lhs[row];
			}
		}
		return vec;
	}

	template <typename T, size_t n>
	Matrix<T, n, n> dot(const Vector<T, n, true>& lhs, const Vector<T, n, false>& rhs)
	{
		Matrix<T, n, n> mat;
		for (size_t row = 0; row < n; row++)
		{
			for (size_t col = 0; col < n; col++)
			{
				mat(row, col) = lhs[row] * rhs[col];
			}
		}
		return mat;
	}

	template <typename T, size_t nrows, size_t ncols>
	Matrix<T, nrows, ncols> operator + (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Add(scalar);
	}

	template <typename T, size_t nrows, size_t ncols>
	Matrix<T, nrows, ncols> operator - (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Subtract(scalar);
	}

	template <typename T, size_t nrows, size_t ncols>
	Matrix<T, nrows, ncols> operator / (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Divide(scalar);
	}

	template <typename T, size_t nrows, size_t ncols>
	Matrix<T, nrows, ncols> operator * (const Matrix<T, nrows, ncols>& mat, const T scalar)
	{
		return mat.Multiply(scalar);
	}

	template <typename T, size_t nrows, size_t ncols, size_t ncolsB>
	Matrix<T, nrows, ncolsB> operator * (const Matrix<T, nrows, ncols>& lhs, const Matrix<T, ncols, ncolsB>& rhs)
	{
		return dot(lhs, rhs);
	}

	template <typename T, size_t nrows, size_t ncols>
	Vector<T, nrows> operator * (const Matrix<T, nrows, ncols>& lhs, const Vector<T, ncols, true>& rhs)
	{
		return dot(lhs, rhs);
	}

	template <typename T, size_t nrows, size_t ncols>
	Vector<T, ncols, false> operator * (const Vector<T, nrows, false>& lhs, const Matrix<T, nrows, ncols>& rhs)
	{
		return dot(lhs, rhs);
	}

	template <typename T, size_t n>
	Matrix<T, n, n> operator * (const Vector<T, n, true>& lhs, const Vector<T, n, false>& rhs)
	{
		return dot(lhs, rhs);
	}

	template <typename T, size_t nrows, size_t ncols>
	Matrix<T, ncols, nrows> transpose(const Matrix<T, nrows, ncols>& mat)
	{
		Matrix<T, ncols, nrows> matrixTransposed;
		for (int row = 1; row <= nrows; row++)
		{
			for (int col = 1; col <= ncols; col++)
			{
				matrixTransposed.data()[(col - 1) * (int)nrows + row - 1] = mat.data()[(row - 1) * (int)ncols + col - 1];
			}
		}
		return matrixTransposed;
	}

	template <typename T, size_t nrows, size_t ncols>
	Matrix<T, nrows, ncols> identity()
	{
		Matrix<T, nrows, ncols> mat;
		for (size_t row = 0; row < nrows; row++)
		{
			for (size_t col = 0; col < ncols; col++)
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


} // namespace