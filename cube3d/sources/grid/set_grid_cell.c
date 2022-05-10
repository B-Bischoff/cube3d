#include "cube3d.h"

void	set_grid_cell(t_data *data, int x, int y)
{
	t_vector2_d tab_pos;

	if (x < 0 || x >= data->width_size || y < 0 || y >= data->height_size)
		return ;

	// Convert pixel coordinate to cell coordinate
	tab_pos.x = x / data->cell_size;
	tab_pos.y = y / data->cell_size;

	//data->tab[tab_pos.y][tab_pos.x] = !data->tab[tab_pos.y][tab_pos.x];
	if (data->mouse_button == LMB)
		data->tab[tab_pos.y][tab_pos.x] = 1;
 	else if (data->mouse_button == RMB)
		data->tab[tab_pos.y][tab_pos.x] = 0;
}