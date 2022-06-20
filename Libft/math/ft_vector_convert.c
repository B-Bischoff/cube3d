#include "../libft.h"

t_vector2_f	vector_d_to_f(t_vector2_d vector_d)
{
	t_vector2_f	vector_f;

	vector_f.x = vector_d.x;
	vector_f.y = vector_d.y;
	return (vector_f);
}

t_vector2_d	vector_f_to_d(t_vector2_f vector_f)
{
	t_vector2_d	vector_d;

	vector_d.x = vector_f.x;
	vector_d.y = vector_f.y;
	return (vector_d);
}
