#include "cube3d.h"

int	is_valid_char(char c)
{
	if (c == ' ')
		return (1);
	if (c == '1')
		return (1);
	if (c == '0')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int get_map(t_data *data, int fd, t_list **map)
{
	char	*buf;
	t_list	*new_elem;
	int		length;

	buf = get_next_line(fd);
	while (buf)
	{
		length = ft_strlen(buf);
		buf[length - 1] = '\0'; // Removing \n at end of line
		length--;
		if (length > data->tab_width) // Updating max line length
			data->tab_width = length;
		new_elem = ft_lstnew(buf);
		if (new_elem == NULL)
			return (1);
		ft_lstadd_back(map, new_elem);
		data->tab_height++;
		buf = get_next_line(fd);
	}
	new_elem = ft_lstnew(NULL);
	if (new_elem == NULL)
		return (1);
	ft_lstadd_back(map, new_elem);
	return (0);
}

int	convert_map_to_int(t_data *data, t_list **map)
{
	int	i;
	int	j;
	int	line_length;
	t_list	*elem;

	dprintf(1, "starting map conversion\n");
	data->tab = malloc(sizeof(int *) * data->tab_height);
	if (data->tab == NULL)
		return (1);
	elem = *map;
	i = 0;
	while (i < data->tab_height)
	{
		data->tab[i] = ft_calloc(data->tab_width, sizeof(int));
		if (data->tab[i] == NULL)
			return (1);
		// Converting datas from linked list (char) to tab (int)
		j = 0;
		char	*str = elem->content;
		line_length = ft_strlen(str);
		while (j < data->tab_width)
		{
			if (j < line_length)
			{
				if (!is_valid_char(str[j]))
				{
					dprintf(2, "Invalid char : '%c' on line %d char number %d\n", str[j], i + 1, j);
					return (1);
				}
				else if (str[j] == ' ')
					data->tab[i][j] = -1;
				else
					data->tab[i][j] = str[j] - 48;
			}
			else
				data->tab[i][j] = -1;
			j++;
		}	
		elem = elem->next;
		i++;
	}	
	return (0);
}
