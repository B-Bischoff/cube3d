#include "cube3d.h"

void	initialize_text(t_data *data)
{
	int	i;
	// int	n;

	i = -1;
	while (++i < 6)
	{
		data->text[i].text = mlx_xpm_file_to_image(data->mlx, "../assets/purplestone.xpm",
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
	if (ft_mlx_init(&data) == 1)
		exit (1);
	if (ft_init_vision(&data) == 1)
		exit (1);
	initialize_text(&data);

	ft_mlx_hooks_and_loop(&data);

	exit (0);
}

