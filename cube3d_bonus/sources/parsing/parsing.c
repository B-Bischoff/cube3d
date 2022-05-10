#include "cube3d.h"

int	get_description(t_data *data, int fd);
int	get_map(t_data *data, int fd, t_list **map);
int	convert_map_to_int(t_data *data, t_list **map);
int	check_map_format(t_data *data, t_list **errors);
void	print_map(t_data *data, t_list *errors);
int	init_parsing(t_data *data);

/*
	textures name are stored in data->texture_name
	
	1st str : NO informations
	2nd str : SO informations
	3rd str : WE informations
	4th str : EA informations
	5th str : F informations
	6th str : C informations
	
	Each line of the map is stored in a linked list 
	then converted to data->tab in integer format
*/
int	parsing(t_data *data, int argc, char *argv[])
{
	t_list	*map = NULL;
	t_list	*errors = NULL;
	int	fd;

	data->cell_size = 40;
	init_parsing(data);
	if (argc != 2)
		return (print_error("Wrong number of arguments\n"));
	fd = open(argv[1], O_RDONLY);	
	if (fd == -1)
		return (print_error("Map opening error\n"));
	if (get_description(data, fd) == 1)
		return (print_error("Description error\n"));
	if (get_map(data, fd, &map) == 1)
		return (print_error("Get map error\n"));
	close(fd);
	if (convert_map_to_int(data, &map) == 1)
		return (print_error("Map conversion error\n"));


	data->width_size = data->cell_size * data->tab_width;
	data->height_size = data->cell_size * data->tab_height;

	if (check_player_pos(data) == 1)
		return (print_error("Player pos error\n"));

	if (check_map_format(data, &errors) == 1)
	{
		print_map(data, errors);
		ft_lstclear(&errors, free);
		return (print_error("Map format error\n"));
	}
	print_map(data, errors);

	// Print logs :

	dprintf(1, "------ TEXTURES -------\n");
	for (int i = 0; i < 6; i++)
		dprintf(1, "%s\n", data->texture_name[i]);


	dprintf(1, "----- MAP SIZE ------\n");
	dprintf(1, "number of line : %d\n", data->tab_height);
	dprintf(1, "max line length : %d\n", data->tab_width);

	dprintf(1, "----- PLAYER ------\n");
	dprintf(1, "X : %f Y :%f\n", data->player.pos.x / data->cell_size, data->player.pos.y / data->cell_size);
	dprintf(1, "Orientation : %f %f\n", data->player.dir.x, data->player.dir.y);

	ft_lstclear(&map, free);
	ft_lstclear(&errors, free);

	return (0);
}

int	init_parsing(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
		data->texture_name[i++] = NULL;
	i = 0;
	while (i < 200)
		data->keyboard[i++] = 0;
	data->tab_height = 0;
	data->tab_width = 0;
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
