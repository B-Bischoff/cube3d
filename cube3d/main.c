#include "cube3d.h"

void	initialize_text(t_data *data)
{
	int	i;
	

	i = -1;
	while (++i < 6)
	{
		data->text[i].text = mlx_xpm_file_to_image(data->mlx, "../assets/purplestone.xpm",
												&data->text[i].long_img, &data->text[i].lar_img);
		data->text[i].text_adr = mlx_get_data_addr(data->text[i].text, &data->text[i].bit, &data->text[i].size_line, &data->text[i].endian);
	}

	// t_color	color;
	// char	*str;

	// for (int y = 0; y < data->text[0].long_img; y++)
	// {
	// 	for (int x = 0; x < data->text[0].lar_img; x++)
	// 	{
	// 		str = &data->text[0].text_adr[y * data->text[0].size_line + x * (data->text[0].bit / 8)];
	// 		color.str[0] = str[0];
	// 		color.str[1] = str[1];
	// 		color.str[2] = str[2];
	// 		color.str[3] = str[3];
			
	// 		mlx_pixel_put(data->img, data->mlx_win, x, y, color.color);
	// 	}
	// }
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
	data.player.pos.x = data.win_width / 2;
	data.player.pos.y = data.win_height / 2;
	data.player.angle = 0.0f;
	data.player.dir.x = -1;
	data.player.dir.y = 0;
	data.plane.x = data.player.pos.x + data.view_dst * data.player.dir.x;
	data.plane.y = data.player.pos.y + data.view_dst * data.player.dir.y;

	initialize_text(&data);

	ft_mlx_hooks_and_loop(&data);

	return (0);
}

