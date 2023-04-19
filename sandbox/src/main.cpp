#include <iostream>

#include <voenmath/sqmat.hpp>
#include <voenmath/io.hpp>

int main()
{
	voenmath::sqmat<int> E
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	std::cout << "Main diagonal:\n";

	E.diagonal([](int& value)
		{
			std::cout << value++ << std::endl;
		}
	);

	std::cout << "\nE =\n" << E << std::endl;

	std::cout << "E[2][1] = " << E[2][1] << std::endl;
	std::cout << "E[0][0] = " << E[0][0] << std::endl;

	return 0;
}
