#include "cube3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x >= data->win_width || y >= data->win_height || x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * 4);
	*(unsigned int *)dst = color;
}

void clear_window(t_data *data)
{
	int total = data->win_width * data->win_height;
	int	size = data->bits_per_pixel / 8;

	for (int i = 0; i < total; i++)
	{
		char *dst = data->addr + i * size;
		*(unsigned int *)dst = DARK_GRAY;
	}
}

int	ft_mlx_init(t_data *data)
{
	data->win_width = 1920;
	data->win_height = 1080;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->mlx_win = mlx_new_window(data->mlx, data->win_width, data->win_height, "Cube3d");
	if (data->mlx_win == NULL)
		return (1);
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (data->img == NULL)
		return (1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (data->addr == NULL)
		return (1);
	return (0);
}

void	ft_mlx_hooks_and_loop(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 4, 1L << 2, mouse_hook, data);
	mlx_hook(data->mlx_win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, update_mouse_pos, data);
	mlx_hook(data->mlx_win, 17, 1L << 0, free_all, data);
	mlx_loop_hook(data->mlx, update, data);
	mlx_loop(data->mlx);
}

void	clamp_mouse_in_window(t_data *data)
{
	// Clamp mouse in window
	if (data->keyboard[KEY_TAB])
	{
		MLX_MOUSE_SHOW;
	}
	else
	{
		MLX_MOUSE_HIDE;
		MLX_MOUSE_MOVE;
	}
}
