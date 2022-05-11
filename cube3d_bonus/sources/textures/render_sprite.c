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

	set_vector_f(&plane, data->plane.x / data->player.pos.x - 1, data->plane.y / data->player.pos.y - 1);

	for (int i = 0; i < data->nb_sprites; i++)
	{
		t_vector2_f	sprite_pos;

		sprite_pos.x = data->player.pos.x - data->sprites[i].pos.x;
		sprite_pos.y = data->player.pos.y - data->sprites[i].pos.y;

		dprintf(1, "%lf\n", data->plane.x / data->player.pos.x - 1);
	}
}
