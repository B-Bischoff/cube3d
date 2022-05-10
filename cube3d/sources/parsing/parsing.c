#include "cube3d.h"

int	get_description(t_data *data, int fd);
int	get_map(t_data *data, int fd);
int	convert_map_to_int(t_data *data);
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
	t_list *errors = NULL;
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
	if (get_map(data, fd) == 1)
		return (print_error("Get map error\n"));
	if (convert_map_to_int(data) == 1)
		return (print_error("Map conversion error\n"));
	
	data->width_size = data->cell_size * data->tab_width;
	data->height_size = data->cell_size * data->tab_height;

	if (check_map_format(data, &errors) == 1)
	{
		print_map(data, errors);
		return (print_error("Map format error\n"));
	}
	print_map(data, errors);

	dprintf(1, "number of line : %d\n", data->tab_height);
	dprintf(1, "max line length : %d\n", data->tab_width);
	return (0);
}

int	init_parsing(t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
		data->texture_name[i++] = NULL;
	data->map = NULL;
	data->tab_height = 0;
	data->tab_width = 0;
	return (0);
}

int get_map(t_data *data, int fd)
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
		ft_lstadd_back(&data->map, new_elem);
		data->tab_height++;
		buf = get_next_line(fd);
	}
	new_elem = ft_lstnew(NULL);
	if (new_elem == NULL)
		return (1);
	ft_lstadd_back(&data->map, new_elem);
	return (0);
}

int	convert_map_to_int(t_data *data)
{
	int	i;
	int	j;
	int	line_length;
	t_list	*elem;

	dprintf(1, "starting map conversion\n");
	data->tab = malloc(sizeof(int *) * data->tab_height);
	if (data->tab == NULL)
		return (1);
	elem = data->map;
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
				if (str[j] == ' ')
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
