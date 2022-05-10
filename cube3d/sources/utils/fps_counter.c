#include "cube3d.h"

/*
* Delta time is used to calculate the refresh rate (in frame per second) of the program
* It is also used to make the player movement consistent according to the refresh rate
*      -> a good pc would make the player move faster than a slow pc
*
* good explanation of delta time concept :
* https://www.gamecodeur.fr/a-propos-du-delta-time/
*/
void	print_fps(t_data *data)
{
	double	delta_time;
	char	*fps;

	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->curr_time));	

	delta_time = (data->curr_time.tv_nsec - data->prev_time.tv_nsec) / 1000;
	delta_time /= 1000000;
	fps = ft_itoa(1 / delta_time);
	mlx_string_put(data->mlx, data->mlx_win, 30, 50, WHITE, "FRAME: ");
	mlx_string_put(data->mlx, data->mlx_win, 100, 50, WHITE, fps);
	// dprintf(1, "%lf", delta_time);
	if (delta_time < 0.01666f) // if fps is greater than 60 fps, cap delta time to 1 / 60
		data->delta_time = 0.01666f;
	else if (delta_time > 0.0f)
		data->delta_time = delta_time;
	free(fps);
}