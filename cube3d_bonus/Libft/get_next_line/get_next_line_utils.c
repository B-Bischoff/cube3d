#include "../libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;

	if (s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (i != 0 && s2[i - 1] == '\n')
			break ;
		str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + i] = '\0';
	free(s1);
	return (str);
}

int	is_newline_gnl(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
		if (str[i++] == '\n')
			return (i);
	return (-1);
}
