#include "cube3d.h"

int	get_tex_x(t_data *data, t_ray *ray, t_text *texture)
{
	double perp_angle = PI_2 - ray->angle + get_angle_f(data->player.pos, vector_d_to_f(data->player.view_dst_pos));

	double	hit_length = ray->perp_length / 2 * data->cell_size * sin(PI_2) / sin(perp_angle);

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

		if (ray->perp_length == -1)
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
		double step = 1.0 * texture->height_img / line_height;
		
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

			
				for (int stripe = tl.x; stripe < br.x; stripe++)	
					my_mlx_pixel_put(data, stripe, y, color);

			}
	    	tex_pos += step;
		}	

	}
}
