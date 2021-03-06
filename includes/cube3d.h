#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>

# include "alias.h"
# include "../Libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>

typedef struct s_ray
{
	t_vector2_f	hit_point;
	t_vector2_d cell;
	double		length;
	double		perp_length;
	double		angle;
	int			side_hit;
	t_vector2_f	ray_dir;
	
	// Might add texture, color, etc

}	t_ray;

typedef	struct s_player
{
	t_vector2_f	pos;
	t_vector2_d	view_dst_pos;
	t_vector2_f	dir;
}	t_player;

/*
	Tab values :
	-1: Out of map cell
	0 : Empty cell
	1 : Wall
	2 : Horizontal door closed
	3 : Horizontal door opened
	4 : Vertical door closed
	5 : Vertical door opened
	6 : Barrel sprite
	7 : Pillar sprite
	8 : Soldier sprite
	9 : Commandant sprite
*/
typedef struct s_text
{
	void	*text;
	int		width_img;
	int		height_img;
	char	*text_adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_text;

typedef struct s_sprite
{
	t_vector2_f	pos;
	t_text		*text;
	int			nb_text;

	float		timer;	// Used to change sprites according to anim_speed
	float		anim_speed;
	int			curr_text;

	// Might add some life, movements, etc
}	t_sprite;

typedef struct s_data {
	// Mlx datas
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	int			win_height;
	int			win_width;

	// Tab and cells
	int			**tab;
	int			tab_width; // Nb cells (width)
	int			tab_height; // Nb cells (height)
	int			cell_size;
	int			height_size; // tab_height * cell_size
	int			width_size; // tab_width * cell_size

	// Mouse
	t_vector2_d	mouse_pos;
	t_vector2_d	mouse_move; // Used to rotate player with mouse
	int			mouse_pressed; // Boolean
	int			mouse_button;

	// Keyboard
	// !! Need to change keyboard array system for Linux OS !!
	int			keyboard[200]; // Each cell correspond to a key state
	int			prev_keyboard[200]; // Keep in memory the previous states of keyboard

	// Player
	t_player	player;

	// Vision properties
	int			view_dst;
	int			fov; // Degree
	int			rays_nb;
	t_ray		*rays;

	// Fps
	struct		timespec curr_time;
	struct		timespec prev_time;
	double		delta_time;

	// Textures & colors
	char		*texture_name[6];
	t_text		*textures;
	int			floor_color;
	int			ceiling_color;

	// Sprites	
	int			nb_sprites;
	t_sprite	*sprites;
	int			*sprite_order;
	double		*sprite_dst;

	int			show_map; // Boolean

}	t_data;

int			update(t_data *data);

// Mlx utils
int			ft_mlx_init(t_data *data);
void		ft_mlx_hooks_and_loop(t_data *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		clear_window(t_data *data);
void		clamp_mouse_in_window(t_data *data);

// Mlx hooks
int			mouse_hook(int keycode, int x, int y, t_data *data);
int			mouse_release(int keycode, int x, int y, t_data *data);
int			update_mouse_pos(int x, int y, t_data *data);
int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);

// Drawing functions
void		bresenham(t_data *data, t_vector2_d p1, t_vector2_d p2, int color);
void		draw_rect_filled(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right);
void		draw_rect_filled_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color);
void		draw_circle(t_data *data, t_vector2_d center);
void		draw_circle_color(t_data *data, t_vector2_d center, int color);
void		draw_circle_empty(t_data *data, t_vector2_d center, int radius, int thickness);
void		draw_circle_color_radius(t_data *data, t_vector2_d center, int color, int radius);
void		draw_triangle_color(t_data *data, t_vector2_d points[3], int color);

// Grid functions
void		print_grid(t_data *data);
void		set_grid_cell(t_data *data, int x, int y);
int			is_in_map(t_data *data, t_vector2_d pos);
int			is_colliding_cell(t_data *data, float x, float y, int plain_cell);

// Utils
void		print_fps(t_data *data);
int			ft_init_vision(t_data *data);
void		floor_and_ceiling(t_data *data);
int			print_error(char *str);
void		print_minimap(t_data *data);
void		player_input(t_data *data);
int			free_all(t_data *data);

// Rays
void		create_rays(t_data *data);
t_vector2_f	dda(t_data *data, t_ray *ray);
void		calculate_collisions(t_data *data);
void		rays_render(t_data *data);

// Parsing
int			parsing(t_data *data, int argc, char *argv[]);
int			get_description(t_data *data, int fd);
int			get_map(t_data *data, int fd, t_list **map);
int			convert_map_to_int(t_data *data, t_list **map);
int			check_map_format(t_data *data, t_list **errors);
int			check_player_pos(t_data *data);
void		print_map(t_data *data, t_list *errors);

// Sprites & Textures
int			init_text(t_data *data);
int			init_floor_and_ceiling(t_data *data);
int			get_text_pix(t_text *text, int x, int y);
int			sprites_init(t_data *data);
void		render_sprite(t_data *data);
int			count_sprites(t_data *data);

#endif