#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
template <typename T>
struct[[nodiscard]] vector3
{
    union {
        struct
        {
            T x, y, z;
        };
        struct
        {
            T r, g, b;
        };
        struct
        {
            T width, height, depth;
        };
        T elements[3];
    };

    vector3() noexcept;
    explicit vector3(T repeated_float) noexcept;
    vector3(T fx, T fy, T fz) noexcept;
};

//static_assert(sizeof(vector3) == sizeof(float) * 3, "vector3 should only be three floats");
template <typename T>
constexpr void operator+=(vector3<T>& v, const vector3<T>& adding_vector) noexcept;
template <typename T>
constexpr void operator-=(vector3<T>& v, const vector3<T>& subtracting_vector) noexcept;
template <typename T>
constexpr void operator*=(vector3<T>& v, float scale) noexcept;
template <typename T>
constexpr void operator/=(vector3<T>& v, float divisor) noexcept;
template <typename T>
constexpr vector3<T> operator-(const vector3<T>& v) noexcept;
template <typename T>
constexpr vector3<T> operator+(const vector3<T>& v1, const vector3<T>& v2) noexcept;
template <typename T>
constexpr vector3<T> operator-(const vector3<T>& v1, const vector3<T>& v2) noexcept;
template <typename T>
constexpr vector3<T> operator*(const vector3<T>& v, float scale) noexcept;
template <typename T>
constexpr vector3<T> operator*(float scale, const vector3<T>& v) noexcept;
template <typename T>
constexpr vector3<T> operator/(const vector3<T>& v, float divisor) noexcept;

template <typename T>
[[nodiscard]]constexpr  bool operator==(const vector3<T>& v1, const vector3<T>& v2) noexcept;
template <typename T>
[[nodiscard]]constexpr  bool operator!=(const vector3<T>& v1, const vector3<T>& v2) noexcept;

template <typename T>
[[nodiscard]]constexpr  float dot(vector3<T> a, vector3<T> b) noexcept;
template <typename T>
constexpr vector3<T>             cross(vector3<T> a, vector3<T> b) noexcept;
template <typename T>
[[nodiscard]]constexpr  float magnitude_squared(vector3<T> a) noexcept;
template <typename T>
[[nodiscard]]constexpr  float magnitude(vector3<T> a) noexcept;
template <typename T>
constexpr vector3<T>             normalize(vector3<T> a) noexcept;
template <typename T>
[[nodiscard]]constexpr  float distance_between_squared(vector3<T> a, vector3<T> b) noexcept;
template <typename T>
[[nodiscard]]constexpr  float distance_between(vector3<T> a, vector3<T> b) noexcept;
template <typename T>
[[nodiscard]]constexpr  float angle_between(vector3<T> a, vector3<T> b) noexcept;

#pragma warning(pop)

#include <cassert>
#include <limits>
#include "vector3.inl"