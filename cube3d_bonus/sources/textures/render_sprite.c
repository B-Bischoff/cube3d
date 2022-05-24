#include "cube3d.h"

void	sort_sprite(t_data *data)
{
	for (int i = 0; i < data->nb_sprites; i++)
		for (int j = 0; j < data->nb_sprites - 1 - i; j++)
			if (data->sprite_dst[data->sprite_order[j]] < data->sprite_dst[data->sprite_order[j + 1]])
				ft_swap_d(&data->sprite_order[j], &data->sprite_order[j + 1]);
}

void	render_sprite(t_data *data)
{
	if (data->nb_sprites == 0)
		return ;

	for (int i = 0; i < data->nb_sprites; i++)
	{
		data->sprite_order[i] = i;
		data->sprite_dst[i] = get_vector_f_length_squared(data->player.pos, data->sprites[i].pos);
	}
	sort_sprite(data);


	t_vector2_f	plane;
	plane.x = data->player.dir.x * cos(PI_2) - data->player.dir.y * sin(PI_2);
	plane.y = data->player.dir.x * sin(PI_2) + data->player.dir.y * cos(PI_2);
	plane.x *= 0.66f;
	plane.y *= 0.66f; // Because the field view is 60 degree

	const int slice_width = data->win_width / data->rays_nb;

	for (int i = 0; i < data->nb_sprites; i++)
	{
		t_sprite	*sprite = &data->sprites[data->sprite_order[i]]; // Sprite reference
		t_vector2_f	sprite_pos;
		sprite_pos.x = sprite->pos.x - data->player.pos.x;
		sprite_pos.y = sprite->pos.y - data->player.pos.y;

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
		tl.y = ft_clamp_d(tl.y, -data->win_height, data->win_height + data->mouse_pos.y);
		br.y = data->win_height / 2 + sprite_height / 2 + data->mouse_move.y;
		br.y = ft_clamp_d(br.y, 0, data->win_height * 2 + data->mouse_move.y);

		int	sprite_width = ft_abs_d((int)data->win_height / transform.y);
		tl.x = -sprite_width / 2 + sprite_screen_x;
		tl.x = ft_clamp_d(tl.x, -data->win_width, data->win_width);
		br.x = sprite_width / 2 + sprite_screen_x;
		br.x = ft_clamp_d(br.x, 0, data->win_width * 2);

		// Calculating sprites texture for animated sprites
		if (sprite->nb_text > 1)
		{
			sprite->timer += data->delta_time;
			if (sprite->timer >= sprite->anim_speed)
			{
				if (sprite->curr_text == sprite->nb_text - 1)
					sprite->curr_text = 0;
				else
					sprite->curr_text += 1;
				sprite->timer = 0;
			}
		}


		// Drawing texture on the screen
		for (int stripe = tl.x; stripe < br.x; stripe += slice_width)
		{
			if (transform.y > 0 && stripe > 0 && stripe < data->win_width - 1 && (transform.y * 1.66f) < data->rays[(stripe) / slice_width].perp_length)
			{
				// draw_rect_filled_color(data, create_vector_d(stripe, tl.y), create_vector_d(stripe + slice_width, br.y), WHITE);

				float text_factor_y = sprite->text[sprite->curr_text].height_img / (float)sprite_height;
				float text_factor_x = sprite->text[sprite->curr_text].width_img / (float)sprite_width;

				for (int y = tl.y; y < br.y; y++)
				{
					if (y < 0)
						y = 0;
					if (y > data->win_height)
						break ;
					int x_pos = (stripe - tl.x) * text_factor_x;
					int	y_pos = (y - tl.y) * text_factor_y;

					int color = get_text_pix(&sprite->text[sprite->curr_text], x_pos, y_pos);
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
