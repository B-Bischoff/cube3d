#include "cube3d.h"

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

void	player_input(t_data *data)
{
	if (data->keyboard[KEY_UP])
		move_forward(data);
	if (data->keyboard[KEY_DOWN])
		move_backward(data);
	if (data->keyboard[KEY_LEFT])
		rotate_left(data);
	if (data->keyboard[KEY_RIGHT])
		rotate_right(data);
}

void	move_forward(t_data *data)
{

	double move_speed = 10;
	data->player.pos.x -= data->player.dir.x * move_speed; 
	data->player.pos.y -= data->player.dir.y * move_speed; 
}

void	move_backward(t_data *data)
{
	double move_speed = 10;
	data->player.pos.x += data->player.dir.x * move_speed; 
	data->player.pos.y += data->player.dir.y * move_speed; 
}
void	rotate_left(t_data *data)
{
	double rot_speed = .05f;
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
	data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
}
void	rotate_right(t_data *data)
{
	double rot_speed = .05f;
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
	data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
}