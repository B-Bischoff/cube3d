#include "cube3d.h"

int	create_sprite(t_sprite *sprite, t_vector2_f pos, int nb_text, double anim_speed)
{
	sprite->nb_text = nb_text;
	set_vector_f(&sprite->pos, pos.x, pos.y);
	sprite->text = malloc(sizeof(t_text) * nb_text);
	if (sprite->text == NULL)
		return (1);
	sprite->anim_speed = anim_speed;
	sprite->curr_text = 0;
	sprite->timer = 0;
	return (0);
}

int	sprites_init(t_data *data)
{
	int	sprite_number = 0;
	int	error = 0;

	// Allocating sprites utilities
	data->sprite_order = ft_calloc(data->nb_sprites, sizeof(int));
	if (data->sprite_order == NULL)
		return (1);
	data->sprite_dst = ft_calloc(data->nb_sprites, sizeof(double));
	if (data->sprite_dst == NULL)
		return (1);

	for (int y = 0; y < data->tab_height; y++)
	{
		for (int x = 0; x < data->tab_width; x++)
		{
			int	c = data->tab[y][x];
			
			if (c >= 6 && c <= 8)
			{
				t_vector2_f	pos = {
					x * data->cell_size + data->cell_size / 2,
					y * data->cell_size + data->cell_size / 2
				};
				if (c == 8) // Soldier
				{
					error |= create_sprite(&data->sprites[sprite_number], pos, 4, .2f);
					if (error)
						return (1);
					data->sprites[sprite_number].text[0] = data->textures[2];
					data->sprites[sprite_number].text[1] = data->textures[3];
					data->sprites[sprite_number].text[2] = data->textures[4];
					data->sprites[sprite_number].text[3] = data->textures[5];
				}
				else
				{
					error |= create_sprite(&data->sprites[sprite_number], pos, 1, 0.0f);
					if (error)
						return (1);
					data->sprites[sprite_number].text[0] = data->textures[c - 6];
				}
				sprite_number++;
			}
		}
	}

	return (0);
}
