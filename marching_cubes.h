#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#include <cmath>
using std::fabs;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;


#include <limits>
using std::numeric_limits;


// Modified from Paul Bourke, Polygonising a Scalar Field
// http://local.wasp.uwa.edu.au/~pbourke/geometry/polygonise/index.html




class vertex_3
{
public:
	inline vertex_3(void) : x(0.0f), y(0.0f), z(0.0f), index(0) { /*default constructor*/ }
	inline vertex_3(const float src_x, const float src_y, const float src_z, const size_t src_index) : x(src_x), y(src_y), z(src_z), index(src_index) { /* custom constructor */ }
	inline vertex_3(const float src_x, const float src_y, const float src_z) : x(src_x), y(src_y), z(src_z), index(0) { /* custom constructor */ }

	inline bool operator==(const vertex_3& right) const
	{
		if (right.x == x && right.y == y && right.z == z)
			return true;
		else
			return false;
	}

	inline bool operator<(const vertex_3& right) const
	{
		if (right.x > x)
			return true;
		else if (right.x < x)
			return false;

		if (right.y > y)
			return true;
		else if (right.y < y)
			return false;

		if (right.z > z)
			return true;
		else if (right.z < z)
			return false;

		return false;
	}

	inline const vertex_3& operator-(const vertex_3& right) const
	{
		static vertex_3 temp;

		temp.x = this->x - right.x;
		temp.y = this->y - right.y;
		temp.z = this->z - right.z;

		return temp;
	}

	inline const vertex_3& operator+(const vertex_3& right) const
	{
		static vertex_3 temp;

		temp.x = this->x + right.x;
		temp.y = this->y + right.y;
		temp.z = this->z + right.z;

		return temp;
	}

	inline const vertex_3& operator*(const float& right) const
	{
		static vertex_3 temp;

		temp.x = this->x * right;
		temp.y = this->y * right;
		temp.z = this->z * right;

		return temp;
	}

	inline const vertex_3& cross(const vertex_3& right) const
	{
		static vertex_3 temp;

		temp.x = y * right.z - z * right.y;
		temp.y = z * right.x - x * right.z;
		temp.z = x * right.y - y * right.x;

		return temp;
	}

	inline float dot(const vertex_3& right) const
	{
		return x * right.x + y * right.y + z * right.z;
	}

	inline const float self_dot(void)
	{
		return x * x + y * y + z * z;
	}

	inline const float length(void)
	{
		return std::sqrt(self_dot());
	}

	inline const void normalize(void)
	{
		float len = length();

		if (0.0f != len)
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}

	inline void zero(void)
	{
		x = y = z = 0;
	}

	inline void rotate_x(const float& radians)
	{
		float t_y = y;

		y = t_y * cos(radians) + z * sin(radians);
		z = t_y * -sin(radians) + z * cos(radians);
	}

	inline void rotate_y(const float& radians)
	{
		float t_x = x;

		x = t_x * cos(radians) + z * -sin(radians);
		z = t_x * sin(radians) + z * cos(radians);
	}


	float x, y, z;
	size_t index;
};

class triangle
{
public:
	vertex_3 vertex[3];
};

class grid_cube
{
public:
	vertex_3 vertex[8];
	double value[8];
};

class marched_cube
{
public:
	vertex_3 centre_point;
	vector<triangle> triangles; // A small number of triangles.
};

vertex_3 vertex_interp(const double &isolevel, const vertex_3 p1, const vertex_3 p2, const double valp1, const double valp2);
short unsigned int tesselate_grid_cube(const double &isovalue, grid_cube grid, triangle *const triangles);


#endif
