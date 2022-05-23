#include "cube3d.h"

void	create_rays(t_data *data)
{
	t_vector2_f perpendicular[2];
	double angle;

	angle = get_angle(vector_f_to_d(data->player.pos), data->plane);

	// Calculating perpendicular line size
	int size = tan(degree_to_radian(data->fov / 2)) * data->view_dst;

	t_vector2_f origin_resized = create_vect_f_from_origin(vector_d_to_f(data->plane), angle, size);
	draw_circle_color(data, vector_f_to_d(origin_resized), YELLOW);
	perpendicular[0] = create_vect_f_from_origin(vector_d_to_f(data->plane), angle - PI_2, size);
	perpendicular[1] = create_vect_f_from_origin(vector_d_to_f(data->plane), angle + PI_2, size);

	// draw_circle_color(data, vector_f_to_d(perpendicular[1]), RED);
	// draw_circle_color(data, vector_f_to_d(perpendicular[0]), RED);

	// bresenham(data, vector_f_to_d(perpendicular[0]), vector_f_to_d(perpendicular[1]), PURPLE);

	// Creating nb rays from perpendicular line to origin
	double incr = 1.0f / (data->rays_nb - 1.0f);
	for (int i = 0; i < data->rays_nb; i++)
	{
		t_vector2_f vector; 
		vector = vector_f_lerp(perpendicular[0], perpendicular[1], incr * i);
		data->rays[data->rays_nb - 1 - i].angle = get_angle_f(data->player.pos, vector);
		// draw_circle_color(data, vector_f_to_d(test), BLUE);
		// bresenham(data, vector_f_to_d(vector), vector_f_to_d(data->player.pos), PURPLE);
		data->rays[data->rays_nb - 1 - i].hit_point = vector;
	}
}
