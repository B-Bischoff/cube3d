#include "cube3d.h"

int is_in_map(t_data *data, t_vector2_d pos)
{
	if (pos.x < 0 || pos.x > data->win_width - 1)
		return (0);
	if (pos.y < 0 || pos.y > data->win_height - 1)
		return (0);
	return (1);
}