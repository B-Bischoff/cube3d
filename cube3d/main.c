#include "cube3d.h"

void	initialize_text(t_data *data)
{
	int	i;
	// int	n;

	i = -1;
	while (++i < 6)
	{
		data->text[i].text = mlx_xpm_file_to_image(data->mlx, "../assets/eagle.xpm",
												&data->text[i].long_img, &data->text[i].lar_img);
		data->text[i].text_adr = mlx_get_data_addr(data->text[i].text, &data->text[i].bit, &data->text[i].size_line, &data->text[i].endian);
	}

	i = -1;
	while (++i < data->rays_nb)
	{
		data->rays[i].text_buf[0] = calloc(data->win_height, sizeof(unsigned int));
		data->rays[i].text_buf[1] = calloc(data->win_height, sizeof(unsigned int));
	}
}

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

	// Player init
	data.player.pos.x = data.win_width / 4;
	data.player.pos.y = data.win_height / 4;
	data.player.angle = 0.0f;
	data.player.dir.x = -1;
	data.player.dir.y = 0;
	data.plane.x = data.player.pos.x + data.view_dst * data.player.dir.x;
	data.plane.y = data.player.pos.y + data.view_dst * data.player.dir.y;

	initialize_text(&data);



	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->text[0].text_adr, 0, 0);


	ft_mlx_hooks_and_loop(&data);

	return (0);
}

