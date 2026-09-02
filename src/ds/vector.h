/* ================================================================
*
*	Contains vector struct and vector math.
*
*	#Authors: The Kumor
*
* ================================================================ */

#pragma once

// STL
#include <cstdint>
#include <string>

namespace ds {

	// #TODO(kumor): Give this a move constructor

	template<typename T>
	struct Vec2
	{
		Vec2(T x, T y)
			: X(x), Y(y)
		{}

		Vec2(const Vec2& other)
			: X(other.x), Y(other.y)
		{}

		Vec2() = default;

		union
		{
			T X;
			T x;
		};

		union
		{
			T Y;
			T y;
		};

		std::wstring ToString()
		{
			return std::to_wstring(x) + L", " + std::to_wstring(y) + L"\n";
		}

		[[nodiscard]] bool operator==(const Vec2& other)
		{
			return other.x == x && other.y == y;
		}

		[[nodiscard]] Vec2 operator+(const Vec2& other)
		{
			return Vec2(x + other.x, y + other.y);
		}

		[[nodiscard]] void operator+=(const Vec2& other)
		{
			x += other.x;
			y += other.y;
		}

		[[nodiscard]] Vec2 operator-(const Vec2& other)
		{
			return Vec2(x - other.x, y - other.y);
		}

		[[nodiscard]] void operator-=(const Vec2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		[[nodiscard]] Vec2 operator*(const Vec2& other)
		{
			return Vec2(x * other.x, y * other.y);
		}

		[[nodiscard]] Vec2 operator*(std::int32_t scalar)
		{
			return Vec2(x * scalar, y * scalar);
		}

		[[nodiscard]] Vec2 operator/(const Vec2& other)
		{
			return Vec2(x / other.x, y / other.y);
		}
	};

	typedef Vec2<std::int32_t> Vec2i;

	using Size = Vec2i;
	using Pos = Vec2i;

};