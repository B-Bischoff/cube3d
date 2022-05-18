#include "cube3d.h"

int	convert_colors_to_int(char *str_color);

int	init_textures(t_data *data)
{
	// Textures gave in map description

	// Floor and ceiling colors
	data->floor_color = convert_colors_to_int(data->texture_name[4]);
	if (data->floor_color == -1)
		return (print_error("Invalid floor color\n"));
	data->ceiling_color = convert_colors_to_int(data->texture_name[5]);
	if (data->ceiling_color == -1)
		return (print_error("Invalid floor color\n"));
	return (0);
}

/*
	Return -1 if an error occured
	Return the color in normal case
*/
int	convert_colors_to_int(char *str_color)
{
	int		i;
	int		color[3]; // [R][G][B]
	char	**tab;
	int		error;

	error = 0;
	tab = ft_split(str_color, ',');
	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (i < 3)
		{
			color[i] = ft_atoi(tab[i]);
			if (color[i] < 0 || color[i] > 255)
				error = 1;
		}
		else
			error = 1;
		free(tab[i]);
		i++;
	}
	free(tab);
	if (error || i < 3)
		return (-1);
	return (create_trgb(0, color[0], color[1], color[2]));
}