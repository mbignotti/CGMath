#pragma once
#include <Vector.h>

namespace cgm {

	template <typename T> 
	struct Vector<T, 3> { 
		union 
		{ 
			T data[3]; 
			struct { float x, y, z; }; 
		}; 
	};

}