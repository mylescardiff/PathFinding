#pragma once
#include <cmath>
#include <Common.h>

namespace slth
{
	class Vector2f
	{

	public:

		float x;
		float y;

		/// <summary>
		/// Default Consturtor (Compile Time)
		/// </summary>
		SLTH_API constexpr Vector2f()
			: x(0)
			, y(0)
		{}

		/// <summary>
		/// Explicit Constructor (Compile Time)
		/// </summary>
		SLTH_API constexpr Vector2f(float x, float y)
			: x(x)
			, y(y)
		{}

		/// <summary>
		/// Gets a 1-D array index from an x, y position
		/// </summary>
		/// <param name="x">X</param>
		/// <param name="y">Y</param>
		/// <param name="width">The width of the map</param>
		/// <returns>Index position</returns>
		template<class T>
		SLTH_API const static size_t IndexFromPosition(const T x, const T y, const T width)
		{
			return static_cast<size_t>((width * y) + x);
		}

		/// <summary>
		/// Gets a Vector2 (x,y) from a 1-D array index. 
		/// </summary>
		/// <param name="index">The 1-D array index</param>
		/// <param name="width">The width of the map</param>
		/// <returns>A vector2 position</returns>
		SLTH_API const static Vector2f PositionFromIndex(const size_t index, const size_t width)
		{
			return Vector2f(static_cast<float>(std::floor(index / width)), static_cast<float>(std::floor(fmod(index, width))));
		}

		/// <summary>
		/// Gets the mathmatical determinant of 2 vectors
		/// </summary>
		/// <param name="vectorA">The first Vector2</param>
		/// <param name="vectorB">The second Vector2</param>
		/// <returns>The determinant of the 2 vectors</returns>
		SLTH_API const static float Determinant(const Vector2f vectorA, const Vector2f vectorB)
		{
			return vectorA.x * vectorB.y - vectorA.y * vectorB.x;
		}

		/// <summary>
		/// Gets the angle between two positions on the screen, using the UP Vector2 (0, -1) as "zero" rotation.
		/// </summary>
		/// <param name="vectorA"></param>
		/// <param name="vectorB"></param>
		/// <returns></returns>
		SLTH_API const static float AngleBetween(const Vector2f vectorA, const Vector2f vectorB)
		{
			Vector2f directionVector = vectorB - vectorA;
			directionVector.Normalize();

			float rads = atan2(directionVector.y, directionVector.x);

			// adding 90 here becuase the my "zero" rotation is up, this calculates from the right. 
			float degrees = RadiansToDegrees(rads) + 90.f; 

			if (degrees > 180.f)
				degrees -= 360.f;

			if (degrees < -180.f)
				degrees += 360.f;

			return degrees;
		}

		/// <summary>
		/// Gets the mathmatical dot product of two vectors (commutative)
		/// </summary>
		/// <param name="vectorA">The first Vector2</param>
		/// <param name="vectorB">The second Vector2</param>
		/// <returns></returns>
		SLTH_API const static float DotProduct(const Vector2f vectorA, const Vector2f vectorB)
		{
			return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
		}

		/// <summary>
		///  Round both elements of a Vector2 to the nearest whole number
		/// </summary>
		/// <returns>Rounded Vector2</returns>
		SLTH_API Vector2f Round()
		{
			return Vector2f(std::round(x), std::round(y));
		}

		/// <summary>
		/// Get the magnitude of the Vector2
		/// </summary>
		/// <returns></returns>
		SLTH_API const float Magnitude() const
		{
			return std::sqrt(x * x + y * y);
		}

		/// <summary>
		/// Makes the magnitude of the Vector2 1.0f
		/// </summary>
		SLTH_API void Normalize()
		{
			float mag = Magnitude();
			x = x / mag;
			y = y / mag;

		}

		/// <summary>
		/// Gets the distance from this Vector2 to another
		/// </summary>
		/// <param name="otherVector"></param>
		/// <returns></returns>
		SLTH_API const float DistanceTo(const Vector2f otherVector)
		{
			return abs(sqrt((x - otherVector.x) * (x - otherVector.x) + (y - otherVector.y) * (y - otherVector.y)));
		}

		SLTH_API const float DistanceSquaredTo(const Vector2f otherVector)
		{
			return abs((x - otherVector.x) * (x - otherVector.x) + (y - otherVector.y) * (y - otherVector.y));
		}


		/// <summary>
		/// Gets the direction of another Vector2 
		/// </summary>
		/// <param name="target"></param>
		/// <returns></returns>
		SLTH_API const Vector2f BearingTo(const Vector2f target)
		{
			Vector2f diff = target - *this;
			diff.Normalize();
			return diff;
		}


		/// <summary>
		/// Rotates the vecror around the origin by degrees, WARNING: this is not super precicse for floats, round to int if you need it to be exact
		/// </summary>
		/// <param name="degrees">Rotation angle in degrees</param>
		/// <returns>A rotated Vector2</returns>
		SLTH_API Vector2f Rotate(float degrees)
		{
			float rads = DegreesToRadians(degrees); // conversion to radians
			float newX = (x * cos(rads)) - (y * std::sin(rads));
			float newY = (x * sin(rads)) + (y * std::cos(rads));

			return { newX, newY };
		}
	
		/// <summary>
		/// Rotates a Vector2 around another Vector2 by the specified angle
		/// </summary>
		/// <param name="degrees">The rotation in degrees</param>
		/// <param name="center">The center point (Vector2) to rotate around</param>
		/// <returns></returns>
		/// <credit>https://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d</credit>
		SLTH_API Vector2f Rotate(float degrees, Vector2f center)
		{
			float rads = degrees * (kPi / 180.f);

			Vector2f returnValue = *this;

			returnValue.x -= center.x;
			returnValue.y -= center.y;

			Vector2f newPos =
			{
				returnValue.x * std::cos(rads) - returnValue.y * std::sin(rads),
				returnValue.x * std::sin(rads) + returnValue.y * std::cos(rads)
			};

			returnValue.x = newPos.x + center.x;
			returnValue.y = newPos.y + center.y;

			return returnValue;
		}

		/// <summary>
		/// Equality operator
		/// </summary>
		/// <param name="other">The Vector2 to compare this one to</param>
		/// <returns>True if both elements of the Vector2 are the same, false otherwise</returns>
		SLTH_API bool operator==(const Vector2f& other) const
		{
			return x == other.x && y == other.y;
		}

		/// <summary>
		/// Inequality operator
		/// </summary>
		/// <param name="other">The Vector2 to compare this one to</param>
		/// <returns>False if both elements of the Vector2 are the same, True otherwise</returns>
		SLTH_API bool operator!=(const Vector2f& other) const
		{
			return !(*this == other);
		}

		/// <summary>
		/// Addition assignment operator
		/// </summary>
		/// <param name="right">The Vector2 to add</param>
		/// <returns>The newly constructed Vector2</returns>
		SLTH_API Vector2f& operator+=(const Vector2f& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		/// <summary>
		/// Subtraction assignment operator
		/// </summary>
		/// <param name="right">The Vector2 to subtract</param>
		/// <returns>the newly constructed Vector2 that is equal to the difference between the two vectors</returns>
		SLTH_API Vector2f& operator-=(const Vector2f& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		/// <summary>
		/// Addition operator
		/// </summary>
		/// <param name="left">The first Vector2</param>
		/// <param name="right">The second Vector2</param>
		/// <returns>A newly constructed vector representing the addition of the two </returns>
		SLTH_API friend Vector2f operator+(const Vector2f& left, const Vector2f& right)
		{
			return Vector2f(left.x + right.x, left.y + right.y);
		}

		/// <summary>
		/// Multiplication operator
		/// </summary>
		/// <param name="left">The first Vector2</param>
		/// <param name="right">The second Vector2</param>
		/// <returns>A newly constructed vector representing the product of the two </returns>
		SLTH_API friend Vector2f operator*(const Vector2f& left, const float right)
		{
			return Vector2f(left.x * right, left.y * right);
		}

		/// <summary>
		/// Division operator
		/// </summary>
		/// <param name="left">The Vector2</param>
		/// <param name="right">The scalar to divide by</param>
		/// <returns>A newly constructed vector representing the quotient of the two </returns>
		SLTH_API friend Vector2f operator/(Vector2f& left, const float right)
		{
			return Vector2f(left.x / right, left.y / right);
		}


		/// <summary>
		/// Subtraction operator
		/// </summary>
		/// <param name="right">The Vector2 to subtract</param>
		/// <returns>the newly constructed Vector2 that is equal to the difference between the two vectors</returns>
		SLTH_API friend Vector2f operator-(const Vector2f& left, const Vector2f& right)
		{
			return Vector2f(left.x - right.x, left.y - right.y);

		}

		/// <summary>
		/// Division operator
		/// </summary>
		/// <param name="right">The Vector2 to divide by</param>
		/// <returns>the newly constructed Vector2 that is equal to the quotient of the two vectors</returns>
		SLTH_API friend Vector2f operator/(const Vector2f& left, const float right)
		{
			return Vector2f(left.x / right, left.y / right);
		}

		/// <summary>
		/// Lerp (Linear Interpolation) between two vectors by a given amount
		/// </summary>
		/// <param name="vec">The vector to lerp</param>
		/// <param name="amount">The amount to lerp it by</param>
		/// <returns>The result of the lerp</returns>
		SLTH_API static float Lerp(slth::Vector2f vec, float amount)
		{
			return (1.0f - amount) * vec.x + amount * vec.y;
		}

		/// <summary>
		/// Tests if a vector is close enough to another one by a given threshold
		/// </summary>
		/// <param name="otherVector">The other vector</param>
		/// <param name="threshold">The distance that qualifies it as "close enough"</param>
		/// <returns>True if it's close enought, false otherwise</returns>
		SLTH_API bool IsApproximatleyEqualTo(slth::Vector2f otherVector, float threshold = 0.1)
		{
			return DistanceTo(otherVector) <= threshold;
		}

		/// <summary>
		/// Converts Radians to Degrees
		/// </summary>
		/// <param name="rads">Input radians</param>
		/// <returns>Degrees</returns>
		SLTH_API const static float RadiansToDegrees(float rads)
		{
			return rads * 57.2958f;
		}

		/// <summary>
		/// Converts  to Radians 
		/// </summary>
		/// <param name="degrees">Input degrees</param>
		/// <returns>Radians</returns>
		SLTH_API const static float DegreesToRadians(float degrees)
		{
			return degrees * (kPi / 180.f);
		}

	};
}