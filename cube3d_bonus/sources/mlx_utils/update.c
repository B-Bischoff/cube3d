#include "cube3d.h"

int	update(t_data *data)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->prev_time)); // Taking time to calculate fps

	player_input(data);

	if (data->mouse_pressed == 1)
		set_grid_cell(data, data->mouse_pos.x, data->mouse_pos.y); // Add or remove walls with mouse in runtime

	if (data->show_map)
	{
		clear_window(data);
		print_grid(data); // Show walls
		bresenham(data, vector_f_to_d(data->player.pos), data->player.view_dst_pos, WHITE);
		draw_circle(data, vector_f_to_d(data->player.pos)); // Player visualization
	}

	create_rays(data);
	calculate_collisions(data);
	if (!data->show_map)
	{
		floor_and_ceiling(data);
		rays_render(data);
		render_sprite(data);
		print_minimap(data);
	}

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);

	print_fps(data);
	return (0);
}
