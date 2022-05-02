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
	
	// Might add texture, color, etc

}	t_ray;

typedef	struct s_player
{
	t_vector2_f	pos;
	t_vector2_f	dir;
	double		angle; // Looking direction
}	t_player;

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
	int			tab_width;
	int			tab_height;
	int			cell_size;
	t_list		*map;

	// Mouse
	t_vector2_d	mouse_pos;
	int			mouse_pressed; // Boolean
	int			mouse_button;

	// Player
	t_player	player;

	// Vision properties
	t_vector2_d	plane;
	int			view_dst;
	int			fov; // Degree
	int			rays_nb;
	t_ray		*rays;

	// Fps
	struct		timespec curr_time;
	struct		timespec prev_time;

	// Textures
	char		*texture_name[6];

}	t_data;

int			update(t_data *data);

// Mlx utils
int			ft_mlx_init(t_data *data);
void		ft_mlx_hooks_and_loop(t_data *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		clear_window(t_data *img);

// Mlx hooks
int			mouse_hook(int keycode, int x, int y, t_data *data);
int			mouse_release(int keycode, int x, int y, t_data *data);
int			update_mouse_pos(int x, int y, t_data *data);
int			key_hook(int keycode, t_data *data);

// Drawing functions
void		bresenham(t_data *data, t_vector2_d p1, t_vector2_d p2, int color);
void		draw_rect_filled(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right);
void		draw_rect_filled_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color);
void		draw_circle(t_data *data, t_vector2_d center);
void		draw_circle_color(t_data *data, t_vector2_d center, int color);
void		draw_triangle_color(t_data *data, t_vector2_d points[3], int color);

// Grid functions
int			init_grid(t_data *data);
void		print_grid(t_data *data);
void		set_grid_cell(t_data *data, int x, int y);
int			is_in_map(t_data *data, t_vector2_d pos);

// Utils
void		print_fps(t_data *data);
int			ft_init_vision(t_data *data);
void		floor_and_ceiling(t_data *data);
int			print_error(char *str);
void		print_minimap(t_data *data);

// Rays
void		create_rays(t_data *data, t_vector2_f direction);
t_vector2_f	dda(t_data *data, t_ray *ray, int ray_index);
void		calculate_collisions(t_data *data);
void		rays_render(t_data *data);
double		get_perp_wall_dst(t_ray ray, double dir_angle);

// Parsing
int			parsing(t_data *data, int argc, char *argv[]);

#endif