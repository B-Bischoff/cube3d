#include "cube3d.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(&data, argc, argv) == 1)
		exit(1);
	if (ft_mlx_init(&data) == 1)
		exit(1);
	if (ft_init_vision(&data) == 1)
		exit(1);
	if (init_floor_and_ceiling(&data) == 1)
		exit(1);
	if (init_text(&data) == 1)
		exit (1);
	if (sprites_init(&data) == 1)
		exit (1);

	// Mouse init
	//mlx_mouse_hide();
	data.mouse_pos.x = data.win_width / 2;
	data.mouse_pos.y = data.win_height / 2;
	data.mouse_move.x = 0;
	data.mouse_move.y = 0;
	//mlx_mouse_move(data.mlx_win, data.win_width / 2, data.win_height / 2);	

	ft_mlx_hooks_and_loop(&data);
	free_all(&data);
}
