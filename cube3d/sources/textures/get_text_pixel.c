#include "cube3d.h"

int	get_text_pix(t_text *text, int x, int y)
{
	int	color;
	
	if (text == NULL)
	{
		dprintf(1, "Invalid texture pointer\n");
		return (0);
	}
	if (x < 0 || x > text->lar_img || y < 0 || y > text->long_img)
	{
		dprintf(1, "Invalid texture coordinate\n");
		return (0);
	}
	color = (*(int *)(text->text_adr + (x * text->bit / 8) + (y * text->size_line)));

	return (color);
}
