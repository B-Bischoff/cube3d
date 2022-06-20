#include "cube3d.h"

void	set_grid_cell(t_data *data, int x, int y)
{
	t_vector2_d tab_pos;

	// Convert pixel coordinate to cell coordinate
	tab_pos.x = x / data->cell_size;
	tab_pos.y = y / data->cell_size;

	// Checking out of tab coordinates
	if (tab_pos.x < 0 || tab_pos.x >= data->tab_width)
		return ;
	if (tab_pos.y < 0 || tab_pos.y >= data->tab_height)
		return ;

	if (data->mouse_button == LMB)
		data->tab[tab_pos.y][tab_pos.x] = 1;
 	else if (data->mouse_button == RMB)
		data->tab[tab_pos.y][tab_pos.x] = 0;
}