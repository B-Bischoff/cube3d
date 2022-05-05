#include "cube3d.h"

int is_in_map(t_data *data, t_vector2_d pos)
{
	if (pos.x < 0 || pos.x >= data->win_width)
		return (0);
	if (pos.y < 0 || pos.y >= data->win_height)
		return (0);
	return (1);
}

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
			side = 0; // Side hit will be equal to : 1 or 3 (meaning, the hit is on the vertical axis)
			side_hit.x = step.x;
			side_hit.y = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			length = side_dist.y;
			side = 1; // Side hit will be equal to : 0 or 2 (meaning, the hit is on the horizontal axis)
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

			// //texturing calculations
 	   		// int texNum; //1 subtracted from it so that texture 0 can be used!
			// texNum = data->tab[map.x / data->cell_size][map.y / data->cell_size] - 1;

      		//calculate value of wallX//where exactly the wall was hit
      		if (side == 0) ray->wall_x = data->player.pos.y + ray->perp_length * ray_dir.y;
      		else           ray->wall_x = data->player.pos.x + ray->perp_length * ray_dir.x;
      		ray->wall_x -= floor((ray->wall_x));


			// // Kepp wall_x in ray struct and calculate tex_x later in ray_render
			// //x coordinate on the texture
      		// int texX = (int)(wallX * (double)(data->text[0].lar_img));
      		// if(side == 0 && ray_dir.x > 0) texX = data->text[0].lar_img - texX - 1;
      		// if(side == 1 && ray_dir.y < 0) texX = data->text[0].lar_img - texX - 1;

			// int lineHeight = (int)(data->win_height / ray->perp_length);

    		// double step = 1.0 * 64 / lineHeight;


      		// 	//calculate lowest and highest pixel to fill in current stripe
      		// int drawStart = -lineHeight / 2 + data->win_height / 2;
      		// if(drawStart < 0) drawStart = 0;
    		// int drawEnd = lineHeight / 2 + data->win_height / 2;
 	    	// if(drawEnd >= data->win_height) drawEnd = data->win_height - 1;


		
    		// double texPos = (drawStart - data->win_height / 2 + lineHeight / 2) * step;
			// for (int y = 0; y < 64; y++)
    		// {
    		// 	int texY = (int)texPos & (64 - 1);
    		// 	texPos += step;
    		// 	t_color color;
			// 	char *str = &data->text[0].text_adr[texX * (data->bits_per_pixel / 8) + texY * data->line_length];
			// 	color.str[0] = str[0];
			// 	color.str[1] = str[1];
			// 	color.str[2] = str[2];
			// 	color.str[3] = str[3];

			// 	ray->text_buf[y] = color.color;
			// }

			// 	t_vector2_d tl = {0, 0};
			// t_vector2_d br = {64, 64};
			// draw_rect_filled(data,tl, br);

			return (vector_d_to_f(map));
		}
	}
	t_vector2_f error = {-1, -1};
	return (error);
}