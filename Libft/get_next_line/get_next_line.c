#include "../libft.h"

void	init_variables(char **temp_buf, char **buf, int *read_val);
void	init_loop(char **buf, int *read_val, int fd);

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	char		*temp_buf;
	int			read_val;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	init_variables(&temp_buf, &buf[fd], &read_val);
	while (read_val > 0 && is_newline_gnl(buf[fd]) == -1)
	{
		init_loop(&buf[fd], &read_val, fd);
		if (read_val <= 0)
		{
			free(buf[fd]);
			buf[fd] = NULL;
			if (read_val == 0 && temp_buf && temp_buf[0])
				return (temp_buf);
			free(temp_buf);
			return (NULL);
		}
		temp_buf = ft_strjoin_gnl(temp_buf, buf[fd]);
	}
	if (is_newline_gnl(buf[fd]) != -1)
		ft_memmove(buf[fd], buf[fd] + is_newline_gnl(buf[fd]),
			BUFFER_SIZE - is_newline_gnl(buf[fd]) + 1);
	return (temp_buf);
}

void	init_variables(char **temp_buf, char **buf, int *read_val)
{
	*temp_buf = NULL;
	if (*buf != NULL)
		*temp_buf = ft_strjoin_gnl(*temp_buf, *buf);
	else
		*buf = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	*read_val = 1;
}

void	init_loop(char **buf, int *read_val, int fd)
{
	free(*buf);
	*buf = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	*read_val = read(fd, *buf, BUFFER_SIZE);
}
