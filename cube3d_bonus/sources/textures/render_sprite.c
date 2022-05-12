#include "cube3d.h"

void	render_sprite(t_data *data)
{
	for (int i = 0; i < data->nb_sprites; i++)
	{
		data->sprite_order[i] = i;
		data->sprite_dst[i] = get_vector_f_length_squared(data->player.pos, data->sprites[i].pos);
	}
	// WILL NEED TO SORT SPRITES IN data->sprite_order

	t_vector2_f	plane;
	plane.x = data->player.dir.x * cos(PI_2) - data->player.dir.y * sin(PI_2);
	plane.y = data->player.dir.x * sin(PI_2) + data->player.dir.y * cos(PI_2);
	plane.x *= 0.66f;
	plane.y *= 0.66f; // Because the field view is 60 degree

	const int slice_width = data->win_width / data->rays_nb;

	for (int i = 0; i < data->nb_sprites; i++)
	{
		t_vector2_f	sprite_pos;
		sprite_pos.x = data->sprites[i].pos.x - data->player.pos.x;
		sprite_pos.y = data->sprites[i].pos.y - data->player.pos.y;

		sprite_pos.x /= data->cell_size;
		sprite_pos.y /= data->cell_size;

		double	inv_det = 1.0f / (plane.x * data->player.dir.y - data->player.dir.x * plane.y);
		
		t_vector2_f	transform;
		transform.x = inv_det * (data->player.dir.y * sprite_pos.x - data->player.dir.x * sprite_pos.y);
		transform.y = inv_det * (-plane.y * sprite_pos.x + plane.x * sprite_pos.y);

		int	sprite_screen_x;
		sprite_screen_x = (int)((data->win_width / 2) * (1 + transform.x / transform.y));

		int	sprite_height = ft_abs_d((int)(data->win_height / transform.y));

		// Calculating sprite dimensions
		t_vector2_d	tl, br;
		tl.y = data->win_height / 2 - sprite_height / 2 + data->mouse_move.y;
		tl.y = ft_clamp_d(tl.y, 0, data->win_height + data->mouse_pos.y);
		br.y = data->win_height / 2 + sprite_height / 2 + data->mouse_move.y;
		br.y = ft_clamp_d(br.y, 0, data->win_height + data->mouse_move.y);

		int	sprite_width = ft_abs_d((int)data->win_height / transform.y);
		tl.x = -sprite_width / 2 + sprite_screen_x;
		tl.x = ft_clamp_d(tl.x, 0, data->win_width);
		br.x = sprite_width / 2 + sprite_screen_x;
		br.x = ft_clamp_d(br.x, 0, data->win_width);

		// draw_rect_filled_color(data, tl, br, BLACK);
		for (int stripe = tl.x; stripe < br.x; stripe += slice_width)
		{
			if (transform.y > 0 && (transform.y * 1.33f) < data->rays[(stripe) / slice_width].perp_length)
			{
				// draw_rect_filled_color(data, create_vector_d(stripe, tl.y), create_vector_d(stripe + slice_width, br.y), WHITE);
				
				float text_factor_y = (float)data->textures[0].height_img / (float)sprite_height;
				float text_factor_x = (float)data->textures[0].width_img / (float)sprite_width;
				for (int y = tl.y; y < br.y; y++)
				{
					int x_pos = (stripe - tl.x) * text_factor_x;
					int	y_pos = (y - tl.y) * text_factor_y;
					// dprintf(1, "factors x %f y %f ------ x %d | y %d\n", text_factor_x, text_factor_y, x_pos, y_pos);

					int color = get_text_pix(&data->textures[0], x_pos, y_pos);
					if (ft_get_t(color) != 255)
					{
						for (int pixel = 0; pixel < slice_width; pixel++)
							my_mlx_pixel_put(data, stripe + pixel, y, color);
					}
				}
			}
		}
	}
}
