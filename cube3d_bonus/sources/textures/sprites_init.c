#include "cube3d.h"

int	sprites_init(t_data *data)
{
	data->nb_sprites = 1;
	
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

	// Setting sprites position
	set_vector_f(&data->sprites[0].pos, data->cell_size * 3 + data->cell_size / 2, data->cell_size * 3 + data->cell_size / 2);
	return (0);
}
