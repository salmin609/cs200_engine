#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union

template <typename T>
struct[[nodiscard]] vector2
{
    union {
        struct
        {
            T x, y;
        };
        struct
        {
            T u, v;
        };
        struct
        {
            T width, height;
        };
        T elements[2];
    };

    vector2() noexcept;
    explicit vector2(T repeated_float) noexcept;
    vector2(T fx, T fy) noexcept;
};

//static_assert(sizeof(vector2) == sizeof(float) * 2, "vector2 should only be two floats");

template <typename T>
constexpr void operator+=(vector2<T>& v, const vector2<T>& adding_vector) noexcept;

template <typename T>
constexpr void operator-=(vector2<T>& v, const vector2<T>& subtracting_vector) noexcept;

template <typename T>
constexpr void operator*=(vector2<T>& v, float scale) noexcept;

template <typename T>
constexpr void operator/=(vector2<T>& v, float divisor) noexcept;

template <typename T>
constexpr vector2<T> operator-(const vector2<T>& v) noexcept;

template <typename T>
constexpr vector2<T> operator+(const vector2<T>& v1, const vector2<T>& v2) noexcept;

template <typename T>
constexpr vector2<T> operator-(const vector2<T>& v1, const vector2<T>& v2) noexcept;

template <typename T>
constexpr vector2<T> operator*(const vector2<T>& v, float scale) noexcept;

template <typename T>
constexpr vector2<T> operator*(float scale, const vector2<T>& v) noexcept;

template <typename T>
constexpr vector2<T> operator/(const vector2<T>& v, float divisor) noexcept;

template <typename T>
[[nodiscard]]constexpr  bool operator==(const vector2<T>& v1, const vector2<T>& v2) noexcept;
template <typename T>
[[nodiscard]]constexpr  bool operator!=(const vector2<T>& v1, const vector2<T>& v2) noexcept;

template <typename T>
[[nodiscard]]constexpr  float dot(vector2<T> a, vector2<T> b) noexcept;
template <typename T>
constexpr vector2<T>             perpendicular_to(vector2<T> a) noexcept;
template <typename T>
[[nodiscard]]constexpr  float magnitude_squared(vector2<T> a) noexcept;
template <typename T>
[[nodiscard]]constexpr  float magnitude(vector2<T> a) noexcept;

template <typename T>
constexpr vector2<T>             normalize(vector2<T> a) noexcept;
template <typename T>
[[nodiscard]]constexpr  float distance_between_squared(vector2<T> a, vector2<T> b) noexcept;
template <typename T>
[[nodiscard]]constexpr  float distance_between(vector2<T> a, vector2<T> b) noexcept;
template <typename T>
[[nodiscard]]constexpr  float angle_between(vector2<T> a, vector2<T> b) noexcept;
template <typename T>
constexpr vector2<T>             rotate_by(float angle_in_radians, vector2<T> v) noexcept;


#pragma warning(pop)

#include "vector2.inl"
#include <cassert>
#include <limits>