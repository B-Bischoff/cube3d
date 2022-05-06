#include "cube3d.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(&data, argc, argv) == 1)
		exit (1);
	if (init_grid(&data) == 1) // Free everything instead of exit 1 ??
		exit (1);
	if (ft_mlx_init(&data) == 1)
		exit (1);
	if (ft_init_vision(&data) == 1)
		exit (1);

	mlx_mouse_hide();

	data.mouse_pos.x = data.win_width / 2;
	data.mouse_pos.y = data.win_height / 2;
	data.mouse_move.x = 0;
	data.mouse_move.y = 0;
	mlx_mouse_move(data.mlx_win, data.win_width / 2, data.win_height / 2);	
	// Player init (store in function)
	
	// Player pos will be defined by the map
	data.player.pos.x = data.win_width / 4; 
	data.player.pos.y = data.win_height / 4;

	// Initial looking direction of the player
	data.player.dir.x = 1;
	data.player.dir.y = 0;


	ft_mlx_hooks_and_loop(&data);

	return (0);
}
