#include "../libft.h"

float	get_vector_d_length(t_vector2_d start, t_vector2_d end)
{
	int	dx;
	int	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

double	get_vector_f_length(t_vector2_f start, t_vector2_f end)
{
	double	dx;
	double	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return (sqrt(dx * dx + dy * dy));
}

float	get_vector_d_length_squared(t_vector2_d start, t_vector2_d end)
{
	int	dx;
	int	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return ((float)(dx * dx) + (float)(dy * dy));
}

float	get_vector_f_length_squared(t_vector2_f start, t_vector2_f end)
{
	float	dx;
	float	dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	return ((float)(dx * dx) + (float)(dy * dy));
}
