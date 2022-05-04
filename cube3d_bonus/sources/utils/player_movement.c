#include "cube3d.h"

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);

void	player_input(t_data *data)
{
	if (data->keyboard[KEY_UP])
		move_forward(data);
	if (data->keyboard[KEY_DOWN])
		move_backward(data);
	if (data->keyboard[KEY_A])
		move_left(data);
	if (data->keyboard[KEY_LEFT])
		rotate_left(data);
	if (data->keyboard[KEY_RIGHT])
		rotate_right(data);

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

	// Check collision
	if (data->tab[(int)p_pos->y / data->cell_size][(int)(p_pos->x + new_pos.x) / data->cell_size] != 1)
		p_pos->x += new_pos.x;
	if (data->tab[(int)(p_pos->y + new_pos.y) / data->cell_size][(int)p_pos->x / data->cell_size] != 1)
		p_pos->y += new_pos.y;
}

void	move_backward(t_data *data)
{
	double move_speed = 150;
	t_vector2_f	new_pos;
	t_vector2_f	*p_pos = &data->player.pos; // Reference to player position

	new_pos.x = data->player.dir.x * move_speed * data->delta_time; 
	new_pos.y = data->player.dir.y * move_speed * data->delta_time; 
	
	// check collision
	if (data->tab[(int)p_pos->y / data->cell_size][(int)(p_pos->x - new_pos.x) / data->cell_size] != 1)
		p_pos->x -= new_pos.x;
	if (data->tab[(int)(p_pos->y - new_pos.y) / data->cell_size][(int)p_pos->x / data->cell_size] != 1)
		p_pos->y -= new_pos.y;
}

void	move_left(t_data *data)
{	
	double move_speed = 150;
	t_vector2_f	new_pos;
	t_vector2_f	*p_pos = &data->player.pos;

	new_pos.x = (data->player.dir.x - cos(PI_2) * 2) * move_speed * data->delta_time;
	new_pos.y = (data->player.dir.y - sin(PI_2) * 2) * move_speed * data->delta_time;

	// Check collision
	if (data->tab[(int)p_pos->y / data->cell_size][(int)(p_pos->x + new_pos.x) / data->cell_size] != 1)
		p_pos->x -= new_pos.x;
	if (data->tab[(int)(p_pos->y + new_pos.y) / data->cell_size][(int)p_pos->x / data->cell_size] != 1)
		p_pos->y += new_pos.y;
}

void	rotate_left(t_data *data)
{
	double rot_speed = 1.5f * data->delta_time;
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
	data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
}
void	rotate_right(t_data *data)
{
	double rot_speed = 1.5f * data->delta_time;
	double old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
	data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
}