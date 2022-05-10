#include "cube3d.h"

int	update(t_data *data)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &(data->prev_time)); // Taking time to calculate fps

<<<<<<< HEAD
	player_input(data);

	// clear_window(data);
	floor_and_ceiling(data);
=======
>>>>>>> 3ba47e90d177c4ab545873242d17002cbe08c4a7

	clear_window(data);
	// // floor_and_ceiling(data);

	set_grid_cell(data, data->mouse_pos.x, data->mouse_pos.y); // Add or remove walls with mouse in runtime
	print_grid(data); // Show walls

	draw_circle(data, vector_f_to_d(data->player.pos)); // Player visualization
	data->plane.x = data->player.dir.x * data->view_dst + data->player.pos.x;
	data->plane.y = data->player.dir.y * data->view_dst + data->player.pos.y;

	bresenham(data, vector_f_to_d(data->player.pos), data->plane, WHITE);

	
<<<<<<< HEAD
=======
	// draw_circle_color(data, data->plane, YELLOW);
>>>>>>> 3ba47e90d177c4ab545873242d17002cbe08c4a7
	create_rays(data, data->player.dir);
	calculate_collisions(data);
	add_text_pix(data);
	rays_render(data);


	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	print_fps(data);
	return (0);
}
