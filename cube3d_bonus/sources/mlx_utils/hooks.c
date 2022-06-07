#include "cube3d.h"

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	data->mouse_pressed = 1;
	data->mouse_pos.x = x;
	data->mouse_pos.y = y;
	data->mouse_button = keycode;

	return (0);
}

int	mouse_release(int keycode, int x, int y, t_data *data)
{
	(void)keycode;
	(void)x;
	(void)y;
	data->mouse_pressed = 0;
	return (0);
}

int	update_mouse_pos(int x, int y, t_data *data)
{
	data->mouse_move.x = data->win_width / 2 - x; // Tell how much the mouse was moved on the X axis
	if (data->mouse_move.y <= 200 && data->mouse_move.y >= -200) //  Tell how much the mouse was moved on the Y axis
	{
		data->mouse_move.y += data->win_height / 2 - y;
		data->mouse_move.y = ft_clamp_d(data->mouse_move.y, -200, 200);
	}
	data->mouse_pos.x = x;
	data->mouse_pos.y = y;

	// Clamp mouse in window
	if (data->keyboard[KEY_TAB])
		MLX_MOUSE_SHOW;
		//mlx_mouse_show();
	else
	{
		MLX_MOUSE_MOVE;
		MLX_MOUSE_HIDE;
	}


	return (0);
}

int	key_press(int keycode, t_data *data)
{
	keycode = keycode % 200;
	if (keycode < 200)
	{
		data->prev_keyboard[keycode] = data->keyboard[keycode];
		data->keyboard[keycode] = 1;
	}
	
	if (data->keyboard[KEY_ESC])
	{
		free_all(data);
		exit (0);
	}

	return (0);
}

int	key_release(int keycode, t_data *data)
{
	keycode = keycode % 200;
	if (keycode < 200)
	{
		data->prev_keyboard[keycode] = data->keyboard[keycode];
		data->keyboard[keycode] = 0;
	}
	return (1);
}