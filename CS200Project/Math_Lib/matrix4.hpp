#pragma once
#include "vector4.hpp"
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
 /**
  * \brief Column first 3x3 matrix class
  */
template <typename T>
struct [[nodiscard]] matrix4
{
public:
	union {
		T elements[4][4];
		struct
		{
			vector4<T> column0;
			vector4<T> column1;
			vector4<T> column2;
			vector4<T> column3;
		};
	};

public:
	constexpr matrix4() noexcept;
	//constexpr matrix4(vector3<T> first_column, vector3<T> second_column, vector3<T> third_column, vector3<T> fourth_column) noexcept;
	
	constexpr T  operator()(int column, int row) const noexcept;
	constexpr T& operator()(int column, int row) noexcept;
};

//static_assert(sizeof(matrix3) == sizeof(float) * 3 * 3, "matrix3 should be 3x3 floats");

template <typename T>
constexpr matrix4<T> operator*(const matrix4<T>& m1, const matrix4<T>& m2) noexcept;
template <typename T>
constexpr void    operator*=(matrix4<T>& m1, const matrix4<T>& m2) noexcept;



template <typename T>
struct vector2;
namespace MATRIX4
{
	template <typename T>
	constexpr matrix4<T> transpose(const matrix4<T>& m) noexcept;
	template <typename T>
	constexpr matrix4<T> build_rotation(float angle_in_radians) noexcept;
	template <typename T>
	constexpr matrix4<T> build_identity() noexcept;
	template <typename T>
	constexpr matrix4<T> build_scale(float scale_x, float scale_y) noexcept;
	template <typename T>
	constexpr matrix4<T> build_scale(float scale) noexcept;
	template <typename T>
	constexpr matrix4<T> build_scale(const vector2<T>& scale) noexcept;
	template <typename T>
	constexpr matrix4<T> build_translation(float translate_x, float translate_y) noexcept;
	//template <typename T>
	//constexpr matrix4<T> build_translation(const vector2<T>& translation) noexcept;
}


#pragma warning(pop)
#include "vector2.hpp"
#include <cassert>
#include <limits>
#include "matrix4.inl"