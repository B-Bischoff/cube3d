#include "cube3d.h"


t_vector2_d	rot_vect_offset(t_vector2_d vector, t_vector2_d offset, double radian)
{
	set_vector_d(&vector, vector.x - offset.x, vector.y - offset.y);
	vector = rotate_vector_d(vector, radian + PI_2);
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
	const int mp_width = 300;
	const int mp_height = 300;
	const int mp_width_2 = mp_width / 2;
	const int mp_height_2 = mp_height / 2;

	const int mp_cell_size = 10;

	t_vector2_d center = {mp_width / 2, mp_height / 2};


	// Painting mp background
	draw_circle_color_radius(data, center, DARK_GRAY, mp_width_2);

	t_vector2_d offset = {
		data->player.pos.x - (int)(data->player.pos.x / mp_cell_size) * mp_cell_size,
		data->player.pos.y - (int)(data->player.pos.y / mp_cell_size) * mp_cell_size
	};


	// Collect points

	const int	dots_nb = mp_height / mp_cell_size;
	t_vector2_d dot_arrays[dots_nb + 1];

	int y1 = 0;
	for (float y = data->player.pos.y - mp_height_2; y <= data->player.pos.y + mp_height_2; y += mp_cell_size) 
	{
		int i = 0;
		int x1 = 0;
		for (float x = data->player.pos.x - mp_width_2; x <= data->player.pos.x + mp_width_2; x += mp_cell_size)
		{
			t_vector2_d dot = {x1, y1};
			set_vector_d(&dot, dot.x - offset.x, dot.y - offset.y); // Substracting offset makes the position accurate
			dot = rot_vect_offset(dot, center, data->player.angle + PI);

			t_vector2_d map_pos = {x, y};
			map_pos.y -= mp_cell_size;
			if (i > 0 && y > (data->player.pos.y - mp_height_2) && map_pos.x >= mp_cell_size)
			{
				t_vector2_d tri[3] = {dot, dot_arrays[i], dot_arrays[i - 1]};
				if (is_in_map(data, map_pos) && data->tab[(map_pos.y) / data->cell_size][(map_pos.x-mp_cell_size) / data->cell_size] == 1)
					if (is_in_mp_area(center, mp_width_2, tri))
						draw_triangle_color(data, tri, BLUE);
			}

			if (i < dots_nb && y > (data->player.pos.y - mp_height_2))
			{
				t_vector2_d tri[3] = {dot, dot_arrays[i], dot_arrays[i + 1]};
				if (is_in_map(data, map_pos) && data->tab[(map_pos.y) / data->cell_size][(map_pos.x) / data->cell_size] == 1)
					if (is_in_mp_area(center, mp_width_2, tri))
						draw_triangle_color(data, tri, BLUE);
			}


			dot_arrays[i] = dot;
			x1 += mp_cell_size;
			i++;
		}
		y1 += mp_cell_size;
	}

	draw_circle_empty(data, center, mp_width_2, 40);

	// Draw player
	draw_circle_color(data, center, WHITE);

}
