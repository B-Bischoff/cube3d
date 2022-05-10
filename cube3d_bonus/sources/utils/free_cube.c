#include "cube3d.h"

void	free_all(t_data *data)
{
	// Map
	for (int y = 0; y < data->tab_height; y++)
		free(data->tab[y]);
	free(data->tab);

	// Textures
	for (int i = 0; i < 6; i++)
		free(data->texture_name[i]);

	// Rays
	free(data->rays);

	// Mlx
	free(data->mlx);
	free(data->mlx_win);
	free(data->img);
	free(data->addr);
}