#include "cube3d.h"

int	get_text_pix(t_text *text, int x, int y)
{
	int	color;

	color = (*(int *)(text->text_adr + (y * text->bit / 8) + (x * text->size_line)));
	return (color);
}
