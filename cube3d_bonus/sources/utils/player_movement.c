#include "cube3d.h"

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data, float coef);
void	rotate_right(t_data *data, float coef);
void	toggle_door(t_data *data);

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

	if (data->keyboard[KEY_E] && !data->prev_keyboard[KEY_E])
	{
		data->prev_keyboard[KEY_E] = 1; // Check if that line can be removed
		toggle_door(data);
	}

	data->show_map = data->keyboard[KEY_TAB];

	if (data->keyboard[KEY_TAB] == 0) // Disable rotation with mouse when map is shown
	{
		if (data->mouse_move.x > 4)
			rotate_right(data, -(float)data->mouse_move.x / 50.0f);
		if (data->mouse_move.x < 4)
			rotate_left(data, (float)data->mouse_move.x / 50.0f);
	}


	// Reset mouse movement
	data->mouse_move.x = 0;

	// Update plane position
	data->player.view_dst_pos.x = data->player.dir.x * data->view_dst + data->player.pos.x;
	data->player.view_dst_pos.y = data->player.dir.y * data->view_dst + data->player.pos.y;

	dprintf(1, "dir | x : %lf | y : %lf\n", data->player.dir.x, data->player.dir.y);

	// data->player.angle = get_angle_f(data->player.pos, vector_d_to_f(data->player.view_dst_pos));
}

void	toggle_door(t_data *data)
{
	t_vector2_d	cell;

	//	- Set targeted cell
	cell.x = data->player.pos.x + (data->player.dir.x * data->cell_size);
	cell.y = data->player.pos.y + (data->player.dir.y * data->cell_size);

	if (!is_in_map(data, cell))
		return ;

	cell.x /= data->cell_size;
	cell.y /= data->cell_size;

	// dprintf(1, "player : %f %f -> %d %d\n", data->player.pos.x/data->cell_size, data->player.pos.y/data->cell_size, cell.x, cell.y);

	// If targeted cell is a door : toggle it
	if (data->tab[cell.y][cell.x] == 2)
		data->tab[cell.y][cell.x] = 3;
	else if (data->tab[cell.y][cell.x] == 3)
		data->tab[cell.y][cell.x] = 2;

	if (data->tab[cell.y][cell.x] == 4)
		data->tab[cell.y][cell.x] = 5;
	else if (data->tab[cell.y][cell.x] == 5)
		data->tab[cell.y][cell.x] = 4;

}

void	move_forward(t_data *data)
{
	double move_speed = 150;
	t_vector2_f	new_pos;
	t_vector2_f	*p_pos = &data->player.pos;

	new_pos.x = data->player.dir.x * move_speed * data->delta_time;
	new_pos.y = data->player.dir.y * move_speed * data->delta_time;

	// Check collision
	if (!is_in_map(data, create_vector_d(p_pos->x + new_pos.x, p_pos->y)))
		p_pos->x += new_pos.x;
	else if (!is_colliding_cell(data, p_pos->x + new_pos.x, p_pos->y, 1))
		p_pos->x += new_pos.x;
	if (!is_in_map(data, create_vector_d(p_pos->x, p_pos->y + new_pos.y)))
		p_pos->y += new_pos.y;
	else if (!is_colliding_cell(data, p_pos->x, p_pos->y + new_pos.y, 1))
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
	if (!is_in_map(data, create_vector_d(p_pos->x - new_pos.x, p_pos->y)))
		p_pos->x -= new_pos.x;
	else if (!is_colliding_cell(data, p_pos->x - new_pos.x, p_pos->y, 1))
		p_pos->x -= new_pos.x;
	if (!is_in_map(data, create_vector_d(p_pos->x, p_pos->y - new_pos.y)))
		p_pos->y -= new_pos.y;
	else if (!is_colliding_cell(data, p_pos->x, p_pos->y - new_pos.y, 1))
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

	// Check collision
	if (!is_in_map(data, create_vector_d(new_pos.x + p_pos->x, p_pos->y))) // If coord is out of tab, increment player pos
		p_pos->x += new_pos.x;
	else if (!is_colliding_cell(data, p_pos->x + new_pos.x, p_pos->y, 1))
		p_pos->x += new_pos.x;
	if (!is_in_map(data, create_vector_d(p_pos->x, new_pos.y + p_pos->y)))
		p_pos->y += new_pos.y;
	else if (!is_colliding_cell(data, p_pos->x, p_pos->y + new_pos.y, 1))
		p_pos->y += new_pos.y;
}

void	move_right(t_data *data)
{
	double move_speed = 150;
	t_vector2_f	*p_pos = &data->player.pos;
	t_vector2_f	new_dir;
	t_vector2_f	new_pos;

	// Calculating direction 90 degree (PI / 2) to the right
	new_dir.x = data->player.dir.x * cos(PI_2) - data->player.dir.y * sin(PI_2);
	new_dir.y = data->player.dir.x * sin(PI_2) + data->player.dir.y * cos(PI_2);

	// Applying that direction to the moving formula
	new_pos.x = new_dir.x * move_speed * data->delta_time;
	new_pos.y = new_dir.y * move_speed * data->delta_time;

	// Check collision

	if (!is_in_map(data, create_vector_d(new_pos.x + p_pos->x, p_pos->y))) // If coord is out of tab, increment player pos
		p_pos->x += new_pos.x;
	else if (!is_colliding_cell(data, p_pos->x + new_pos.x, p_pos->y, 1))
		p_pos->x += new_pos.x;
	if (!is_in_map(data, create_vector_d(p_pos->x, new_pos.y + p_pos->y)))
		p_pos->y += new_pos.y;
	else if (!is_colliding_cell(data, p_pos->x, p_pos->y + new_pos.y, 1))
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