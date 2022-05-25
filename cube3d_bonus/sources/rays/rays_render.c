#include "cube3d.h"

int	get_tex_x(t_data *data, t_ray *ray, t_text *texture)
{
	double perp_angle = PI_2 - ray->angle + data->player.angle;

	double	hit_length = ray->perp_length / 2 * data->cell_size * sin(degree_to_radian(90)) / sin(perp_angle);

	t_vector2_f _wall_x = create_vect_f_from_origin(data->player.pos, ray->angle, hit_length);

	int	tex_x;

	if (ray->side_hit == 1 || ray->side_hit == 3) // Horizontal hit
	{
		_wall_x.y = _wall_x.y - (double)((int)floor(_wall_x.y / (double)data->cell_size) * data->cell_size);
		_wall_x.y = 1 - _wall_x.y / (double)data->cell_size;
		tex_x = (int)(_wall_x.y * (double)texture->width_img);
	}
	else
	{
		_wall_x.x = _wall_x.x - (double)((int)floor(_wall_x.x / (double)data->cell_size) * data->cell_size);
		_wall_x.x = 1 - _wall_x.x / (double)data->cell_size;
		tex_x = (int)(_wall_x.x * (double)texture->width_img);
	}

	if ((ray->side_hit == 1 || ray->side_hit == 3) && ray->ray_dir.x > 0)
		tex_x = texture->width_img - tex_x - 1;

	if ((ray->side_hit == 0 || ray->side_hit == 2) && ray->ray_dir.y < 0)
		tex_x = texture->width_img - tex_x - 1;

	return (tex_x);
}

void	rays_render(t_data *data)
{
	int slice_width;

	slice_width = data->win_width / data->rays_nb;


	for (int i = 0; i < data->rays_nb; i++)
	{
		t_ray *ray = &data->rays[i];

		if (ray->length == -1)
			continue;

		t_text *texture;
		if (data->tab[ray->cell.y][ray->cell.x] == 2 || data->tab[ray->cell.y][ray->cell.x] == 4)
			texture = &data->textures[22];
		else
			texture = &data->textures[ray->side_hit];


		float line_height = (float)data->win_height / (float)(ray->perp_length);

		int	tex_x = get_tex_x(data, ray, texture);

		float j = ft_inv_lerp_f(10.0f, 100.0f, line_height);

		int color;
		// if (data->tab[ray->cell.y][ray->cell.x] == 1)
		// {
		// 	if (ray->side_hit == 0)
		// 		color = color_lerp(DARK_GRAY, RED, j);
		// 	else if (ray->side_hit == 1)
		// 		color = color_lerp(DARK_GRAY, BLUE, j);
		// 	else if (ray->side_hit == 2)
		// 		color = color_lerp(DARK_GRAY, YELLOW, j);
		// 	else
		// 		color = color_lerp(DARK_GRAY, GREEN, j);
		// }
		// if (data->tab[ray->cell.y][ray->cell.x] == 2 || data->tab[ray->cell.y][ray->cell.x] == 4)
		// 	color = PURPLE;
		// else
		// 	color = BLACK;
	
		double step = 1.0 * texture->height_img / line_height;

		int draw_start_y = (data->win_height / 2) - line_height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;

		int draw_end_y = (data->win_height / 2) + line_height / 2;
		if (draw_end_y >= data->win_height) 
			draw_end_y = data->win_height - 1;
		
		t_vector2_d tl = {i * slice_width, (data->win_height / 2 + data->mouse_move.y) - line_height / 2};
		t_vector2_d br = {i * slice_width + slice_width, (data->win_height / 2 + data->mouse_move.y) + line_height / 2};
		
		double tex_pos = (double)(tl.y - (data->win_height / 2 + data->mouse_move.y) + (line_height / 2)) * step;

		for (int y = tl.y; y < br.y; y++)
		{
			if (y < 0)
			{
				tex_pos += -y * step;
				y = 0;
			}
			if (y >= data->win_height)
				break;

			if (y >= 0 && y < data->win_height)
			{
				int tex_y = (int)tex_pos;

				color = get_text_pix(texture, tex_x, tex_y);
					if (j <= 0.98f)
						color = color_lerp(BLACK, color, j);

			
				my_mlx_pixel_put(data, i * 2, y, color);
				my_mlx_pixel_put(data, i * 2 + 1, y, color);

			}
	    	tex_pos += step;
		}	

	}
}
