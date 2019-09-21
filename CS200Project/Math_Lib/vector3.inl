/************************************************
 *NAME              : sangmin.kim
 *ASSIGNMENT NUMBER : 1
 *COURSE NAME       : CS230
 *TERM              : Spring 2019
 ************************************************/
#include "vector3.hpp"
#include <cassert>
#include <limits>

template <typename T>
vector3<T>::vector3() noexcept
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}
template <typename T>
vector3<T>::vector3(T repeated_float) noexcept
{
    x = repeated_float;
    y = repeated_float;
    z = repeated_float;
}
template <typename T>
vector3<T>::vector3(T fx, T fy, T fz) noexcept
{
    x = fx;
    y = fy;
    z = fz;
}
template <typename T>
constexpr void operator+=(vector3<T>& v, const vector3<T>& adding_vector) noexcept
{
    v.x += adding_vector.x;
    v.y += adding_vector.y;
    v.z += adding_vector.z;
}
template <typename T>
constexpr void operator-=(vector3<T>& v, const vector3<T>& subtracting_vector) noexcept
{
    v.x -= subtracting_vector.x;
    v.y -= subtracting_vector.y;
    v.z -= subtracting_vector.z;
}
template <typename T>
constexpr void operator*=(vector3<T>& v, float scale) noexcept
{
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
}
template <typename T>
constexpr void operator/=(vector3<T>& v, float divisor) noexcept
{
    assert(divisor != 0);
    v.x /= divisor;
    v.y /= divisor;
    v.z /= divisor;
}
template <typename T>
constexpr vector3<T> operator-(const vector3<T>& v) noexcept
{
    vector3<T> result_vec;

    result_vec.x = -(v.x);
    result_vec.y = -(v.y);
    result_vec.z = -(v.z);

    return result_vec;
}
template <typename T>
constexpr vector3<T> operator+(const vector3<T>& v1, const vector3<T>& v2) noexcept
{
    vector3<T> result_vec;
    result_vec.x = v1.x + v2.x;
    result_vec.y = v1.y + v2.y;
    result_vec.z = v1.z + v2.z;

    return result_vec;
}
template <typename T>
constexpr vector3<T> operator-(const vector3<T>& v1, const vector3<T>& v2) noexcept
{
    vector3<T> result_vec;

    v2.x > v1.x ? result_vec.x = v2.x - v1.x : result_vec.x = v1.x - v2.x;
    v2.y > v1.y ? result_vec.y = v2.y - v1.y : result_vec.y = v1.y - v2.y;
    v2.z > v1.z ? result_vec.z = v2.z - v1.z : result_vec.z = v1.z - v2.z;

    return result_vec;
}
template <typename T>
constexpr vector3<T> operator*(const vector3<T>& v, float scale) noexcept
{
    vector3<T> result_vec(v.x * scale, v.y * scale, v.z * scale);

    return result_vec;
}
template <typename T>
constexpr vector3<T> operator*(float scale, const vector3<T>& v) noexcept
{
    vector3<T> result_vec(scale * v.x, scale * v.y, scale * v.z);

    return result_vec;
}
template <typename T>
constexpr vector3<T> operator/(const vector3<T>& v, float divisor) noexcept
{
    assert(divisor != 0);
    vector3<T> result_vec;

    result_vec.x = v.x / divisor;
    result_vec.y = v.y / divisor;
    result_vec.z = v.z / divisor;

    return result_vec;
}

template <typename T>
constexpr bool operator==(const vector3<T>& v1, const vector3<T>& v2) noexcept
{
    if (std::abs(v2.x - v1.x) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.y - v1.y) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.z - v1.z) <= std::numeric_limits<float>::epsilon())
    {
        return true;
    }
    return false;
}

template <typename T>
constexpr bool operator!=(const vector3<T>& v1, const vector3<T>& v2) noexcept
{
    if (std::abs(v2.x - v1.x) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.y - v1.y) <= std::numeric_limits<float>::epsilon() &&
        std::abs(v2.z - v1.z) <= std::numeric_limits<float>::epsilon())
    {
        return false;
    }
    else
        return true;
}
template <typename T>
constexpr float dot(vector3<T> a, vector3<T> b) noexcept
{
    float dot_product = 0.0f;

    dot_product += (a.x * b.x);
    dot_product += (a.y * b.y);
    dot_product += (a.z * b.z);

    return dot_product;
}
template <typename T>
constexpr vector3<T> cross(vector3<T> a, vector3<T> b) noexcept
{
    vector3<T> result_vec;

    result_vec.x = ((a.y * b.z) - (a.z * b.y));
    result_vec.y = -((a.x * b.z) - (a.z * b.x));
    result_vec.z = ((a.x * b.y) - (a.y * b.x));

    return result_vec;
}
template <typename T>
constexpr float magnitude_squared(vector3<T> a) noexcept
{
    float magnitude_val_squared = 0.0f;

    magnitude_val_squared += dot(a, a);

    return magnitude_val_squared;
}
template <typename T>
constexpr float magnitude(vector3<T> a) noexcept
{
    float magnitude_val = 0.0f;

    magnitude_val += sqrt(dot(a, a));
    return magnitude_val;
}
template <typename T>
constexpr vector3<T> normalize(vector3<T> a) noexcept
{
    vector3<T> result_vec;
    float   magnitude_val = 0.0f;

    magnitude_val = magnitude(a);
    result_vec.x = a.x / magnitude_val;
    result_vec.y = a.y / magnitude_val;
    result_vec.z = a.z / magnitude_val;

    return result_vec;
}
template <typename T>
constexpr float distance_between_squared(vector3<T> a, vector3<T> b) noexcept
{
    float distance_squared = 0.0f;
    float distance_x = 0.0f;
    float distance_y = 0.0f;
    float distance_z = 0.0f;

    distance_x = b.x - a.x;
    distance_y = b.y - a.y;
    distance_z = b.z - a.z;

    distance_squared = ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z));

    return distance_squared;
}
template <typename T>
constexpr float distance_between(vector3<T> a, vector3<T> b) noexcept
{
    float distance = 0.0f;
    float distance_x = 0.0f;
    float distance_y = 0.0f;
    float distance_z = 0.0f;

    distance_x = b.x - a.x;
    distance_y = b.y - a.y;
    distance_z = b.z - a.z;

    distance = sqrt((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z));

    return distance;
}
template <typename T>
constexpr float angle_between(vector3<T> a, vector3<T> b) noexcept
{
    float cos_theta = dot(a, b) / (magnitude(a) * magnitude(b));
    float radian = acosf(cos_theta);
    float angle = radian;

    return angle;
}

