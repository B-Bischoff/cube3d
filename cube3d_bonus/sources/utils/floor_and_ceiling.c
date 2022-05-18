#include "cube3d.h"

void	floor_and_ceiling(t_data *data)
{
	t_vector2_d	tl;
	t_vector2_d	br;

	// Floor
	set_vector_d(&tl, 0, data->win_height / 2 + data->mouse_move.y);
	set_vector_d(&br, data->win_width, data->win_height);
	draw_rect_filled_color(data, tl, br, data->floor_color);

	// Ceiling
	set_vector_d(&tl, 0, 0);
	set_vector_d(&br, data->win_width, data->win_height / 2 + data->mouse_move.y);
	draw_rect_filled_color(data, tl, br, data->ceiling_color);
}
