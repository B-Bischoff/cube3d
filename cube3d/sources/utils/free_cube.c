#include "cube3d.h"

int	free_all(t_data *data)
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
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->mlx);

	exit (0);
}
