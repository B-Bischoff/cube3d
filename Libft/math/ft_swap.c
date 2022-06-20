#include "../libft.h"

void	ft_swap_d(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_f(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_v2_d(t_vector2_d *a, t_vector2_d *b)
{
	t_vector2_d	temp;

	set_vector_d(&temp, a->x, a->y);
	set_vector_d(a, b->x, b->y);
	set_vector_d(b, temp.x, temp.y);
}

void	ft_swap_v2_f(t_vector2_f *a, t_vector2_f *b)
{
	t_vector2_f	temp;

	set_vector_f(&temp, a->x, a->y);
	set_vector_f(a, b->x, b->y);
	set_vector_f(b, temp.x, temp.y);
}