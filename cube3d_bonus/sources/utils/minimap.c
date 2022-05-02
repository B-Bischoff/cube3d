#include "cube3d.h"


t_vector2_d	rot_vect_offset(t_vector2_d vector, t_vector2_d offset, double radian)
{
	set_vector_d(&vector, vector.x - offset.x, vector.y - offset.y);
	vector = rotate_vector_d(vector, radian + PI_2);
	set_vector_d(&vector, vector.x + offset.x, vector.y + offset.y);
	return (vector);
}

/*
	mp stands for minimap
*/
void	print_minimap(t_data *data)
{
	const int mp_width = 300;
	const int mp_height = 300;
	const int mp_width_2 = mp_width / 2;
	const int mp_height_2 = mp_height / 2;

	dprintf(1, "Player angle : %lf\n", radian_to_degree(data->player.angle));

	// Painting mp background
	for (int y = 0; y < mp_height; y++)
		for (int x = 0; x < mp_width; x++)
			my_mlx_pixel_put(data, x, y, DARK_GRAY);

	t_vector2_d center = {mp_width / 2, mp_height / 2};
	t_vector2_d offset = {
		data->player.pos.x - (int)data->player.pos.x / data->cell_size * data->cell_size,
		data->player.pos.y - (int)data->player.pos.y / data->cell_size * data->cell_size
	};

	dprintf(1, "h %d w %d size %d", data->tab_height, data->tab_width, data->cell_size);
	dprintf(1, "p %f %f offset %d %d\n", data->player.pos.x, data->player.pos.y, offset.x, offset.y);


	// Collect points
	dprintf(1, "----------------------\n");
	int y1 = 0;
	t_vector2_d dot_arrays[6];
	for (float y = data->player.pos.y - mp_height_2; y <= data->player.pos.y + mp_height_2; y += data->cell_size)
	{
		int i = 0;
		int x1 = 0;
		for (float x = data->player.pos.x - mp_width_2; x <= data->player.pos.x + mp_width_2; x += data->cell_size)
		{
			t_vector2_d dot = {x1, y1};
			dot.x -= offset.x;
			dot.y -= offset.y;
			dot = rot_vect_offset(dot, center, data->player.angle + PI);

			t_vector2_d map_pos = {x, y};
			map_pos.y -= data->cell_size;
			if (i > 0 && y > (data->player.pos.y - mp_height_2))
			{
				t_vector2_d tri[3] = {dot, dot_arrays[i], dot_arrays[i - 1]};
				if (is_in_map(data, map_pos) && data->tab[(map_pos.y) / data->cell_size][(map_pos.x-data->cell_size) / data->cell_size] == 1)
					draw_triangle_color(data, tri, BLUE);
			}

			if (i < 6 && y > (data->player.pos.y - mp_height_2))
			{
				t_vector2_d tri[3] = {dot, dot_arrays[i], dot_arrays[i + 1]};
				if (is_in_map(data, map_pos) && data->tab[(map_pos.y) / data->cell_size][(map_pos.x) / data->cell_size] == 1)
					draw_triangle_color(data, tri, RED);
			}


			dot_arrays[i] = dot;
			// draw_circle_color(data, dot, GREEN);
			x1 += data->cell_size;
			i++;
		}
		y1 += data->cell_size;
	}
	dprintf(1, "------\n");

	// Draw player
	draw_circle_color(data, center, WHITE);

	// Printing lines according to player direction
	// vertical lines
}
