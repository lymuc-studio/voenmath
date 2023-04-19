#include <iostream>

#include <voenmath/io.hpp>
#include <voenmath/mat.hpp>
#include <voenmath/product.hpp>

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

	auto r = m1 * m2;

	std::cout << r << std::endl;

	return 0;
}
