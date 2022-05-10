#include "cube3d.h"

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	data->mouse_pressed = 1;
	data->mouse_pos.x = x;
	data->mouse_pos.y = y;
	data->mouse_button = keycode;

	set_grid_cell(data, x, y);

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
	if (data->mouse_pressed == 1)
	{
		data->mouse_pos.x = x;
		data->mouse_pos.y = y;
	}
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode < 200)
		data->keyboard[keycode] = 1;
	
	if (data->keyboard[KEY_ESC])
	{
		exit (0);
	}

	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode < 200)
		data->keyboard[keycode] = 0;
	return (1);
}