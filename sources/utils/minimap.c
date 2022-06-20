#include "cube3d.h"


t_vector2_d	rot_vect_offset(t_vector2_d vector, t_vector2_d offset, double radian)
{
	set_vector_d(&vector, vector.x - offset.x, vector.y - offset.y);
	vector = rotate_vector_d(vector, radian);
	set_vector_d(&vector, vector.x + offset.x, vector.y + offset.y);
	return (vector);
}

int	is_in_mp_area(t_vector2_d center, int max_length, t_vector2_d tri[3])
{
	int	length;

	for (int i = 0; i < 3; i++)
	{
		length = get_vector_d_length_squared(center, tri[i]);
		if (length > max_length * max_length)
			return (0);
	}
	return (1);
}

/*
	mp stands for minimap
*/
void	print_minimap(t_data *data)
{
	// Constants
	const int mp_radius = 300;
	const int mp_radius_2 = mp_radius / 2;
	const int mp_cell_size = 10;

	t_vector2_d center = {mp_radius_2, mp_radius_2}; // center of the minimap

	// Painting mp background
	draw_circle_color_radius(data, center, DARK_GRAY, mp_radius_2);

	// Offset is the distance between the player and the top left corner of his cell position
	t_vector2_d offset = {
		data->player.pos.x - (int)(data->player.pos.x / mp_cell_size) * mp_cell_size,
		data->player.pos.y - (int)(data->player.pos.y / mp_cell_size) * mp_cell_size
	};

	const int	dots_nb = mp_radius / mp_cell_size;
	t_vector2_d dot_arrays[dots_nb + 1];


	t_vector2_d dot = {0, 0};
	for (float y = data->player.pos.y - mp_radius_2; y <= data->player.pos.y + mp_radius_2; y += mp_cell_size) 
	{
		int i = 0;
		dot.x = 0;
		for (float x = data->player.pos.x - mp_radius_2; x <= data->player.pos.x + mp_radius_2; x += mp_cell_size)
		{
			// Placing dot on minimap depending on the player direction
			t_vector2_d	temp_dot = dot;
			set_vector_d(&temp_dot, dot.x - offset.x, dot.y - offset.y); // Substracting offset makes the position accurate
			temp_dot = rot_vect_offset(temp_dot, center, get_angle_f(data->player.pos, vector_d_to_f(data->player.view_dst_pos)) - PI_2);

			t_vector2_d map_pos = {floor(x), floor(y)};

			map_pos.y -= mp_cell_size; // Changing dot detection

			if (i < dots_nb - 1 && y > data->player.pos.y - mp_radius_2)
			{
				t_vector2_d tri[3] = {temp_dot, dot_arrays[i], dot_arrays[i + 1]};
				if (is_in_mp_area(center, mp_radius_2, tri) && is_colliding_cell(data, map_pos.x, map_pos.y, 1))
					draw_triangle_color(data, tri, RED);
			}
			map_pos.x -= mp_cell_size;
			if (y > data->player.pos.y - mp_radius_2 && i > 0)
			{
				t_vector2_d tri[3] = {temp_dot, dot_arrays[i], dot_arrays[i - 1]};
				if (is_in_mp_area(center, mp_radius_2, tri) && is_colliding_cell(data, map_pos.x, map_pos.y, 1))
					draw_triangle_color(data, tri, BLUE);
			}

			dot_arrays[i] = temp_dot;
			dot.x += mp_cell_size;
			i++;
		}
		dot.y += mp_cell_size;
	}

	draw_circle_empty(data, center, mp_radius_2, 40); // Draw mp borders
	draw_circle_color(data, center, WHITE); // Draw player
}
