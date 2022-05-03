#include "cube3d.h"

void	initialize_text(t_data *data)
{
	int	i;
	

	i = -1;
	while (++i < 6)
	{
		data->text[i].text = mlx_xpm_file_to_image(data->mlx, "./purplestone.xpm",
												&data->text[i].long_img, &data->text[i].lar_img);
		data->text[i].text_adr = mlx_get_data_addr(data->text[i].text, &data->text[i].bit, &data->text[i].size_line, &data->text[i].endian);
	}

	// t_color	color;
	// char	*str;

	// for (int y = 0; y < data->text[0].long_img; y++)
	// {
	// 	for (int x = 0; x < data->text[0].lar_img; x++)
	// 	{
	// 		str = &data->text[0].text_adr[y * data->text[0].size_line + x * (data->text[0].bit / 8)];
	// 		color.str[0] = str[0];
	// 		color.str[1] = str[1];
	// 		color.str[2] = str[2];
	// 		color.str[3] = str[3];
			
	// 		mlx_pixel_put(data->img, data->mlx_win, x, y, color.color);
	// 	}
	// }
}

int main(void)
{
	t_data	data;

	if (init_grid(&data) == 1) // Free everything instead of exit 1 ??
		exit (1);
	if (ft_mlx_init(&data) == 1)
		exit (1);
	if (ft_init_vision(&data) == 1)
		exit (1);

	// Player init
	data.player.pos.x = data.win_width / 2;
	data.player.pos.y = data.win_height / 2;
	data.player.angle = 0.0f;
	data.player.dir.x = -1;
	data.player.dir.y = 0;
	data.plane.x = data.player.pos.x + data.view_dst * data.player.dir.x;
	data.plane.y = data.player.pos.y + data.view_dst * data.player.dir.y;

	initialize_text(&data);

	ft_mlx_hooks_and_loop(&data);

	return (0);
}

int	update(t_data *data)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->prev_time)); // Taking time to calculate fps

	

	
	clear_window(data);


	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
    	{
			// char *str = &data->text[0].text_adr[x * (data->bits_per_pixel / 8) + y * data->line_length];
			unsigned int color = (*(unsigned int *)(&data->text[0].text_adr[(y * data->line_length + x) * (data->bits_per_pixel / 8)]));
			my_mlx_pixel_put(data, x, y, color);
		}
	}

	// set_grid_cell(data, data->mouse_pos.x, data->mouse_pos.y); // Add or remove walls with mouse in runtime
	// print_grid(data); // Show walls

	// draw_circle(data, vector_f_to_d(data->player.pos)); // Player visualization
	// data->plane.x = data->player.dir.x * data->view_dst + data->player.pos.x;
	// data->plane.y = data->player.dir.y * data->view_dst + data->player.pos.y;

	// bresenham(data, vector_f_to_d(data->player.pos), data->plane, WHITE);

	// draw_circle_color(data, data->plane, YELLOW);
	// create_rays(data, data->player.dir);
	// calculate_collisions(data);
	// rays_render(data);

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);

	// print_fps(data);
	return (0);
}
