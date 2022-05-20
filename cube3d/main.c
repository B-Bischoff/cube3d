#include "cube3d.h"

void	initialize_text(t_data *data)
{
	int	i;
	
	i = -1;
	while (++i < 6)
	{
		data->text[i].text = mlx_xpm_file_to_image(data->mlx, "../assets/photo.xpm",
												&data->text[i].width_img, &data->text[i].height_img);
		data->text[i].text_adr = mlx_get_data_addr(data->text[i].text, &data->text[i].bit, &data->text[i].size_line, &data->text[i].endian);
	}
	dprintf(1, "height %d  width %d\n", data->text[0].height_img, data->text[0].width_img);

	i = -1;
	while (++i < data->rays_nb)
		data->rays[i].text_buf = calloc(data->win_height, sizeof(unsigned int));

	data->floor_celling = malloc(sizeof(unsigned int) * data->win_width * data->win_height / 2);
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

	// Player init

	data.player.pos.x = data.win_width / 4;
	data.player.pos.y = data.win_height / 4;
	data.player.angle = 0.0f;
	data.player.dir.x = -1;
	data.player.dir.y = 0;

	initialize_text(&data);

	ft_mlx_hooks_and_loop(&data);

	exit (0);
}

