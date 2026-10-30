#pragma once

namespace math_helper
{
	template<typename T>
	T clamp(T value, T minValue, T maxValue)
	{
		if (value < minValue) return minValue;
		if (value > maxValue) return maxValue;
		return value;
	}

	template<typename T>
	T Lerp(T start, T end, T t)
	{
		return (end - start) * t + start;
	}

}