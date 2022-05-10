#include "cube3d.h"

void	create_rays(t_data *data, t_vector2_f direction)
{
	t_vector2_f perpendicular[2];
	double angle;

	angle = get_angle(vector_f_to_d(data->player.pos), data->plane);

	direction = vector_d_to_f(data->plane);


	// Calculating perpendicular line size
	int size = tan(degree_to_radian(data->fov / 2)) * data->view_dst;

	t_vector2_f origin_resized = create_vect_f_from_origin(direction, -angle, size);
	// draw_circle(data, origin_resized);

	perpendicular[0].x = origin_resized.x - direction.x;
	perpendicular[0].y = origin_resized.y - direction.y;
	perpendicular[1].x = origin_resized.x - direction.x;
	perpendicular[1].y = origin_resized.y - direction.y;


	perpendicular[0] = rotate_vector_f(perpendicular[0], 3.14f / 2.0f);
	perpendicular[0].x += direction.x;
	perpendicular[0].y += direction.y;
	perpendicular[1] = rotate_vector_f(perpendicular[1], -3.14 / 2.0f);
	perpendicular[1].x += direction.x;
	perpendicular[1].y += direction.y;

	// draw_circle_color(data, vector_f_to_d(perpendicular[1]), RED);
	// draw_circle_color(data, vector_f_to_d(perpendicular[0]), RED);

	// bresenham(data, perpendicular[0], perpendicular[1], PURPLE);

	// Creating nb rays from perpendicular line to origin
	double incr = 1.0f / (data->rays_nb - 1.0f);
	for (int i = 0; i < data->rays_nb; i++)
	{
		t_vector2_f vector; 
		vector = vector_f_lerp(perpendicular[0], perpendicular[1], incr * i);
		// draw_circle_color(data, vector_f_to_d(vector), YELLOW);
		// bresenham(data, vector, vector_f_to_d(data->player.pos), WHITE);
		data->rays[data->rays_nb - 1 - i].hit_point = vector;
	}
}
