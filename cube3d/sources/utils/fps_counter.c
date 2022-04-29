#include "cube3d.h"

void	print_fps(t_data *data)
{
	double	delta_time;
	char	*fps;

	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->curr_time));
	delta_time = (data->curr_time.tv_nsec - data->prev_time.tv_nsec) / 1000;
	fps = ft_itoa(1 / (delta_time / 1000000));
	mlx_string_put(data->mlx, data->mlx_win, 30, 50, WHITE, "FRAME: ");
	mlx_string_put(data->mlx, data->mlx_win, 100, 50, WHITE, fps);
}
