#ifndef VOENMATH_OPERATION_HPP
#define VOENMATH_OPERATION_HPP

#include "voenmath/mat.hpp"
#include "voenmath/err.hpp"

namespace voenmath::detail
{
	template<typename T>
	mat<T> negate(const mat<T>& m)
	{
		using size_type = typename mat<T>::size_type;

		size_type rows = m.get_rows();
		size_type cols = m.get_cols();
		
		mat<T> result(rows, cols);

		for (size_type ir = 0; ir < rows; ir++)
		{
			for (size_type ic = 0; ic < cols; ic++)
			{
				result.at(ir, ic) = -m.at(ir, ic);
			}
		}

		return result;
	}

	template<typename T>
	mat<T> sum(const mat<T>& left, const mat<T>& right)
	{
		using size_type = typename mat<T>::size_type;

		size_type rows = left.get_rows();
		size_type cols = left.get_cols();
		
		VOENASSERT(rows == right.get_rows() && cols == right.get_cols());

		mat<T> result(rows, cols);	
	
		for (size_type ir = 0; ir < rows; ir++)
		{
			for (size_type ic = 0; ic < cols; ic++)
			{
				result.at(ir, ic) = left.at(ir, ic) + right.at(ir, ic);
			}
		}

		return result;
	}

	template<typename T>
	mat<T> subtract(const mat<T>& left, const mat<T>& right)
	{
		using size_type = typename mat<T>::size_type;

		size_type rows = left.get_rows();
		size_type cols = left.get_cols();
		
		VOENASSERT(rows == right.get_rows() && cols == right.get_cols());

		mat<T> result(rows, cols);	

		for (size_type ir = 0; ir < rows; ir++)
		{
			for (size_type ic = 0; ic < cols; ic++)
			{
				result.at(ir, ic) = left.at(ir, ic) - right.at(ir, ic);
			}
		}
	
		return result;
	}

	template<typename T>
	mat<T> product(const T& scalar, const mat<T>& m)
	{
		using size_type = typename mat<T>::size_type;

		size_type rows = m.get_rows();
		size_type cols = m.get_cols();

		mat<T> result(rows, cols);

		for (size_type ir = 0; ir < rows; ir++)
		{
			for (size_type ic = 0; ic < cols; ic++)
			{
				result.at(ir, ic) = scalar * m.at(ir, ic);
			}
		}
	
		return result;
	}

	template<typename T>
	mat<T> product(const mat<T>& left, const mat<T>& right)
	{
		using size_type = typename mat<T>::size_type;

		size_type left_cols = left.get_cols();
		size_type left_rows = left.get_rows();
		size_type right_rows = right.get_rows();
		size_type right_cols = right.get_cols();

		VOENASSERT(left_cols == right_rows);

		mat<T> result(left_rows, right_cols);
	
		for (size_type i = 0; i < left_rows; i++)
		{
			for (size_type j = 0; j < right_cols; j++)
			{
				for (size_type k = 0; k < left_cols; k++)
				{
					result.at(i, j) += left.at(i, k) * right.at(k, j);
				}
			}
		}

		return result;
	}
}

namespace voenmath
{
	template<typename T>
	mat<T> operator-(const mat<T>& m)
	{
		return detail::negate(m);
	}

	template<typename T>
	mat<T> operator+(const mat<T>& m)
	{
		return m;
	}

	template<typename T>
	mat<T> operator+(const mat<T>& left, const mat<T>& right)
	{
		return detail::sum(left, right);
	}

	template<typename T>
	mat<T>& operator+=(mat<T>& left, const mat<T>& right)
	{
		return left = left + right;
	}

	template<typename T>
	mat<T> operator-(const mat<T>& left, const mat<T>& right)
	{
		return detail::subtract(left, right);
	}

	template<typename T>
	mat<T>& operator-=(mat<T>& left, const mat<T>& right)
	{
		return left = left - right;
	}

	template<typename T>
	mat<T> operator*(const T& scalar, const mat<T>& m)
	{
		return detail::product(scalar, m);
	}

	template<typename T>
	mat<T>& operator*=(mat<T>& left, const T& scalar)
	{
		return left = scalar * left;
	}

	template<typename T>
	mat<T> operator*(const mat<T>& left, const mat<T>& right)
	{
		return detail::product(left, right);
	}

	template<typename T>
	mat<T>& operator*=(mat<T>& left, const mat<T>& right)
	{
		return left = left * right;
	}
}

#endif // VOENMATH_OPERATION_HPP
