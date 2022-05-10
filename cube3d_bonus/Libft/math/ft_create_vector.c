#include "../libft.h"

t_vector2_d	create_vector_d(int x, int y)
{
	t_vector2_d	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vector2_f	create_vector_f(float x, float y)
{
	t_vector2_f	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vector2_d	create_vect_d_from_origin(t_vector2_d origin, double radian, \
				double length)
{
	t_vector2_d	vector;

	vector.x = cos(radian) * length + origin.x;
	vector.y = sin(radian) * length + origin.y;
	return (vector);
}

t_vector2_f	create_vect_f_from_origin(t_vector2_f origin, double radian, \
				double length)
{
	t_vector2_f	vector;

	vector.x = cos(radian) * length + origin.x;
	vector.y = sin(radian) * length + origin.y;
	return (vector);
}
