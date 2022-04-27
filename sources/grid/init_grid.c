#include "cube3d.h"

int	init_grid(t_data *data)
{
	int	i;

	data->cell_size = 20;
	data->tab_height = 50;
	data->tab_width = 70;
	data->tab = malloc(sizeof(int *) * data->tab_height);
	if (data->tab == NULL)
		return (1);
	i = 0;
	while (i < data->tab_height)
	{
		data->tab[i] = ft_calloc(data->tab_width, sizeof(int));
		if (data->tab[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}
