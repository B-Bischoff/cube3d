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
	const int mp_height = 200;
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
	for (float y = data->player.pos.y - mp_height_2; y < data->player.pos.y + mp_height_2; y += data->cell_size)
	{
		int i = 0;
		int x1 = 0;
		for (float x = data->player.pos.x - mp_width_2; x < data->player.pos.x + mp_width_2; x += data->cell_size)
		{
			// int cell_size_2 = data->cell_size /  2;
			t_vector2_d dot = {x1 + offset.x, y1 + offset.y};
			dot = rot_vect_offset(dot, center, data->player.angle);

			draw_circle_color(data, dot, RED);

			if (i > 0)
			{
				bresenham(data, dot, dot_arrays[i - 1], PURPLE);
			}
			if (y > (data->player.pos.y - mp_height_2))
			{
				bresenham(data, dot, dot_arrays[i], BLUE);
			}
			dot_arrays[i] = dot;
			draw_circle_color(data, dot, GREEN);
			x1 += data->cell_size;
			i++;
		}
		dprintf(1, "------\n");
		y1 += data->cell_size;
	}

	// Draw player
	draw_circle_color(data, center, PINK);

	// Printing lines according to player direction
	// vertical lines
}
