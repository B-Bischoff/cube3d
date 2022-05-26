#include "cube3d.h"

void	floor_and_ceiling(t_data *data)
{
	int floor_start = data->win_width * (data->win_height / 2);
	int total = data->win_width * data->win_height;
	int	size = data->bits_per_pixel / 8;

	// Using my_mlx_pixel_put is slower than directly accessing img address

	// Ceiling
	for (int i = 0; i < floor_start; i++)
	{
		if (i >= 0)
		{
			char *dst = data->addr + i * size;
			*(unsigned int *)dst = data->ceiling_color;
		}
	}
	
	// Floor
	for (int i = floor_start; i < total; i++)
	{
		char *dst = data->addr + i * size;
		*(unsigned int *)dst = data->floor_color;
	}
}