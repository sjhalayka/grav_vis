#pragma once

#include "uv_camera.h"
#include "mesh.h"


#include <cstdlib>
#include <GL/glut.h>


#include <vector>
using std::vector;

#include <string>
using std::string;

#include <sstream>
using std::ostringstream;
using std::istringstream;


void idle_func(void);
void init_opengl(const int &width, const int &height);
void reshape_func(int width, int height);
void display_func(void);
void keyboard_func(unsigned char key, int x, int y);
void mouse_func(int button, int state, int x, int y);
void motion_func(int x, int y);
void passive_motion_func(int x, int y);
void render_string(int x, const int y, void *font, const string &text);
void draw_objects(void);

class graviton
{
public:
	vertex_3 pos;
	vertex_3 vel;
};

vector<graviton> gravitons;

const float mass = 100;

const float pi = 4.0f * atanf(1.0f);

const float c = 10;
const float c2 = c * c;
const float c3 = c * c * c;
const float c4 = c * c * c * c;
const float c5 = c * c * c * c * c;

const float G = 1 / 10.0f;
const float hbar = 1 / 10.0f;

const float lp = sqrtf(hbar * G / c3);
const float lp2 = lp * lp;

const float Mp = sqrt(hbar*c/G);
const float Mp2 = Mp * Mp;


const float tp = sqrt(hbar * G / c5);

const float steps_per_second = c / lp;

const float Rs = 2 * G * mass / c2;
const float As = 4 * pi * Rs * Rs;
//const float n = As / (4 * lp2 * logf(2.0f));
const float n = 4 * pi * mass * mass / (logf(2.0f) * Mp2);




float grid_min = -1.5;
float grid_max = 1.5;
size_t res = 100;




vector<vector<triangle>> triangles;
vector<vector<vertex_3>> face_normals;
vector<vector<vertex_3>> vertices;
vector<vector<vertex_3>> vertex_normals;

vertex_3 background_colour(0.0f, 0.0f, 0.0f);
vertex_3 control_list_colour(0.9f, 0.9f, 0.9f);






bool draw_mesh = true;
bool draw_axis = true;
bool draw_control_list = true;
bool smooth_shading = false;

uv_camera main_camera;

GLint win_id = 0;
GLint win_x = 800, win_y = 600;
float camera_w = 4;
float camera_fov = 45;
float camera_x_transform = 0;
float camera_y_transform = 0;
float u_spacer = 0.01;
float v_spacer = 0.5*u_spacer;
float w_spacer = 0.1;
float camera_near = 0.01;
float camera_far = 30.0;

bool lmb_down = false;
bool mmb_down = false;
bool rmb_down = false;
int mouse_x = 0;
int mouse_y = 0;






void tesselate_field(const vector<float>& values, vector<triangle>& triangle_list, const float& isovalue, const float& grid_min, const float& grid_max, const size_t& res)
{
	triangle_list.clear();

	const float step_size = (grid_max - grid_min) / (res - 1);

	for (size_t x = 0; x < res - 1; x++)
	{
		for (size_t y = 0; y < res - 1; y++)
		{
			for (size_t z = 0; z < res - 1; z++)
			{
				grid_cube temp_cube;

				size_t x_offset = 0;
				size_t y_offset = 0;
				size_t z_offset = 0;

				// Setup vertex 0
				x_offset = 0;
				y_offset = 0;
				z_offset = 0;
				temp_cube.vertex[0].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[0].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[0].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[0] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 1
				x_offset = 1;
				y_offset = 0;
				z_offset = 0;
				temp_cube.vertex[1].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[1].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[1].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[1] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 2
				x_offset = 1;
				y_offset = 0;
				z_offset = 1;
				temp_cube.vertex[2].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[2].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[2].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[2] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 3
				x_offset = 0;
				y_offset = 0;
				z_offset = 1;
				temp_cube.vertex[3].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[3].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[3].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[3] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 4
				x_offset = 0;
				y_offset = 1;
				z_offset = 0;
				temp_cube.vertex[4].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[4].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[4].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[4] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 5
				x_offset = 1;
				y_offset = 1;
				z_offset = 0;
				temp_cube.vertex[5].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[5].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[5].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[5] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 6
				x_offset = 1;
				y_offset = 1;
				z_offset = 1;
				temp_cube.vertex[6].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[6].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[6].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[6] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Setup vertex 7
				x_offset = 0;
				y_offset = 1;
				z_offset = 1;
				temp_cube.vertex[7].x = grid_min + ((x + x_offset) * step_size);
				temp_cube.vertex[7].y = grid_min + ((y + y_offset) * step_size);
				temp_cube.vertex[7].z = grid_min + ((z + z_offset) * step_size);
				temp_cube.value[7] = values[(x + x_offset) * (res) * (res)+(y + y_offset) * (res)+(z + z_offset)];

				// Generate triangles from cube
				triangle temp_triangle_array[5];

				short unsigned int number_of_triangles_generated = tesselate_grid_cube(isovalue, temp_cube, temp_triangle_array);

				for (short unsigned int i = 0; i < number_of_triangles_generated; i++)
				{
					triangle_list.push_back(temp_triangle_array[i]);
				}
			}
		}
	}
}




void convert_points_to_triangles(const vector<graviton>& gravitons,
	float isovalue,
	size_t res,
	float grid_min, float grid_max,
	vector<triangle>& triangles)
{
	vector<float> field;
	field.resize(res * res * res, 0);

	float curr_x_min = grid_min;
	float curr_y_min = grid_min;
	float curr_z_min = grid_min;
	float curr_x_max = grid_max;
	float curr_y_max = grid_max;
	float curr_z_max = grid_max;

	float x_extent = curr_x_max - curr_x_min;
	float y_extent = curr_y_max - curr_y_min;
	float z_extent = curr_z_max - curr_z_min;

	for (size_t i = 0; i < gravitons.size(); i++)
	{
		float x_location = gravitons[i].pos.x - curr_x_min;
		size_t x_index = static_cast<size_t>(static_cast<double>(res) * (x_location / x_extent));

		if (x_index >= res)
			x_index = res - 1;

		float y_location = gravitons[i].pos.y - curr_y_min;
		size_t y_index = static_cast<size_t>(static_cast<double>(res) * (y_location / y_extent));

		if (y_index >= res)
			y_index = res - 1;

		float z_location = gravitons[i].pos.z - curr_z_min;
		size_t z_index = static_cast<size_t>(static_cast<double>(res) * (z_location / z_extent));

		if (z_index >= res)
			z_index = res - 1;

		size_t index = z_index * res * res;
		index += y_index * res;
		index += x_index;

		field[index] += 1;
	}

	tesselate_field(field, triangles, isovalue, grid_min, grid_max, res);
}



vertex_3 get_point_on_sphere(float radius)
{
	double u = rand() / static_cast<double>(RAND_MAX);
	double v = rand() / static_cast<double>(RAND_MAX);

	double theta = 2 * pi * u;
	double phi = acos(2 * v - 1.0);

	vertex_3 pos;

	pos.x = radius * cos(theta) * sin(phi);
	pos.y = radius * sin(theta) * sin(phi);
	pos.z = radius * cos(phi);

	return pos;
}

void proceed(void)
{
	const float dt = tp;

	// move gravitons
	for (size_t i = 0; i < gravitons.size(); i++)
		gravitons[i].pos = gravitons[i].pos + gravitons[i].vel * dt;

	// n oscillators emit n gravitons, once per planck time
	for (size_t i = 0; i < n; i++)
	{
		double u = rand() / static_cast<double>(RAND_MAX);
		double v = rand() / static_cast<double>(RAND_MAX);

		double theta = 2 * pi * u;
		double phi = acos(2 * v - 1.0);

		graviton g;

		g.pos = get_point_on_sphere(Rs);
		g.vel = get_point_on_sphere(c);

		if (g.pos.dot(g.vel) < 0)
		{
			g.vel.x = -g.vel.x;
			g.vel.y = -g.vel.y;
			g.vel.z = -g.vel.z;
		}

		g.pos.x += 1.0f;

		gravitons.push_back(g);
	}

	for (size_t i = 0; i < n; i++)
	{
		double u = rand() / static_cast<double>(RAND_MAX);
		double v = rand() / static_cast<double>(RAND_MAX);

		double theta = 2 * pi * u;
		double phi = acos(2 * v - 1.0);

		graviton g;

		g.pos = get_point_on_sphere(Rs);
		g.vel = get_point_on_sphere(c);

		if (g.pos.dot(g.vel) < 0)
		{
			g.vel.x = -g.vel.x;
			g.vel.y = -g.vel.y;
			g.vel.z = -g.vel.z;
		}

		g.pos.x -= 1.0f;

		gravitons.push_back(g);
	}

	for (vector<graviton>::const_iterator ci = gravitons.begin(); ci != gravitons.end(); )
	{
		const vertex_3 p = ci->pos;

		if (p.x < grid_min || p.x > grid_max ||
			p.y < grid_min || p.y > grid_max ||
			p.z < grid_min || p.z > grid_max)
		{
			gravitons.erase(ci);
			ci = gravitons.begin();
		}
		else
			ci++;
	}

}