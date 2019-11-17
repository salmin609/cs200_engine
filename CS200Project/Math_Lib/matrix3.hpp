/*
 * Rudy Castan
 * Math Library
 * CS230
 */
#pragma once
#include "vector3.hpp""
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
 /**
  * \brief Column first 3x3 matrix class
  */
template <typename T>
struct[[nodiscard]] matrix3
{
public:
    union {
        T elements[3][3];
        struct
        {
            vector3<T> column0;
            vector3<T> column1;
            vector3<T> column2;
        };
    };

public:
    constexpr matrix3() noexcept;
    constexpr matrix3(vector3<T> first_column, vector3<T> second_column, vector3<T> third_column) noexcept;
    constexpr matrix3(T column0_row0, T column0_row1, T column0_row2, T column1_row0, T column1_row1,
        T column1_row2, T column2_row0, T column2_row1, T column2_row2) noexcept;

    constexpr T  operator()(int column, int row) const noexcept;
    constexpr T& operator()(int column, int row) noexcept;
};

//static_assert(sizeof(matrix3) == sizeof(float) * 3 * 3, "matrix3 should be 3x3 floats");

template <typename T>
constexpr matrix3<T> operator*(const matrix3<T>& m1, const matrix3<T>& m2) noexcept;
template <typename T>
constexpr void    operator*=(matrix3<T>& m1, const matrix3<T>& m2) noexcept;
template <typename T>
constexpr vector3<T> operator*(const matrix3<T>& m, vector3<T> v) noexcept;


template <typename T>
struct vector2;
namespace MATRIX3
{
    template <typename T>
    constexpr matrix3<T> transpose(const matrix3<T>& m) noexcept;
    template <typename T>
    constexpr matrix3<T> build_rotation(float angle_in_radians) noexcept;
    template <typename T>
    constexpr matrix3<T> build_identity() noexcept;
    template <typename T>
    constexpr matrix3<T> build_scale(float scale_x, float scale_y) noexcept;
    template <typename T>
    constexpr matrix3<T> build_scale(float scale) noexcept;
    template <typename T>
    constexpr matrix3<T> build_scale(const vector2<T>& scale) noexcept;
    template <typename T>
    constexpr matrix3<T> build_translation(float translate_x, float translate_y) noexcept;
    template <typename T>
    constexpr matrix3<T> build_translation(const vector2<T>& translation) noexcept;
}


#pragma warning(pop)
#include "vector2.hpp"
#include <cassert>
#include <limits>
#include "matrix3.inl"