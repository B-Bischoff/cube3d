#include "cube3d.h"

int	init_parsing(t_data *data);
int	check_file_extension(char *str);

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
	if (check_file_extension(argv[1]) == 1)
		return (print_error("Wrong file extension"));
	fd = open(argv[1], O_RDONLY);	
	if (fd == -1)
		return (print_error("Map opening error\n"));
	if (get_description(data, fd) == 1)
		return (print_error("Description error\n"));
	if (get_map(data, fd, &map) == 1)
		return (print_error("Get map error\n"));
	close(fd);
	if (convert_map_to_int(data, &map) == 1)
	{
		ft_lstclear(&map, free);
		return (print_error("Map conversion error\n"));
	}

	ft_lstclear(&map, free);
	data->width_size = data->cell_size * data->tab_width;
	data->height_size = data->cell_size * data->tab_height;

	if (check_player_pos(data) == 1)
		return (print_error("Player pos error\n"));

	if (count_sprites(data) == 1)
		return (print_error("Sprite couting error\n"));

	if (check_map_format(data, &errors) == 1)
	{
		print_map(data, errors);
		ft_lstclear(&errors, free);
		return (print_error("Map format error\n"));
	}
	print_map(data, errors);
	ft_lstclear(&errors, free);

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
	data->nb_sprites = 0;
	data->show_map = 0;

	return (0);
}

int	check_file_extension(char *str)
{
	int length = ft_strlen(str);

	if (length <= 4 || str[length - 5] == '/')
		return (1);
	if (ft_strncmp(str + length - 4, ".cub", 4))
		return (1);
	return (0);
}
