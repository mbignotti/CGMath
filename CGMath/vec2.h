#pragma once
#include "vector.h"

namespace cgm {

	template <typename T>
	struct Vec2 : public Vector<T, 2> {

		using Vector<T, 2>::shape;
		using Vector<T, 2>::data;
		using Vector<T, 2>::Vector;

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
		Vec2<T>& operator=(const Vec2<T>& vec)
		{
			shape = vec.shape;
			data = vec.data;

			return *this;
		}

		inline T& x() { return data[0]; }
		inline const T& x() const { return data[0]; }

		inline T& y() { return data[1]; }
		inline const T& y() const { return data[1]; }

	};

	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;

}