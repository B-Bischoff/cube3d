#include "cube3d.h"

int	get_text_pix(t_text *text, int x, int y)
{
	int	color;
	
	if (text == NULL)
	{
		dprintf(1, "Invalid texture pointer\n");
		return (0);
	}
	if (x < 0 || x >= text->width_img || y < 0 || y >= text->height_img)
	{
		// dprintf(1, "Invalid texture coordinate\n");
		return (0);
	}
	color = (*(int *)(text->text_adr + (x * text->bits_per_pixel / 8) + (y * text->line_length)));

	return (color);
}