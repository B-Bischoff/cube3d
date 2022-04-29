#include "cube3d.h"

double	get_perp_wall_dst(t_ray ray, double dir_angle)
{
	double		length;
	// t_vector2_d	perp_coord;

	// dprintf(1, "%lf %lf\n", radian_to_degree(dir_angle), );
	length = cos(ray.angle - dir_angle) * ray.length; 	
	// perp_coord = create_vect_d_from_origin(ray.hit_point, PI - dir_angle, length);
	// bresenham(data, ray.hit_point, perp_coord, RED);
	return (length);
}