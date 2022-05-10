#include "cube3d.h"

int	ft_init_vision(t_data *data)
{
	data->view_dst = 800;
	data->fov = 60;
	data->rays_nb = data->win_width / 2; // Might be divided by 2 for fps improvement
	// data->rays_nb = 4; // Might be divided by 2 for fps improvement
	data->rays = malloc(sizeof(t_ray) * data->rays_nb);
	if (data->rays == NULL)
		return (1);
	return (0);
}
