#include "cube3d.h"

int	update(t_data *data)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->prev_time)); // Taking time to calculate fps

	player_input(data);

	// clear_window(data);
	floor_and_ceiling(data);

	// set_grid_cell(data, data->mouse_pos.x, data->mouse_pos.y); // Add or remove walls with mouse in runtime
	// print_grid(data); // Show walls

	// draw_circle(data, vector_f_to_d(data->player.pos)); // Player visualization

	// bresenham(data, vector_f_to_d(data->player.pos), data->plane, WHITE);

	
	// floor_and_ceiling(data);
	create_rays(data);
	calculate_collisions(data);
	rays_render(data);


	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	print_fps(data);
	return (0);
}
