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
	int	error = 0;
	data->nb_sprites = 6;
	
	// Allocating sprites utilities
	data->sprites = malloc(sizeof(t_sprite) * data->nb_sprites);
	if (data->sprites == NULL)
		return (1);
	data->sprite_order = ft_calloc(data->nb_sprites, sizeof(int));
	if (data->sprite_order == NULL)
		return (1);
	data->sprite_dst = ft_calloc(data->nb_sprites, sizeof(double));
	if (data->sprite_dst == NULL)
		return (1);

	t_vector2_f	pos;
	set_vector_f(&pos, data->cell_size * 40 + data->cell_size / 2, data->cell_size * 4 + data->cell_size / 2);
	error |= create_sprite(&data->sprites[0], pos, 1, 0);
	set_vector_f(&pos, data->cell_size * 44 + data->cell_size / 2, data->cell_size * 3 + data->cell_size / 2);
	error |= create_sprite(&data->sprites[1], pos, 1, 0);
	set_vector_f(&pos, data->cell_size * 40 + data->cell_size / 2, data->cell_size * 3 + data->cell_size / 2);
	error |= create_sprite(&data->sprites[2], pos, 1, 0);
	set_vector_f(&pos, data->cell_size * 41 + data->cell_size / 2, data->cell_size * 4 + data->cell_size / 2);
	error |= create_sprite(&data->sprites[3], pos, 1, 0);
	set_vector_f(&pos, data->cell_size * 40 + data->cell_size / 2, data->cell_size * 5 + data->cell_size / 2);
	error |= create_sprite(&data->sprites[4], pos, 1, 0);
	set_vector_f(&pos, data->cell_size * 37 + data->cell_size / 2, data->cell_size * 5 + data->cell_size / 2);
	error |= create_sprite(&data->sprites[5], pos, 4, .2f);

	if (error == 1)
		return (1);

	// Setting sprites textures
	data->sprites[0].text[0] = data->textures[0];
	data->sprites[1].text[0] = data->textures[0];
	data->sprites[2].text[0] = data->textures[0];
	data->sprites[3].text[0] = data->textures[0];
	data->sprites[4].text[0] = data->textures[0];
	data->sprites[5].text[0] = data->textures[2];
	data->sprites[5].text[1] = data->textures[3];
	data->sprites[5].text[2] = data->textures[4];
	data->sprites[5].text[3] = data->textures[5];

	return (0);
}
