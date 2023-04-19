#ifndef VOENMATH_PRODUCT_HPP
#define VOENMATH_PRODUCT_HPP

#include "voenmath/mat.hpp"
#include "voenmath/err.hpp"

namespace voenmath::detail
{
	template<typename T>
	mat<T> product(const mat<T>& left, const mat<T>& right)
	{
		auto left_cols = left.get_cols();
		auto left_rows = left.get_rows();
		auto right_rows = right.get_rows();
		auto right_cols = right.get_cols();

		using size_type = decltype(left_cols);

		VOENASSERT(left_cols == right_rows);

		mat<T> result(left_rows, right_cols);
	
		for (size_type i = 0; i < left_rows; i++)
		{
			for (size_type j = 0; j < right_cols; j++)
			{
				for (size_type k = 0; k < left_cols; k++)
				{
					result[i][j] += left.at(i, k) * right.at(k, j);
				}
			}
		}

		return result;
	}
}

namespace voenmath
{
	template<typename T>
	mat<T> operator*(const mat<T>& left, const mat<T>& right)
	{
		return detail::product(left, right);
	}
}

#endif // VOENMATH_PRODUCT_HPP
