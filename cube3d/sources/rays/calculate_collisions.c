#include "cube3d.h"

void	calculate_collisions(t_data *data)
{
	int	i;
	t_vector2_f	res;

	i = 0;
	data->player.angle = get_angle_f(data->player.pos, vector_d_to_f(data->plane));
	while (i < data->rays_nb)
	{
		res = dda(data, &data->rays[i], i);

		if (res.x != -1 && res.y != -1) // Hit
		{
			data->rays[i].hit_point = res;
			data->rays[i].angle = get_angle(vector_f_to_d(data->player.pos), vector_f_to_d(res));
			data->rays[i].length = get_vector_f_length(data->player.pos, res);
			bresenham(data, vector_f_to_d(data->player.pos), vector_f_to_d(res), YELLOW);
		}
		else
		{
			data->rays[i].length = -1;
			bresenham(data, vector_f_to_d(data->player.pos), vector_f_to_d(data->rays[i].hit_point), YELLOW);
		}
		i++;
	}
}