#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) // warning C4201 : nonstandard extension used : nameless struct / union
template <typename T>
struct [[nodiscard]] vector4
{
	union {
		struct
		{
			T x, y, z, w;
		};
		struct
		{
			T r, g, b, w;
		};
		struct
		{
			T width, height, depth;
		};
		T elements[4];
	};

	vector4() noexcept;
	vector4(T fx, T fy, T fz, T fw) noexcept;
};

#include "vector4.inl"