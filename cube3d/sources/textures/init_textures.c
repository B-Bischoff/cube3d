#include "cube3d.h"

int	convert_colors_to_int(char *str_color);

int	init_floor_and_ceiling(t_data *data)
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
		int j = 0;
		while (tab[i][j] == ' ')
			j++;
		if (i < 3)
		{
			while (tab[i][j])
			{
				if (ft_isdigit(tab[i][j]) == 0)
					error = 1;
				j++;
			}
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

int		load_texture(t_data *data, t_text *texture, char *texture_path)
{
	texture->text = mlx_xpm_file_to_image(data->mlx, texture_path, &texture->width_img, &texture->height_img);
	if (texture->text == NULL)
	{
		dprintf(2, "Failed to load texture : \"%s\"\n", texture_path);
		return (1);
	}
	texture->text_adr = mlx_get_data_addr(texture->text, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (texture->text_adr == NULL)
	{
		dprintf(2, "Failed to get text_adr of : \"%s\"\n", texture_path);
		return (1);
	}
	return (0);
}

int	init_text(t_data *data)
{
	int	error;

	error = 0;
	data->textures = malloc(sizeof(t_text) * 23);
	if (data->textures == NULL)
		return (1);


	error |= load_texture(data, &data->textures[0], data->texture_name[0]);
	error |= load_texture(data, &data->textures[1], data->texture_name[1]);
	error |= load_texture(data, &data->textures[2], data->texture_name[2]);
	error |= load_texture(data, &data->textures[3], data->texture_name[3]);

	error |= load_texture(data, &data->textures[4], "../assets/barrel.xpm");
	error |= load_texture(data, &data->textures[5], "../assets/pillar.xpm");

	// Animated sprites
	error |= load_texture(data, &data->textures[6], "../assets/mguard/mguard_w1_1.xpm");
	error |= load_texture(data, &data->textures[7], "../assets/mguard/mguard_w2_1.xpm");
	error |= load_texture(data, &data->textures[8], "../assets/mguard/mguard_w3_1.xpm");
	error |= load_texture(data, &data->textures[9], "../assets/mguard/mguard_w4_1.xpm");

	error |= load_texture(data, &data->textures[10], "../assets/soldier_xpm/soldier_1.xpm");
	error |= load_texture(data, &data->textures[11], "../assets/soldier_xpm/soldier_2.xpm");
	error |= load_texture(data, &data->textures[12], "../assets/soldier_xpm/soldier_3.xpm");
	error |= load_texture(data, &data->textures[13], "../assets/soldier_xpm/soldier_4.xpm");
	error |= load_texture(data, &data->textures[14], "../assets/soldier_xpm/soldier_5.xpm");
	error |= load_texture(data, &data->textures[15], "../assets/soldier_xpm/soldier_6.xpm");
	error |= load_texture(data, &data->textures[16], "../assets/soldier_xpm/soldier_7.xpm");
	error |= load_texture(data, &data->textures[17], "../assets/soldier_xpm/soldier_8.xpm");
	error |= load_texture(data, &data->textures[18], "../assets/soldier_xpm/soldier_9.xpm");
	error |= load_texture(data, &data->textures[19], "../assets/soldier_xpm/soldier_10.xpm");
	error |= load_texture(data, &data->textures[20], "../assets/soldier_xpm/soldier_11.xpm");
	error |= load_texture(data, &data->textures[21], "../assets/soldier_xpm/soldier_12.xpm");



	error |= load_texture(data, &data->textures[22], "../assets/door.xpm");
	
	if (error == 1)
		dprintf(2, "Texture loading error\n");

	return (error);
}

