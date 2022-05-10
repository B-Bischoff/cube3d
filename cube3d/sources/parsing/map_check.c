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

int	check_player_pos(t_data *data)
{
	int	y;
	int	x;
	char	player;
	t_vector2_d	pos;

	player = '0';
	y = 0;
	while (y < data->tab_height)
	{
		x = 0;
		while (x < data->tab_width)
		{
			if (data->tab[y][x] + 48 == 'N' || data->tab[y][x] + 48 == 'S' || data->tab[y][x] + 48 == 'E' ||data->tab[y][x] + 48 == 'W')
			{
				if (player != '0')
				{
					dprintf(2, "Multiple player definition\n");
					return (1);
				}
				player = data->tab[y][x] + 48;
				set_vector_d(&pos, x, y);
			}
			x++;
		}
		y++;
	}
	if (player == '0')
	{
		dprintf(2, "Player position not defined\n");
		return (1);
	}

	// Assigning player init position and rotation

	dprintf(1, "pos x %d y %d\n", pos.x, pos.y);

	data->player.pos.x = pos.x * data->cell_size + data->cell_size / 2;
	data->player.pos.y = pos.y * data->cell_size + data->cell_size / 2;

	dprintf(1, "player x %f, player y %f\n", data->player.pos.x, data->player.pos.y);

	if (player == 'N')
		set_vector_f(&data->player.dir, 0, -1);
	else if (player == 'S')
		set_vector_f(&data->player.dir, 0, 1);
	else if (player == 'E')
		set_vector_f(&data->player.dir, 1, 0);
	else
		set_vector_f(&data->player.dir, -1, 0);

	// Set player to 0 in tab
	data->tab[pos.y][pos.x] = 0;

	return (0);
}
