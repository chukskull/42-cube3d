#include "cub3d.h"


void	draw_p(t_data *data, int color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < 3)
    {
        j = 0;
        while(j < 3)
        {
            fill_pixel(data, j + ((SQUARE/18) * data->player->x), i +((SQUARE / 18) * data->player->y), color);
            j++;
        }
        i++;
    }
}


void	draw_map_p(t_data *data, int init)
{
	int	r;
	int	c;

	r = 0;
	c = 0;

	int map[18][18] =
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1},
			{1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1},
			{1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		};
	while(r < 18)
		{
			c = 0;
			while(c < 18)
			{
				if (map[r][c] == 1)
					draw_square(data, c, r, 0xB3ff0000);
				else if (map[r][c] == 0 || map[r][c] == 2)
					draw_square(data, c, r, 0x00e5dad5);
				c++;
			}
			r++;
		}
		r = 0;
		while(r < 18)
		{
			c = 0;
			while(c < 18)
			{
				if (map[r][c] == 2 && init ==1)
					draw_player(data, c,r, 0x00ff0000);
				else if (init == 0)
					draw_p(data, 0x00ff0000);
				c++;
			}
			r++;
		}
		double an = data->player->an - (60/2 * DEGREE);
		float x;
		x = 0;
		while (x < 60)
		{
			float ra = x * DEGREE;
			draw_line(data, (SQUARE/18) * data->player->x + 1, 
			(SQUARE/18) * data->player->y + 1,
			((SQUARE/18) * data->player->x + 1+ cos(an + ra) * 500),
			((SQUARE/18) * data->player->y + 1 - sin(an + ra) * 500));
			x += 0.5;
		}
		//draw_rays(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
