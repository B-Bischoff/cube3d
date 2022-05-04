#include "cube3d.h"

void	print_grid(t_data *data)
{
	for (int y = 0; y < data->tab_height; y++)
	{
		for (int x = 0; x < data->tab_width; x++)
		{
			t_vector2_d	top_left = {x * data->cell_size, y * data->cell_size};
			t_vector2_d	bot_right = {top_left.x + data->cell_size, top_left.y + data->cell_size};
			if (data->tab[y][x] == 1)
				draw_rect_filled_color(data, top_left, bot_right, PINK);
			else if (data->tab[y][x] == 2)
				draw_rect_filled_color(data, top_left, bot_right, GREEN);
		}
	}
}