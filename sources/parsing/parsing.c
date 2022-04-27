#include "cube3d.h"

int	get_description(t_data *data, int fd);
int	get_map(t_data *data, int fd);
int	convert_map_to_int(t_data *data);
int	check_map_format(t_data *data);

/*
	textures name are stored in data->texture_name
	
	1st str : NO informations
	2nd str : SO informations
	3rd str : WE informations
	4th str : EA informations
	5th str : F informations
	6th str : C informations
	
	Each line of the map is stored in a linked list
*/
int	parsing(t_data *data, int argc, char *argv[])
{
	int	fd;

	if (argc != 2)
	{
		dprintf(1, "Wrong number of arguments\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);	
	if (fd == -1)
	{
		dprintf(1, "Cannot open the map\n");
		return (1);
	}

	for (int i = 0; i < 6; i++)
		data->texture_name[i] = NULL;
	data->map = NULL;
	data->tab_height = 0;
	data->tab_width = 0;

	if (get_description(data, fd) == 1)
		return (1);
	if (get_map(data, fd) == 1)
		return (1);
	if (convert_map_to_int(data) == 1)
		return (1);

	dprintf(1, "max line length ; %d\n", data->tab_width);
	dprintf(1, "number of line : %d\n", data->tab_height);

	return (0);
}

int	is_valid_description(char *str)
{
	int	len = ft_strlen(str);

	if (ft_strnstr(str, "NO ", len))
		return (1);
	else if (ft_strnstr(str, "SO ", len))
		return (2);
	else if (ft_strnstr(str, "WE ", len))
		return (3);
	else if (ft_strnstr(str, "EA ", len))
		return (4);
	else if (ft_strnstr(str, "F ", len))
		return (5);
	else if (ft_strnstr(str, "C ", len))
		return (6);
	return (0);
}

int	get_description(t_data *data, int fd)
{
	char	*buf;
	char	*str;
	int		count = 0;
	int		i;

	buf = get_next_line(fd);
	while (buf)
	{
		i = is_valid_description(buf);
		if (i != 0)
		{
			if (data->texture_name[i - 1] != NULL)
			{
				dprintf(1, "Multiple texture definition\n");
				return (1);
			}
			// Removing id information
			str = ft_strdup(buf);
			str[ft_strlen(str) - 1] = '\0'; // Removing \n 
			str = ft_memmove(str, str + 3, ft_strlen(str));
			data->texture_name[i - 1] = str;
			dprintf(1, "%s\n",str);
			count++;
		}
		free(buf);
		if (count >= 6)
			break ;
		buf = get_next_line(fd);
	}
	if (count < 6)
		return (1);
	return (0);
}

int get_map(t_data *data, int fd)
{
	char	*buf;
	t_list	*new_elem;
	int		length;

	dprintf(1, "displaying map\n");

	buf = get_next_line(fd);
	while (buf)
	{
		dprintf(1, "%s", buf);
		new_elem = ft_lstnew(buf);
		if (new_elem == NULL)
			return (1);
		ft_lstadd_back(&data->map, new_elem);
		length = ft_strlen(buf);
		buf[length - 1] = '\0';
		length--;
		if (length > data->tab_width)
			data->tab_width = length;
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

	(void)data;
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
		// Copying datas from linked list to tab
		j = 0;
		char	*str = elem->content;
		line_length = ft_strlen(str);
		while (j < data->tab_width)
		{
			if (j < line_length)
			{
				data->tab[i][j] = str[j] - 48;
				dprintf(1, "%d", data->tab[i][j]);
			}
			else
			{
				data->tab[i][j] = 0;
				dprintf(1, "%d", data->tab[i][j]);
			}
			j++;
		}	
		elem = elem->next;
		i++;
		dprintf(1, "\n");
	}	
	dprintf(1, "end map conversion\n");
	return (0);
}

int	check_map_format(t_data *data)
{
	(void)data;
	return (0);
}