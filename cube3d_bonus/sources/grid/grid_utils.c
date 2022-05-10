#include "cube3d.h"

int is_in_map(t_data *data, t_vector2_d pos)
{
	if (pos.x < 0 || pos.x > data->width_size - 1)
		return (0);
	if (pos.y < 0 || pos.y > data->height_size - 1)
		return (0);
	return (1);
}