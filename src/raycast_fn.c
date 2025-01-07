/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgimon-c <mgimon-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:39:59 by apaterno          #+#    #+#             */
/*   Updated: 2025/01/07 20:08:17 by mgimon-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int check_wall(t_game *game, float x , float y)
{
		t_map *mapa;
		int x1 = x / 100;
		int y1 = y / 100;
		mapa = game->map;
		if(mapa->map[y1][x1] == '1')
			return (0);
		return (1);
}

static int set_increment(int v0, int v1)
{
	if (v0 < v1)
		return(1);
	else
		return(-1);
}

void calc_delta(t_player *player, int *x1, int *y1)
{
	*x1 = round(player->pos_x + 30 *cos(to_radians(player->direction)));
	*y1 = round(player->pos_y + 30 *sin(to_radians(player->direction)));
	player->dx = *x1 - player->pos_x;
	player->dy = *y1 - player->pos_y;		
}
// void draw_ray(t_game *game, t_player *player)
// {
// 	int 	x;
// 	int 	y;
// 	int 	x1;
// 	int 	y1;
// 	float 	m;

// 	x = player->pos_x;
// 	y = player->pos_y;
// 	calc_delta(player,&x1,&y1);
// 	if (abs(player->dx) >=abs(player->dy))
// 	{
// 		m = (float) player->dy / player->dx;
// 		while(x != x1)
// 		{
// 			img_pixel_put(game->img, x,y,GREEN);
// 			x += set_increment(player->pos_x, x1);
// 			y = round(m*(x - player->pos_x) + player->pos_y);
// 		}
// 	}
// 	else
// 	{
// 		m = (float) player->dx / player->dy;
// 		while(y != y1)
// 		{
// 			img_pixel_put(game->img, x,y,GREEN);
// 			y += set_increment(player->pos_y,y1);
// 			x = round(m*(y - player->pos_y) + player->pos_x);
// 		}
// 	}
// }

/*void draw_ray(t_game *game, t_player *player)
{
	int i;
	float y;
	float x;
	int x_i;
	int y_i;
	
	i = 0;
	x = (float)player->pos_x;
	y = (float)player->pos_y;
	while(check_wall(game, x, y))
	{
		x += player->dx;
		y -= player->dy;
		x_i = round(x);
		y_i = round(y);
		img_pixel_put(game->img, x_i, y_i,GREEN);
	}
}*/

void draw_ray(t_game *game, t_player *player)
{
    float	y;
	float	x;
    int		x_i;
	int		y_i;
    float	angle_step;
    float	angle;
    float	rotated_dx; // Adjusts deltas for rays
	float	rotated_dy; // Adjusts deltas for rays

    angle = -PI / 4;
	angle_step = 0.0174533 / 10 ; // 0.1 degree in radians
    while (angle <= PI / 4)
    {
        rotated_dx = player->dx * cos(angle) - player->dy * sin(angle);
        rotated_dy = player->dx * sin(angle) + player->dy * cos(angle);
        x = (float)player->pos_x;
        y = (float)player->pos_y;
        while (check_wall(game, x, y))
        {
            x += rotated_dx;
            y -= rotated_dy;
            x_i = round(x);
            y_i = round(y);
            img_pixel_put(game->img, x_i, y_i, GREEN);
        }
		angle += angle_step;
    }
}
