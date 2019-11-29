template <typename T>
vector4<T>::vector4() noexcept
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

template <typename T>
vector4<T>::vector4(T fx, T fy, T fz, T fw) noexcept
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}