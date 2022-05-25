#include "cube3d.h"

void	calculate_collisions(t_data *data)
{
	t_vector2_f	res;

	for (int i = 0; i < data->rays_nb; i++)
	{
		res = dda(data, &data->rays[i], i);

		if (res.x != -1 && res.y != -1) // Hit
		{
			data->rays[i].hit_point = res;
			data->rays[i].angle = get_angle(vector_f_to_d(data->player.pos), vector_f_to_d(res));
			data->rays[i].length = get_vector_f_length(data->player.pos, res);
			if (data->show_map)
				bresenham(data, vector_f_to_d(data->player.pos), vector_f_to_d(res), YELLOW);
		}
		else
		{
			data->rays[i].length = -1;
			if (data->show_map)
			{
				// Setting the vector length to view_dst (to create the "rounded" effect in fov display)
				t_vector2_f ray_full_dst = create_vect_f_from_origin(
					data->player.pos,
					get_angle_f(data->player.pos, data->rays[i].hit_point),
					data->view_dst
				);
				bresenham(data, vector_f_to_d(data->player.pos), vector_f_to_d(ray_full_dst), YELLOW);
			}
		}
	}
}