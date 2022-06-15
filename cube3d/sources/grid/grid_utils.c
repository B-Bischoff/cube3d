#include "cube3d.h"

int is_in_map(t_data *data, t_vector2_d pos)
{
	if (pos.x < 0 || pos.x > data->width_size - 1)
		return (0);
	if (pos.y < 0 || pos.y > data->height_size - 1)
		return (0);
	return (1);
}

/*
	x & y are the coordinate in world space to check
	plain_cell is used to differenciate full cell (walls) and half cell (doors)
*/
int		is_colliding_cell(t_data *data, float x, float y, int plain_cell)
{
	t_vector2_d	cell;

	if (!is_in_map(data, create_vector_d(x, y)))
		return (0);
	set_vector_d(&cell, x / data->cell_size, y / data->cell_size);
	if (data->tab[cell.y][cell.x] == 1) // Wall
		return (1);
	if (data->tab[cell.y][cell.x] == 2) // Horizontal wall
	{
		if (plain_cell || (int)y % data->cell_size == data->cell_size / 2)
			return (1);
	}
	if (data->tab[cell.y][cell.x] == 4) // Vertical wall
	{
		if (plain_cell || (int)x % data->cell_size == data->cell_size / 2)
			return (1);
	}
	return (0);
}
