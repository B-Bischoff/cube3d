#include "cube3d.h"

int	get_text_pix(t_text *text, int x, int y)
{
	int	color;

	if (text == NULL)
	{
		dprintf(1, "Invalid texture pointer\n");
		return (0);
	}
	if (x < 0 || x > 64 || y < 0 || y > 64) // Remove hard coded size
	{
		dprintf(1, "Invalid texture coordinate\n");
		return (0);
	}
	color = (*(int *)(text->text_adr + (y * text->bit / 8) + (x * text->size_line)));
	return (color);
}
