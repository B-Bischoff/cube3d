#include "cube3d.h"

void	draw_floor_ceiling(t_data *data, t_vector2_d tl, t_vector2_d br, int up_or_down)
{
	for (int i = 0; i < data->win_height / 2; i++)
	{
		for (int x = tl.x; x < br.x; x++)
			my_mlx_pixel_put(data, x, (data->win_height / 2) + (i * up_or_down), data->floor_celling[i * data->win_width + x]);
	}
}

void	floor_and_ceiling(t_data *data)
{
	// int	floor_color = DARK_GRAY;
	// int	ceiling_color = LIGHT_BLUE;

	t_vector2_d	tl;
	t_vector2_d	br;

	// Floor
	set_vector_d(&tl, 0, data->win_height / 2);
	set_vector_d(&br, data->win_width, data->win_height);
	draw_floor_ceiling(data, tl, br, 1);

	// Ceiling
	set_vector_d(&tl, 0, 0);
	set_vector_d(&br, data->win_width, data->win_height / 2);
	draw_floor_ceiling(data, tl, br, -1);
	// draw_rect_filled_color(data, tl, br, ceiling_color);
}
