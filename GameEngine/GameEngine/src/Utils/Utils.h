#pragma once
#include "Ogre.h"

/**
UTIL MATHEMATICAL CLASSES
*/

class Vec2
{
public:
	Vec2()
		: x(0.0f), y(0.0f)
	{}

	Vec2(float x, float y)
		: x(x), y(y)
	{}

	Vec2(Ogre::Vector2 vec)
		: x(vec.x), y(vec.y)
	{}

	Vec2 operator+(Vec2 const& v)
	{
		return Vec2(
			x + v.x,
			y + v.y);
	}

	Vec2 operator+=(Vec2 const& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	Vec2 operator-(Vec2 const& v)
	{
		return Vec2(
			x - v.x,
			y - v.y);
	}

	Vec2 operator-=(Vec2 const& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	Vec2 operator=(Ogre::Vector2 vec) {
		x = vec.x;
		y = vec.y;
		return *this;
	}


	float x, y;
};

class Vec3
{
public:
	Vec3()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	Vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	Vec3(Ogre::Vector3 vec)
		: x(vec.x), y(vec.y), z(vec.z)
	{}

	Vec3 operator+(Vec3 const& rhs) const
	{
		return Vec3(
			x + rhs.x,
			y + rhs.y,
			z + rhs.z);
	}

	Vec3 operator+=(Vec3 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vec3 operator-(Vec3 const& rhs) const
	{
		return Vec3(
			x - rhs.x,
			y - rhs.y,
			z - rhs.z);
	}

	Vec3 operator-=(Vec3 const& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	Vec3 operator*(Vec3 const& rhs) const
	{
		return Vec3(
			x * rhs.x,
			y * rhs.y,
			z * rhs.z);
	}

	Vec3 operator*=(Vec3 const& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;

		return *this;
	}

	Vec3 operator*(float rhs) const
	{
		return Vec3(
			x * rhs,
			y * rhs,
			z * rhs);
	}

	Vec3 operator*=(float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
	}

	Vec3 operator=(Ogre::Vector3 vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	Ogre::Vector3 toOgre() {
		return Ogre::Vector3(x, y, z);
	}

	float x, y, z;
};

class Vec4
{
public:
	Vec4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	Vec4(float x, float y, float z)
		: x(x), y(y), z(z), w(0.0f)
	{}

	Vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}

	Vec4(Ogre::Vector4 vec)
		: x(vec.x), y(vec.y), z(vec.z), w(vec.w)
	{}

	Vec4 operator+(Vec4 const& v) const
	{
		return Vec4(
			x + v.x,
			y + v.y,
			z + v.z,
			w + v.w);
	}

	Vec4 operator+=(Vec4 const& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

	Vec4 operator-(Vec4 const& v) const
	{
		return Vec4(
			x - v.x,
			y - v.y,
			z - v.z,
			w - v.w);
	}

	Vec4 operator-=(Vec4 const& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	Vec4 operator=(Ogre::Vector4 vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}


	float x, y, z, w;
};

class Mat44
{
public:
	Mat44()
	{
		//@formatter:off
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		//@formatter:on
	}


	Mat44 operator*(Mat44 const& rhs)
	{
		Mat44 result;

		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				float sum = 0.0f;

				for (int i = 0; i < 4; ++i)
				{
					sum += m[row][i] * rhs.m[i][col];
				}

				result.m[row][col] = sum;
			}
		}

		return result;
	}


	Vec4 operator*(Vec4 const& rhs)
	{
		return Vec4(
			(rhs.x * m[0][0]) + (rhs.y * m[0][1]) + (rhs.z * m[0][2]) + (rhs.w * m[0][3]),
			(rhs.x * m[1][0]) + (rhs.y * m[1][1]) + (rhs.z * m[1][2]) + (rhs.w * m[1][3]),
			(rhs.x * m[2][0]) + (rhs.y * m[2][1]) + (rhs.z * m[2][2]) + (rhs.w * m[2][3]),
			(rhs.x * m[3][0]) + (rhs.y * m[3][1]) + (rhs.z * m[3][2]) + (rhs.w * m[3][3]));
	}


	float m[4][4];
};

