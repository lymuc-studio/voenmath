#include <iostream>

#include <voenmath/io.hpp>
#include <voenmath/mat.hpp>
#include <voenmath/operation.hpp>

int main()
{
	voenmath::imat m1
	{
		2, 3,
		{
			3, -2, 5,
			3, 0, 4
		}
	};

	voenmath::imat m2
	{
		3, 2,
		{
			2, 3,
			-9, 0,
			0, 4
		}
	};

	voenmath::imat m3
	{
		2, 3,
		{
			-3, -1, 4,
			14, 0, -4
		}
	};

	auto r = m2 * m3;

	r *= 2;

	std::cout << -r << std::endl;

	return 0;
}
