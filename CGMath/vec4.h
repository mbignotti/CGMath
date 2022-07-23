#pragma once
#include "vector.h"

namespace cgm {

	template <typename T>
	struct Vec4 : public Vector<T, 4> {

		using Vector<T, 4>::data;
		using Vector<T, 4>::Vector;

		// Access Operators
		T& operator[](const int i)
		{
			return data[i];
		}

		T operator[](const int i) const
		{
			return data[i];
		}

		// Assignment Operator
		Vec4<T>& operator=(const Vec4<T>& vec)
		{
			data = vec.data;
			return *this;
		}

		inline T& x() { return data[0]; }
		inline const T& x() const { return data[0]; }

		inline T& y() { return data[1]; }
		inline const T& y() const { return data[1]; }

		inline T& z() { return data[2]; }
		inline const T& z() const { return data[2]; }

		inline T& w() { return data[3]; }
		inline const T& w() const { return data[3]; }

	};

	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;

}