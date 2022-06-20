#include "cube3d.h"

void	print_background_color(char *color);

void	print_map(t_data *data, t_list *errors)
{
	int	y;
	int	x;
	t_vector2_d *error_pos = NULL;

	y = 0;
	if (errors != NULL)
		error_pos = errors->content;
	while (y < data->tab_height)
	{
		x = 0;
		while (x < data->tab_width)
		{
			if (error_pos != NULL && error_pos->x == x && error_pos->y == y)
			{
				print_background_color(TERM_BCKG_RED);
				errors = errors->next;
				if (errors->content != NULL)
					error_pos = errors->content;
			}
			else if (data->tab[y][x] == -1)
				ft_putstr_fd("  ", 1);
			else if (data->tab[y][x] == 0)
				print_background_color(TERM_BCKG_BLUE);
			else
				print_background_color(TERM_BCKG_WHITE);
			x++;
		}
		ft_putchar_fd('\n', 1);
		y++;
	}
}

void	print_background_color(char *color)
{
	ft_putstr_fd(color, 1);
	ft_putstr_fd("  ", 1);
	ft_putstr_fd(TERM_BCKG_END, 1);
}
