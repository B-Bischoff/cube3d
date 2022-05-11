#include "cube3d.h"

void	initialize_text(t_data *data)
{
	data->textures = malloc(sizeof(t_text));
	data->textures[0].text = mlx_xpm_file_to_image(data->mlx, "../assets/barrel.xpm", &data->textures[0].width_img, &data->textures[0].height_img);
	data->textures[0].text_adr = mlx_get_data_addr(data->textures[0].text, &data->textures[0].bit, &data->textures[0].size_line, &data->textures[0].endian);
}

int main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(&data, argc, argv) == 1)
		exit (1);
	if (ft_mlx_init(&data) == 1)
		exit (1);
	if (ft_init_vision(&data) == 1)
		exit (1);

	initialize_text(&data);
	sprites_init(&data);

	mlx_mouse_hide();
	data.mouse_pos.x = data.win_width / 2;
	data.mouse_pos.y = data.win_height / 2;
	data.mouse_move.x = 0;
	data.mouse_move.y = 0;
	mlx_mouse_move(data.mlx_win, data.win_width / 2, data.win_height / 2);	

	ft_mlx_hooks_and_loop(&data);

	free_all(&data);
	exit (0);
}
