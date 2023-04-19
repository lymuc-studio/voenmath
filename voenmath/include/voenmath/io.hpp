#ifndef VOENMATH_IO_HPP
#define VOENMATH_IO_HPP

#include <ostream>

#include "voenmath/mat.hpp"

namespace voenmath
{
	template<typename T>
	std::ostream& operator<<(std::ostream& out, const mat<T>& m)
	{
		auto rows = m.get_rows();
		auto cols = m.get_cols();
	
		using size_type = decltype(rows);
	
		for (size_type r = 0; r < rows - 1; r++)
		{
			for (size_type c = 0; c < cols - 1; c++)
			{
				std::cout << m.at(r, c) << ' ';
			}
			std::cout << m.at(r, cols - 1) << '\n';
		}
	
		for (size_type c = 0; c < cols - 1; c++)
		{
			std::cout << m.at(rows - 1, c) << ' ';
		}
		std::cout << m.at(rows - 1, cols - 1);

		return out;
	}
}

#endif // VOENMATH_IO_HPP
