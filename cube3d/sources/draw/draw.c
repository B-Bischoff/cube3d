#include "cube3d.h"


void draw_line(t_data *data, t_vector2_d p1, t_vector2_d p2)
{
	for (float i = 0.0f; i < 1.0f; i += .0005f)
	{
		int	x = p1.x + (p2.x - p1.x) * i;
		int y = p1.y + (p2.y - p1.y) * i;
		my_mlx_pixel_put(data, x, y, WHITE);
	}
}

void draw_line_color(t_data *data, t_vector2_d p1, t_vector2_d p2, int color)
{
	for (float i = 0.0f; i < 1.0f; i += .0005f)
	{
		int	x = p1.x + (p2.x - p1.x) * i;
		int y = p1.y + (p2.y - p1.y) * i;
		my_mlx_pixel_put(data, x, y, color);
	}
}

void draw_line_fade_from_ref(t_data *data, t_vector2_d p1, t_vector2_d p2, t_vector2_d fade_ref)
{
	for (float i = 0.0f; i < 1.0f; i += .0005f)
	{
		int	x = p1.x + (p2.x - p1.x) * i;
		int y = p1.y + (p2.y - p1.y) * i;
		t_vector2_d curr = {x, y};
		int color = color_lerp(PURPLE, DARK_GRAY, vector_d_inv_lerp(p1, fade_ref, curr));
		my_mlx_pixel_put(data, x, y, color);
	}
}

void draw_line_fade(t_data *data, t_vector2_d p1, t_vector2_d p2)
{
	for (float i = 0.0f; i < 1.0f; i += .0005f)
	{
		int color = color_lerp(PURPLE, DARK_GRAY, i);
		int	x = p1.x + (p2.x - p1.x) * i;
		int y = p1.y + (p2.y - p1.y) * i;
		my_mlx_pixel_put(data, x, y, color);
	}
}
