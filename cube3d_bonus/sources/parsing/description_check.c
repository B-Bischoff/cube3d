#include "cube3d.h"

int	is_valid_description(char *str);

int	format_description(t_data *data, char *str, int *count);
int	assign_description(t_data *data, char *str, int id_value);
/*
	Textures and color order in data->texture_name[6]: 
	0 : North
	1 : South
	2 : West
	3 : East
	4 : Floor
	5 : Ceiling
*/
int	get_description(t_data *data, int fd)
{
	char	*buf;
	int		count;
	int		error;

	count = 0;
	error = 0;
	buf = get_next_line(fd);
	while (buf)
	{
		if (!ft_is_empty_str(buf))
		{
			error = format_description(data, buf, &count);
			if (error == 1)
			{
				free(buf);
				return (1);
			}
		}
		free(buf);
		buf = NULL;
		if (count == 6)
			break ;
		buf = get_next_line(fd);
	}
	if (buf)
		free(buf);
	dprintf(1, "count : %d\n", count);
	if (count < 6)
		return (print_error("Texture indication missing\n"));
	return (0);
}

int	format_description(t_data *data, char *str, int *count)
{
	char	*id;
	int		id_value;
	int		error;

	error = 0;
	id = get_word(str);
	id_value = is_valid_description(id);
	if (id_value != 0)
	{
		if (data->texture_name[id_value - 1] != NULL)
			error = 1;
		else
			error = assign_description(data, ft_strnstr(str, id, ft_strlen(str)), id_value);
		*count += 1;
	}
	free(id);
	// dprintf(1, "data->texture_name : %s | id : %d\n", data->texture_name[id_value - 1], id_value - 1);
	return (error);
}

int	assign_description(t_data *data, char *str, int id_value)
{
	char	*final_str;
	int	i;

	i = 2; // 2 To skip id
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_is_empty_str(str + i))
		return (1);
	final_str = ft_strdup(str + i);
	if (final_str == NULL)
		return (1);	
	final_str[ft_strlen(final_str) - 1] = '\0'; // Removing \n
	data->texture_name[id_value - 1] = final_str;
	return (0);
}


int	is_valid_description(char *str)
{
	int	len = ft_strlen(str);

	if (len > 2)
		return (0);
	if (ft_strnstr(str, "NO", len))
		return (1);
	else if (ft_strnstr(str, "SO", 2))
		return (2);
	else if (ft_strnstr(str, "WE", 2))
		return (3);
	else if (ft_strnstr(str, "EA", 2))
		return (4);
	if (len > 1)
		return (0);
	else if (ft_strnstr(str, "F", 1))
		return (5);
	else if (ft_strnstr(str, "C", 1))
		return (6);
	return (0);
}
