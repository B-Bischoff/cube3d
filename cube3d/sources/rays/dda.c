#include "cube3d.h"

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
			length += side_dist.x;
			side = 0; // Side hit will be equal to : 1 or 3 (meaning, the hit is on the vertical axis)
			side_hit.x = step.x;
			side_hit.y = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			length += side_dist.y;
			side = 1; // Side hit will be equal to : 0 or 2 (meaning, the hit is on the horizontal axis)
			side_hit.y = step.y;
			side_hit.x = 0;
		}
		float len = get_vector_d_length_squared(vector_f_to_d(data->player.pos), map);
		if (len >= data->view_dst * data->view_dst)
			break ;
		if (!is_in_map(data, map))
			continue;
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

			double angle = get_angle_f(data->player.pos, ray->hit_point);

			double _angle = PI_2 - angle + data->player.angle;

			t_vector2_f _wall_x = create_vect_f_from_origin(data->player.pos, -angle, ray->perp_length / 2 * data->cell_size * sin(degree_to_radian(90)) / sin(_angle));
		
			if (side == 0)
			{
				_wall_x.y = _wall_x.y - (double)((int)floor(_wall_x.y / (double)data->cell_size) * data->cell_size);
				_wall_x.y = 1 - _wall_x.y / (double)data->cell_size;

				ray->tex_x = (int)(_wall_x.y * (double)data->text[0].height_img);

				if (ray_index == 1)
					dprintf(1, "wall_x %f  tex_x %d\n", _wall_x.y, ray->tex_x);
			}
			else
			{
				_wall_x.x = _wall_x.x - (double)((int)floor(_wall_x.x / (double)data->cell_size) * data->cell_size);
				_wall_x.x = 1 - _wall_x.x / (double)data->cell_size;
	
				ray->tex_x = (int)(_wall_x.x * (double)data->text[0].height_img);
				
				if (ray_index == 1)
					dprintf(1, "wall_x %f  tex_x %d\n", _wall_x.x, ray->tex_x);
			}

			// t_vector2_f	plane;
			// plane.x = data->player.dir.x * cos(PI_2) - data->player.dir.y * sin(PI_2);
			// plane.y = data->player.dir.x * sin(PI_2) + data->player.dir.y * cos(PI_2);
			// plane.x *= 0.66f;
			// plane.y *= 0.66f; // Because the field view is 60 degree
			
			// double camera_x = (double)(2 * (double)ray_index * 2) / (double)data->win_width - 1;
			// double ray_dr_y = data->player.dir.y + plane.y * camera_x;
			// double ray_dr_x = data->player.dir.x + plane.x * camera_x;

			if (side == 0 && ray_dir.x > 0) ray->tex_x = data->text[0].height_img - ray->tex_x - 1;
      		
			if (side == 1 && ray_dir.y < 0) ray->tex_x = data->text[0].height_img - ray->tex_x - 1;

			return (vector_d_to_f(map));
		}
	}
	t_vector2_f error = {-1, -1};

	return (error);
}
