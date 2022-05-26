#include "cube3d.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(&data, argc, argv) == 1)
		exit (1);
	if (ft_mlx_init(&data) == 1)
		exit (1);
	if (ft_init_vision(&data) == 1)
		exit (1);
	if (init_floor_and_ceiling(&data) == 1)
		exit (1);
	if (init_text(&data) == 1)
		exit (1);

	// Player init

	data.player.pos.x = data.win_width / 4;
	data.player.pos.y = data.win_height / 4;
	data.player.angle = 0.0f;
	data.player.dir.x = -1;
	data.player.dir.y = 0;

	ft_mlx_hooks_and_loop(&data);

	exit (0);
}

