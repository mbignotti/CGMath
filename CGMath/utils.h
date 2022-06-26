#pragma once
#include <iostream>

namespace cgm {

	struct Shape
	{
		int nrows;
		int ncols;

		Shape() : nrows{ }, ncols{ } { }

		Shape(int rows, int cols)
			: nrows(rows), ncols(cols) { }

		friend std::ostream& operator << (std::ostream& out, const Shape s)
		{
			out << "(" << s.nrows << ", " << s.ncols << ")" << "\n";
			return out;
		}

		inline void transpose()
		{
			std::swap(nrows, ncols);
		}
	};

	struct Strides
	{
		int dimOne;
		int dimTwo;

		Strides() : dimOne{ }, dimTwo{ } { }

		Strides(int firstDim, int secondDim)
			: dimOne(firstDim), dimTwo(secondDim) { }

		friend std::ostream& operator << (std::ostream& out, const Strides s)
		{
			out << "(" << s.dimOne << ", " << s.dimTwo << ")" << "\n";
			return out;
		}

		inline void transpose()
		{
			std::swap(dimOne, dimTwo);
		}
	};
}
