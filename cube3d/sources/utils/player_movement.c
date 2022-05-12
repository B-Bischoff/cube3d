#include "cube3d.h"

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data, float coef);
void	rotate_right(t_data *data, float coef);

void	player_input(t_data *data)
{
	if (data->keyboard[KEY_UP] || data->keyboard[KEY_W])
		move_forward(data);
	if (data->keyboard[KEY_DOWN] || data->keyboard[KEY_S])
		move_backward(data);
	if (data->keyboard[KEY_A])
		move_left(data);
	if (data->keyboard[KEY_D])
		move_right(data);
	if (data->keyboard[KEY_LEFT])
		rotate_left(data, 1);
	if (data->keyboard[KEY_RIGHT])
		rotate_right(data, 1);

	// Update plane position
	data->plane.x = data->player.dir.x * data->view_dst + data->player.pos.x;
	data->plane.y = data->player.dir.y * data->view_dst + data->player.pos.y;
}

void	move_forward(t_data *data)
{
	double move_speed = 150;
	t_vector2_f	new_pos;
	t_vector2_f	*p_pos = &data->player.pos;

	new_pos.x = data->player.dir.x * move_speed * data->delta_time;
	new_pos.y = data->player.dir.y * move_speed * data->delta_time;

	p_pos->x += new_pos.x;
	p_pos->y += new_pos.y;
}

void	move_backward(t_data *data)
{
	double move_speed = 150;
	t_vector2_f	new_pos;
	t_vector2_f	*p_pos = &data->player.pos; // Reference to player position

	new_pos.x = data->player.dir.x * move_speed * data->delta_time; 
	new_pos.y = data->player.dir.y * move_speed * data->delta_time; 

	p_pos->x -= new_pos.x;
	p_pos->y -= new_pos.y;
}

void	move_left(t_data *data)
{	
	double move_speed = 150;
	t_vector2_f	*p_pos = &data->player.pos;
	t_vector2_f	new_dir;
	t_vector2_f	new_pos;

	// Calculating direction 90 degree (PI / 2) to the left
	new_dir.x = data->player.dir.x * cos(-PI_2) - data->player.dir.y * sin(-PI_2);
	new_dir.y = data->player.dir.x * sin(-PI_2) + data->player.dir.y * cos(-PI_2);

	// Applying that direction to the moving formula
	new_pos.x = new_dir.x * move_speed * data->delta_time;
	new_pos.y = new_dir.y * move_speed * data->delta_time;

	p_pos->x += new_pos.x;
	p_pos->y += new_pos.y;
}

void	move_right(t_data *data)
{
	double move_speed = 150;
	t_vector2_f	*p_pos = &data->player.pos;
	t_vector2_f	new_dir;
	t_vector2_f	new_pos;

	// Calculating direction 90 degree (PI / 2) to the left
	new_dir.x = data->player.dir.x * cos(PI_2) - data->player.dir.y * sin(PI_2);
	new_dir.y = data->player.dir.x * sin(PI_2) + data->player.dir.y * cos(PI_2);

	// Applying that direction to the moving formula
	new_pos.x = new_dir.x * move_speed * data->delta_time;
	new_pos.y = new_dir.y * move_speed * data->delta_time;

	// Check collision

	p_pos->x += new_pos.x;
	p_pos->y += new_pos.y;
}

void	rotate_left(t_data *data, float coef)
{
	double rot_speed = 1.5f * coef * data->delta_time;
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
	data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
}
void	rotate_right(t_data *data, float coef)
{
	double rot_speed = 1.5f * coef * data->delta_time;
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
	data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
}