#ifndef VOENMATH_IO_HPP
#define VOENMATH_IO_HPP

#include <ostream>

#include "voenmath/sqmat.hpp"

namespace voenmath
{
	template<typename T>
	std::ostream& operator<<(std::ostream& out, sqmat<T>& m)
	{
		auto elements = m.element_count();
		auto size = m.size();
	
		for (std::size_t i = 0; i < elements; i++)
		{
			out << m[i / size][i % size] << ' ';
			if ((i + 1) % size == 0)
			{
				out << '\n';
			}
		}

		return out;
	}
}

#endif // VOENMATH_IO_HPP
