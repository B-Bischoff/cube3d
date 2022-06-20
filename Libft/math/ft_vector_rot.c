#include "../libft.h"

t_vector2_d	rotate_vector_d(t_vector2_d vector, double radian)
{
	t_vector2_d	new_vect;

	new_vect.x = vector.x * cos(radian) - vector.y * sin(radian);
	new_vect.y = vector.x * sin(radian) + vector.y * cos(radian);
	return (new_vect);
}
t_vector2_f	rotate_vector_f(t_vector2_f vector, double radian)
{
	t_vector2_f	new_vect;

	new_vect.x = vector.x * cos(radian) - vector.y * sin(radian);
	new_vect.y = vector.x * sin(radian) + vector.y * cos(radian);
	return (new_vect);
}

