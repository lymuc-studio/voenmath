#ifndef VOENMATH_MAT_HPP
#define VOENMATH_MAT_HPP

#include <vector>
#include <type_traits>

#include "voenmath/err.hpp"

namespace voenmath::detail
{
	template<typename T>
	struct mat_traits
	{
		static_assert(!std::is_reference_v<T>);
	
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using vector_type = std::vector<value_type>;
		using size_type = typename vector_type::size_type;
	};

	template<typename T>
	class mat_row_view
	{
	public:
		using traits = mat_traits<T>;
	
		using reference = typename traits::reference;
		using size_type = typename traits::size_type;
		using vector_type = typename traits::vector_type;

		mat_row_view(vector_type& storage, size_type cols, size_type row)
			: storage_(storage)
			, cols_(cols)
			, row_(row)
		{
		}

		reference operator[](size_type col)
		{
			return storage_.at(cols_ * row_ + col);
		}

	private:
		vector_type& storage_;
		size_type cols_ = 1;
		size_type row_ = 0;
	};
}

namespace voenmath
{
	template<typename T>
	class mat
	{
	public:
		using traits = detail::mat_traits<T>;
		using row_view = detail::mat_row_view<T>;

		using value_type = typename traits::value_type;
		using reference = typename traits::reference; 
		using const_reference = typename traits::const_reference;

		using size_type = typename traits::size_type;
		using vector_type = typename traits::vector_type;
		using init_list = std::initializer_list<value_type>;

		explicit mat(size_type rows = 1, size_type cols = 1)
		{
			resize(rows, cols);
		}

		explicit mat(size_type rows, size_type cols, const init_list& values)
			: rows_(rows)
			, cols_(cols)
			, storage_(values)
		{
			VOENASSERT(rows && cols);
			VOENASSERT(rows * cols == values.size());
		}

		explicit mat(size_type rows, size_type cols, const vector_type& values)
			: rows_(rows)
			, cols_(cols)
			, storage_(values)
		{
			VOENASSERT(rows && cols);
			VOENASSERT(rows * cols == values.size());
		}

		void resize(size_type rows, size_type cols)
		{
			VOENASSERT(rows && cols);
			storage_.resize((rows_ = rows) * (cols_ = cols));
		}

		void fill_with(const_reference fill_value)
		{
			storage_.assign(storage_.size(), fill_value);
		}

		reference at(size_type row, size_type col)
		{
			return storage_.at(row * cols_ + col);
		}

		const_reference at(size_type row, size_type col) const
		{
			return storage_.at(row * cols_ + col);
		}

		size_type get_rows() const
		{
			return rows_;
		}

		size_type get_cols() const
		{
			return cols_;
		}

		row_view operator[](size_type row)
		{
			return make_row_view(row);
		}

	private:
		row_view make_row_view(size_type row)
		{
			return row_view(storage_, cols_, row);
		}

		vector_type storage_;
		size_type rows_ = 1;
		size_type cols_ = 1;
	};

	using imat = mat<int>;
	using fmat = mat<float>;
	using dmat = mat<double>;
	using umat = mat<unsigned>;
}

#endif // VOENMATH_MAT_HPP
