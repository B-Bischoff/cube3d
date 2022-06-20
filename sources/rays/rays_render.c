#include "cube3d.h"

int	get_tex_x(t_data *data, t_ray *ray, t_text *texture)
{
	// Calculating exact hit position
	double perp_angle = PI_2 - ray->angle + get_angle_f(data->player.pos, vector_d_to_f(data->player.view_dst_pos));
	double	hit_length = ray->perp_length * 0.5f * data->cell_size / sin(perp_angle);
	t_vector2_f wall_x = create_vect_f_from_origin(data->player.pos, ray->angle, hit_length);

	float cell_pos; 
	if (ray->side_hit == 1 || ray->side_hit == 3) // Horizontal hit
		cell_pos = wall_x.y - (int)(wall_x.y / data->cell_size) * data->cell_size;
	else // Vertical hit 
		cell_pos = wall_x.x - (int)(wall_x.x / data->cell_size) * data->cell_size;

	if (ray->side_hit == 3 || ray->side_hit == 2) // Converting cell_pos to ratio
		cell_pos = cell_pos / data->cell_size;
	else // Flip texture if the side hit is the top or the right side of a cell
		cell_pos = 1.0f - cell_pos / data->cell_size;

	int tex_x = cell_pos * texture->width_img; // Mapping ratio to texture dimension

	return (tex_x);
}

void	rays_render(t_data *data)
{
	const int slice_width = data->win_width / data->rays_nb;

	for (int i = 0; i < data->rays_nb; i++)
	{
		t_ray *ray = &data->rays[i];

		if (ray->perp_length == -1)
			continue;

		// Norming perp_length according to view dst otherwise texture scale and wall height are changing depending on the view_dst
		ray->perp_length *= data->view_dst * 0.00125; // 0.00125 is 1 / 800 (which is the reference view dst when cell_size = 40)

		float slice_height = (float)data->win_height / (float)ray->perp_length;
		t_vector2_d tl = {i * slice_width, (data->win_height / 2 + data->mouse_move.y) - slice_height / 2};
		t_vector2_d br = {i * slice_width + slice_width, (data->win_height / 2 + data->mouse_move.y) + slice_height / 2};

		t_text *texture;
		if (data->tab[ray->cell.y][ray->cell.x] == 2 || data->tab[ray->cell.y][ray->cell.x] == 4) // Door texture
			texture = &data->textures[22];
		else
			texture = &data->textures[ray->side_hit]; // Wall texture
		
		double tex_y = 0;
		int	tex_x = get_tex_x(data, ray, texture);
		double step = texture->height_img / slice_height;

		// dprintf(2, "%lf\n", (double)(tl.y - (data->win_height / 2 + data->mouse_move.y) + (slice_height / 2)) * step);

		float color_timestamp = ft_inv_lerp_f(10.0f, 100.0f, slice_height); // Calculating shadows

		for (int y = tl.y; y < br.y; y++)
		{
			if (y < 0) // Clamping out of screen tl.y
			{
				tex_y += -y * step;
				y = 0;
			}
			if (y >= data->win_height)
				break;

			if (y >= 0 && y < data->win_height)
			{
				int color = get_text_pix(texture, tex_x, tex_y);

				// Applying shadows to pixel
				if (color_timestamp <= 0.98f)
					color = color_lerp(BLACK, color, color_timestamp);
			
				// Filling stripe width
				for (int stripe = tl.x; stripe < br.x; stripe++)
					my_mlx_pixel_put(data, stripe, y, color);

			}
	    	tex_y += step;
		}	
	}
}
