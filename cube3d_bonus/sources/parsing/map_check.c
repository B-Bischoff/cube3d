#include "cube3d.h"

int	is_valid_cell(t_data *data, t_vector2_d pos);

int	check_map_format(t_data *data, t_list **errors)
{
	int			y;
	int			x;
	t_vector2_d	pos;
	t_list		*elem;
	t_vector2_d	*pos_alloc;

	y = 0;
	while (y < data->tab_height)
	{
		x = 0;
		while (x < data->tab_width)
		{
			set_vector_d(&pos, x, y);
			if (is_valid_cell(data, pos) == 0)
			{
				pos_alloc = malloc(sizeof(t_vector2_d));
				set_vector_d(pos_alloc, pos.x, pos.y);
				elem = ft_lstnew(pos_alloc);
				ft_lstadd_back(errors, elem);
			}
			x++;
		}
		y++;
	}
	if ((*errors) != NULL)
	{
		elem = ft_lstnew(NULL);
		ft_lstadd_back(errors, elem);
		return (1);
	}
	return (0);
}
/*
	If the cell is a zero (free space)
	Check if it's connected to a forbidden cell (-1, borders)
	If it's the case, the map is not closed, therefore return an error
*/
int	is_valid_cell(t_data *data, t_vector2_d pos)
{
	int	c;

	c = data->tab[pos.y][pos.x];
	if (c == 0)
	{
		// Borders
		if (pos.x == data->tab_width - 1 || pos.x == 0)
			return (0);
		if (pos.y == data->tab_height - 1 || pos.y == 0)
			return (0);

		// Neighbors
		if (data->tab[pos.y][pos.x - 1] == -1) // Left
			return (0);
		if (data->tab[pos.y][pos.x + 1] == -1) // Right
			return (0);
		if (data->tab[pos.y - 1][pos.x] == -1) // Top
			return (0);
		if (data->tab[pos.y + 1][pos.x] == -1) // Bottom
			return (0);
	}
	return (1);	
}

