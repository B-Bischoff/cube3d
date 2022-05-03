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
	(void)data;
	if (keycode < 200)
		data->keyboard[keycode] = 1;
	
	if (data->keyboard[KEY_ESC])
	{
		// Free allocated stuff
		exit (0);
	}

	double move_speed = 10;
	double rot_speed = 0.05f;
	if (data->keyboard[KEY_RIGHT])
	{
		double old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
		data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
	}
	else if (data->keyboard[KEY_LEFT])
	{
		double old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
		data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
	}
	if (data->keyboard[KEY_DOWN])
	{
		data->player.pos.x += data->player.dir.x * move_speed; 
		data->player.pos.y += data->player.dir.y * move_speed; 
	}
	else if (data->keyboard[KEY_UP])
	{
		data->player.pos.x -= data->player.dir.x * move_speed; 
		data->player.pos.y -= data->player.dir.y * move_speed; 
	}

	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode < 200)
		data->keyboard[keycode] = 0;
	return (1);
}