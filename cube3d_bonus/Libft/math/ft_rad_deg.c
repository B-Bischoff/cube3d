#include "../libft.h"

double	radian_to_degree(double radian)
{
	return (180.0f / PI * radian);
}

double	degree_to_radian(double degree)
{
	return (degree / (180.0f / PI));
}
