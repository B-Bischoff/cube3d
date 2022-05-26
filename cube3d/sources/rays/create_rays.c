#include "cube3d.h"

void	create_rays(t_data *data)
{
	t_vector2_f opposite_vect[2];
	double angle;

	angle = get_angle(vector_f_to_d(data->player.pos), data->plane);

	// Calculating perpendicular line size
	int opposite_length = tan(degree_to_radian(data->fov / 2)) * data->view_dst;

	// draw_circle(data, origin_resized);

	opposite_vect[0] = create_vect_f_from_origin(vector_d_to_f(data->plane), angle + PI_2, opposite_length);
	opposite_vect[1] = create_vect_f_from_origin(vector_d_to_f(data->plane), angle - PI_2, opposite_length);


	// draw_circle_color(data, vector_f_to_d(perpendicular[1]), RED);
	// draw_circle_color(data, vector_f_to_d(perpendicular[0]), RED);

	// bresenham(data, perpendicular[0], perpendicular[1], PURPLE);

	// Creating nb rays from perpendicular line to origin
	double incr = 1.0f / (data->rays_nb - 1.0f);
	for (int i = 0; i < data->rays_nb; i++)
	{
		t_vector2_f vector; 
		vector = vector_f_lerp(opposite_vect[0], opposite_vect[1], incr * i);
		// draw_circle_color(data, vector_f_to_d(vector), YELLOW);
		// bresenham(data, vector, vector_f_to_d(data->player.pos), WHITE);
		data->rays[i].hit_point = vector;
	}
}
