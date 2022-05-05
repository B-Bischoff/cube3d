#include "../libft.h"

int	ft_is_empty_str(char *str)
{
	char	c;
	int		i;

	i = 0;
	while (str[i])	
	{
		c = str[i];
		if (c != ' ' || c != '\n')
			return (1);
		i++;
	}
	return (0);
}