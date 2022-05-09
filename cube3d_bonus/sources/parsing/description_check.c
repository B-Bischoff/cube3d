#include "cube3d.h"

int	is_valid_description(char *str);

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
	char	*str;
	int		count = 0;
	int		i;

	buf = get_next_line(fd);
	add_to_garbage(buf, &data->garbage);
	while (buf)
	{
		i = is_valid_description(buf);
		if (i != 0)
		{
			if (data->texture_name[i - 1] != NULL)
				return (print_error("Multiple texture definition\n"));
			// Removing id information
			str = ft_strdup(buf);
			str[ft_strlen(str) - 1] = '\0'; // Removing \n 
			str = ft_memmove(str, str + 3, ft_strlen(str));
			data->texture_name[i - 1] = str;
			count++;
		}
		if (count >= 6)
			break ;
		buf = get_next_line(fd);
		add_to_garbage(buf, &data->garbage);
	}
	if (count < 6)
		return (print_error("Texture indication missing\n"));
	return (0);
}

int	is_valid_description(char *str)
{
	// MIGHT IMPROVE THAT FUNCTION TO CHECK FULL WORD INSTEAD OF FIRSTS CHARS
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
