#pragma once
#include <iostream>

namespace cgm {

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

}

