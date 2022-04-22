#include "../libft.h"

double	get_angle(t_vector2_d start, t_vector2_d end)
{
	double	dx;
	double	dy;

	dx = (double)(end.x - start.x);
	dy = (double)(end.y - start.y);
	if (dx >= 0 && dy < 0)
		return (atan(-dy / dx));
	else if (dx < 0 && dy < 0)
		return (atan(dx / dy) + 3.14f / 2.0f);
	else if (dx < 0 && dy > 0)
		return (atan(-dy / dx) + 3.14f);
	else
		return (atan(dx / dy) + 3.14 + 1.57f);
}
