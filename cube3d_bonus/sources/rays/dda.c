#include "cube3d.h"


/*
t_vector2_f old_dda(t_data *data, t_ray *ray, int ray_index)
{
	t_vector2_f error = {-1, -1};
	t_vector2_f end = ray->hit_point;

	t_vector2_f ray_dir = {
		end.x - data->player.pos.x,
		end.y - data->player.pos.y
	};
	(void)ray_index;

	// Norming vector ray_dir
	float norm  = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y;
	// if (norm == 0)
		// return (error);

	float x = ray_dir.x / norm;
	float y = ray_dir.y / norm;

	// Try to get rid of sqrt functions
	double step_size_x = sqrt(1.0f + (y / x) * (y / x));
	double step_size_y = sqrt(1.0f + (x / y) * (x / y));

	// printf("%f %f\n", step_size_y, step_size_x);

	t_vector2_f map_check = {data->player.pos.x, data->player.pos.y};
	t_vector2_d step;
	double ray_length_x;
	double ray_length_y;

	if (ray_dir.x < 0)
	{
		step.x = -1;
		ray_length_x = 0;
	}
	else
	{
		step.x = 1;
		ray_length_x = step_size_x;
	}

	if (ray_dir.y < 0)
	{
		step.y = -1;
		ray_length_y = 0;
	}
	else
	{
		step.y = 1;
		ray_length_y = step_size_y;
	}

	double dst = 0.0f;

	t_vector2_d last_step;
	double length = get_vector_f_length(data->player.pos, ray->hit_point);
	while (dst <= length)
	{
		if (ray_length_x < ray_length_y)
		{
			map_check.x += step.x;
			dst = ray_length_x;
			ray_length_x += step_size_x;
			last_step.x = step.x;
			last_step.y = 0;
		}
		else
		{
			map_check.y += step.y;
			dst = ray_length_y;
			ray_length_y += step_size_y;
			last_step.y = step.y;
			last_step.x = 0;
		}
		if (map_check.x >= 0 && map_check.x < data->win_width \
			&& map_check.y >= 0 && map_check.y < data->win_height)
			{
				// printf("HERE %d %d\n", map_check.x, map_check.y);
				if (data->tab[(int)map_check.y / data->cell_size][(int)map_check.x / data->cell_size] == 1)
				{
					t_vector2_f center = {map_check.x, map_check.y};
					ray->cell.x = map_check.x / data->cell_size;
					ray->cell.y = map_check.y / data->cell_size;
					// draw_circle_color(data, vector_f_to_d(center), GREEN);

					if (last_step.x == 1)
						ray->side_hit = 3;
					else if (last_step.x == -1)
						ray->side_hit = 1;
					else if (last_step.y == 1)
						ray->side_hit = 0;
					else
						ray->side_hit = 2;

					dprintf(1, "-------\n");
					dprintf(1, "end : %f %f\n", end.x, end.y);
					dprintf(1, "norm %f\n", norm);
					dprintf(1, "player : %f %f\n", data->player.pos.x, data->player.pos.y);
					dprintf(1, "map : %f %f -> %d %d\n", map_check.x, map_check.y, ray->cell.x, ray->cell.y);
					dprintf(1, "dst : %lf\n", dst);

					return (center);
				}
			}
	}
	return (error);
}
*/
t_vector2_f dda(t_data *data, t_ray *ray, int ray_index)
{
	t_vector2_f	ray_dir = ray->hit_point;
	t_vector2_d	map = vector_f_to_d(data->player.pos);

	t_vector2_f side_dist;
	t_vector2_f	delta_dist;

	(void)ray_index;
	ray_dir.x = ray_dir.x - data->player.pos.x;
	ray_dir.y = ray_dir.y - data->player.pos.y;

	if (ray_dir.x == 0.0f)
		delta_dist.x = 1e30; // Large value
	else
		delta_dist.x = ft_abs_f(1.0f / ray_dir.x);
	if (ray_dir.y == 0.0f)
		delta_dist.y = 1e30; // Large value
	else
		delta_dist.y = ft_abs_f(1.0f / ray_dir.y);


	t_vector2_d step;
	int			side;
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (data->player.pos.x - map.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map.x + 1.0f - data->player.pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (data->player.pos.y - map.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map.y + 1.0f - data->player.pos.y) * delta_dist.y;
	}


	double length = 0.0f;
	t_vector2_d side_hit;

	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map.x += step.x;
			length = side_dist.x;
			side = 0;
			side_hit.x = step.x;
			side_hit.y = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			length = side_dist.y;
			side = 1;
			side_hit.y = step.y;
			side_hit.x = 0;
		}
		float len = get_vector_d_length_squared(vector_f_to_d(data->player.pos), map);
		if (len >= data->view_dst * data->view_dst)
			break ;
		if (!is_in_map(data, map))
			continue; ;
		// draw_circle_color(data, map, RED);
		if (data->tab[map.y / data->cell_size][map.x / data->cell_size] > 0)
		{
			if (side == 0)
				ray->perp_length = side_dist.x - delta_dist.x;
			else
				ray->perp_length = side_dist.y - delta_dist.y; 
			ray->perp_length *= data->cell_size;

			if (side_hit.x == 1)
				ray->side_hit = 3;
			else if (side_hit.x == -1)
				ray->side_hit = 1;
			else if (side_hit.y == 1)
				ray->side_hit = 0;
			else
				ray->side_hit = 2;
			return (vector_d_to_f(map));
		}
	}
	t_vector2_f error = {-1, -1};
	return (error);
}