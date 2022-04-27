#include "cube3d.h"

void draw_rect_filled(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right)
{
	for (int y = top_left.y; y < bottom_right.y; y++)
	{
		for (int x = top_left.x; x < bottom_right.x; x++)
		{
			my_mlx_pixel_put(data, x, y, LIGHT_BLUE);
		}
	}
}

void draw_rect_filled_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color)
{
	for (int y = top_left.y; y < bottom_right.y; y++)
	{
		for (int x = top_left.x; x < bottom_right.x; x++)
		{
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}
