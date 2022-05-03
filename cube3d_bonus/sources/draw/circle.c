#include "cube3d.h"

void draw_circle(t_data *data, t_vector2_d center)
{
	t_vector2_d pos;
	int radius = 2;

	for (int y = center.y - radius; y < center.y + radius; y++)
	{
		for (int x = center.x - radius; x < center.x + radius; x++)
		{
			pos.y = (center.y - y) * (center.y - y);
			pos.x = (center.x - x) * (center.x - x);
			if ((float)(pos.x + pos.y) - (radius * radius) < 0.1f)
				my_mlx_pixel_put(data, x, y, PINK);
		}
	}
}

void draw_circle_color(t_data *data, t_vector2_d center, int color)
{
	t_vector2_d pos;
	int radius = 1;

	for (int y = center.y - radius; y < center.y + radius; y++)
	{
		for (int x = center.x - radius; x < center.x + radius; x++)
		{
			pos.y = (center.y - y) * (center.y - y);
			pos.x = (center.x - x) * (center.x - x);
			if ((float)(pos.x + pos.y) - (radius * radius) < 0.1f)
				my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void	draw_circle_color_radius(t_data *data, t_vector2_d center, int color, int radius)
{
	t_vector2_d	pos;

	for (int y = center.y - radius; y < center.y + radius; y++)
	{
		for (int x = center.x - radius; x < center.x + radius; x++)
		{
			pos.y = (center.y - y) * (center.y - y);
			pos.x = (center.x - x) * (center.x - x);
			float test = (float)(pos.x + pos.y) - (radius * radius);
			if (test < 0.0f)
				my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void	draw_circle_empty(t_data *data, t_vector2_d center, int radius, int thickness)
{
	t_vector2_d	pos;

	for (int y = center.y - radius; y < center.y + radius; y++)
	{
		for (int x = center.x - radius; x < center.x + radius; x++)
		{
			pos.y = (center.y - y) * (center.y - y);
			pos.x = (center.x - x) * (center.x - x);
			float test = (float)(pos.x + pos.y) - (radius * radius);
			if (test < 0.0f && test > -(thickness * thickness))
				my_mlx_pixel_put(data, x, y, WHITE);
		}
	}
}


