#pragma once
#include <math.h>
#include <cmath>
#include <Common.h>

namespace slth
{
	class Vector2
	{

	public:

		float x;
		float y;

		SLTH_API Vector2()
			: x(0)
			, y(0)
		{}

		SLTH_API Vector2(float x, float y)
			: x(x)
			, y(y)
		{}

		SLTH_API ~Vector2() {}

		// position helper functions
		SLTH_API static float IndexFromPosition(float x, float y, float width)
		{
			return (width * y) + x;
		}
		SLTH_API static Vector2 PositionFromIndex(int index, int width)
		{
			return Vector2(static_cast<float>(floor(index / width)), static_cast<float>(floor(fmod(index, width))));
		}

		// finds the direction of another object on the screen
		SLTH_API Vector2 BearingTo(Vector2 target, float speed)
		{
			float xDiff = x - target.x;
			float yDiff = y - target.y;
			float xChange = -(xDiff / yDiff) * speed;
			return Vector2(xChange, -speed);
		}

		// equality 
		SLTH_API bool operator==(const Vector2& other) const
		{
			if (x == other.x && y == other.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		SLTH_API bool operator!=(const Vector2& other) const
		{
			return !(*this == other);
		}

		// addition
		SLTH_API Vector2& operator+=(const Vector2& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}
		// subtraction
		SLTH_API Vector2& operator-=(const Vector2& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		SLTH_API friend Vector2 operator+(const Vector2& left, const Vector2& right)
		{
			return Vector2(left.x + right.x, left.y + right.y);
		}

		SLTH_API friend Vector2 operator*(const Vector2& left, const float right)
		{
			return Vector2(left.x * right, left.y * right);
		}
		// subtraction 
		SLTH_API friend Vector2 operator-(const Vector2& left, const Vector2& right)
		{
			return Vector2(left.x - right.x, left.y - right.y);

		}
		SLTH_API friend Vector2 operator/(const Vector2& left, const float right)
		{
			return Vector2(left.x / right, left.y / right);

		}
	};
}


