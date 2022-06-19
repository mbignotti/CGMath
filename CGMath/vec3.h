#pragma once
#include "vector.h"

namespace cgm {

	template <typename T>
	struct Vec3 : public Vector<T, 3> {

		using Vector<T, 3>::shape;
		using Vector<T, 3>::data;
		using Vector<T, 3>::Vector;

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
		Vec3<T>& operator=(const Vec3<T>& vec)
		{
			shape = vec.shape;
			data = vec.data;

			return *this;
		}

		inline T& x() { return data[0]; }
		inline const T& x() const { return data[0]; }

		inline T& y() { return data[1]; }
		inline const T& y() const { return data[1]; }

		inline T& z() { return data[2]; }
		inline const T& z() const { return data[2]; }

	};

	template <typename T>
	Vec3<T> cross(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		Vec3<T> result
		{
			lhs[1] * rhs[2] - lhs[2] * rhs[1],
			lhs[2] * rhs[0] - lhs[0] * rhs[2],
			lhs[0] * rhs[1] - lhs[1] * rhs[0]
		};
		return result;
	}

	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;

}