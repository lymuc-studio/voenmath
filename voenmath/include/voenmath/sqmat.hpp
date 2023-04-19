#ifndef VOENMATH_VEC_2_MAT_HPP
#define VOENMATH_VEC_2_MAT_HPP

#include <cmath>

#include <vector>
#include <type_traits>

#include "voenmath/err.hpp"

namespace voenmath::detail
{
	template<typename T>
	struct sqmat_traits
	{
		static_assert(!std::is_reference_v<T>);

		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using vector_type = std::vector<value_type>;
		using size_type = typename vector_type::size_type;
	};

	template<typename T>
	class sqmat_row
	{
	public:
		using parent_traits = sqmat_traits<T>;

		using size_type = typename parent_traits::size_type;
		using reference = typename parent_traits::reference;
		using vector_type = typename parent_traits::vector_type;

		sqmat_row(vector_type& storage, size_type size, size_type row_index)
			: storage_(storage)
			, size_(size)
			, row_index_(row_index)
		{
		}

		reference operator[](size_type column_index)
		{
			return storage_.at(row_index_ * size_ + column_index);
		}

	private:
		vector_type& storage_;
		size_type size_ = 0;
		size_type row_index_ = 0;
	};
}

namespace voenmath
{
	template<typename T>
	class sqmat
	{
	public:
		using traits = detail::sqmat_traits<T>;
		using sqmat_row = detail::sqmat_row<T>;

		using size_type = typename traits::size_type;
		using value_type = typename traits::value_type;
		using vector_type = typename traits::vector_type;
		using const_reference = typename traits::const_reference;

		sqmat(size_type size = 1)
		{
			resize(size);
		}

		sqmat(const std::initializer_list<value_type>& values)
			: storage_(values)
		{
			resize(std::sqrt(values.size()));
		}

		void resize(size_type size)
		{
			VOENASSERT(size);
			size_ = size;
			storage_.resize(size * size);
		}

		void resize(size_type size, const_reference fill)
		{
			VOENASSERT(size);
			size_ = size;
			storage_.resize(size * size, fill);
		}

		void fill_with(const_reference fill)
		{
			storage_.assign(storage_.size(), fill);
		}

		size_type size() const
		{
			return size_;
		}

		size_type element_count() const
		{
			return size_ * size_;
		}

		template<typename FunctorT>
		void diagonal(FunctorT functor)
		{
			for (size_type ielem = 0; ielem < storage_.size(); ielem += size_ + 1)
			{
				functor(storage_.at(ielem));
			}
		}

		sqmat_row operator[](size_type row_index)
		{
			return make_row_view(row_index);
		}

	private:
		sqmat_row make_row_view(size_type row_index)
		{
			return sqmat_row(storage_, size_, row_index);
		}

		vector_type storage_;
		size_type size_ = 1;
	};
}

#endif // VOENMATH_VEC_2_MAT_HPP
