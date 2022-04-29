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
