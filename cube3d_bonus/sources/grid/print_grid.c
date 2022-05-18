#include "cube3d.h"

/*
	Print grid in full screen
*/
void	print_grid(t_data *data)
{
	// Walls
	for (int y = 0; y < data->tab_height; y++)
	{
		for (int x = 0; x < data->tab_width; x++)
		{
			t_vector2_d	top_left = {x * data->cell_size, y * data->cell_size};
			t_vector2_d	bot_right = {top_left.x + data->cell_size, top_left.y + data->cell_size};
			if (data->tab[y][x] == 1)
				draw_rect_filled_color(data, top_left, bot_right, PINK);
			else if (data->tab[y][x] == 2 || data->tab[y][x] == 4)
				draw_rect_filled_color(data, top_left, bot_right, GREEN);
		}
	}

	// Sprites
	for (int i = 0; i < data->nb_sprites; i++)
		draw_circle_color_radius(data, vector_f_to_d(data->sprites[i].pos), RED, 5);
}