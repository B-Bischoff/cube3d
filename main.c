#include "cube3d.h"

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

	ft_mlx_hooks_and_loop(&data);

	return (0);
}

int	update(t_data *data)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->prev_time)); // Taking time to calculate fps

	clear_window(data);

	set_grid_cell(data, data->mouse_pos.x, data->mouse_pos.y); // Add or remove walls with mouse in runtime
	print_grid(data); // Show walls

	draw_circle(data, vector_f_to_d(data->player.pos)); // Player visualization
	data->plane.x = data->player.dir.x * data->view_dst + data->player.pos.x;
	data->plane.y = data->player.dir.y * data->view_dst + data->player.pos.y;

	bresenham(data, vector_f_to_d(data->player.pos), data->plane, WHITE);

	
	draw_circle_color(data, data->plane, YELLOW);
	create_rays(data, data->player.dir);
	calculate_collisions(data);
	rays_render(data);


	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	print_fps(data);
	return (0);
}
