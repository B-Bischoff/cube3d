#include "cube3d.h"

int is_in_map(t_data *data, t_vector2_d pos)
{
	if (pos.x < 0 || pos.x > data->width_size - 1)
		return (0);
	if (pos.y < 0 || pos.y > data->height_size - 1)
		return (0);
	return (1);
}

int		is_colliding_cell(t_data *data, float x, float y)
{
	t_vector2_d	cell;

	set_vector_d(&cell, x / data->cell_size, y / data->cell_size);
	if (data->tab[cell.y][cell.x] == 1)
		return (1);
	if (data->tab[cell.y][cell.x] == 2)
		return (1);
	return (0);
}
