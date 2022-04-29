#include "cube3d.h"

void	floor_and_ceiling(t_data *data)
{
	int	floor_color = DARK_GRAY;
	int	ceiling_color = LIGHT_BLUE;

	t_vector2_d	tl;
	t_vector2_d	br;

	// Floor
	set_vector_d(&tl, 0, data->win_height / 2);
	set_vector_d(&br, data->win_width, data->win_height);
	draw_rect_filled_color(data, tl, br, floor_color);

	// Ceiling
	set_vector_d(&tl, 0, 0);
	set_vector_d(&br, data->win_width, data->win_height / 2);
	draw_rect_filled_color(data, tl, br, ceiling_color);
}
