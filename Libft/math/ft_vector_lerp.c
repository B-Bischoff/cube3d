#include "../libft.h"

t_vector2_d	vector_d_lerp(t_vector2_d start, t_vector2_d end, float timestamp)
{
	t_vector2_d	vector;
	int			dx;
	int			dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	vector.x = start.x + dx * timestamp;
	vector.y = start.y + dy * timestamp;
	return (vector);
}

t_vector2_f	vector_f_lerp(t_vector2_f start, t_vector2_f end, float timestamp)
{
	t_vector2_f	vector;
	float		dx;
	float		dy;

	dx = end.x - start.x;
	dy = end.y - start.y;
	vector.x = start.x + dx * timestamp;
	vector.y = start.y + dy * timestamp;
	return (vector);
}

float	vector_d_inv_lerp(t_vector2_d start, t_vector2_d end, t_vector2_d curr)
{
	int	max_length;
	int	curr_length;

	max_length = get_vector_d_length(start, end);
	curr_length = get_vector_d_length(start, curr);
	return (ft_inv_lerp_d(0, max_length, curr_length));
}

float	vector_d_inv_lerp_length(t_vector2_d start, int max_length, \
			t_vector2_d curr)
{
	int	curr_length;

	max_length *= max_length;
	curr_length = get_vector_d_length_squared(start, curr);
	return (ft_inv_lerp_d(0, max_length, curr_length));
}
