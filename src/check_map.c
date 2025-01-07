/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgimon-c <mgimon-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:10:59 by mgimon-c          #+#    #+#             */
/*   Updated: 2024/12/11 05:02:00 by mgimon-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int is_it_closed(char **matrix, int full_height)
{
    int i;
    int j;

    i = 0;
    while (matrix[i])
    {
        if (check_line_ends(matrix[i]) != 0)
            return (1);
        j = 0;
        while (matrix[i][j])
        {
            if (i == 0 || i == (full_height - 1))
            {
                if (matrix[i][j] != '1' && matrix[i][j] != ' ')
                    return (1);
            }
            j++;
        }
        i++;
    }
    if (validate_holes(matrix))
        return (0);
    printline_fd(2, "hhhh\n");
    return (1);
}

int does_player_exist(char **matrix)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (matrix[i] != NULL)
    {
        j = 0;
        while (matrix[i][j] != '\0')
        {
            if (matrix[i][j] == 'N' || matrix[i][j] == 'E' || matrix[i][j] == 'W' || matrix[i][j] == 'S')
            {
                player_count++;
                if (player_count > 1)
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int is_player_free(char **matrix)
{
    int i;
    int j;

    i = 0;
    while (matrix[i] != NULL)
    {
        j = 0;
        while (matrix[i][j] != '\0')
        {
            if (matrix[i][j] == 'N' || matrix[i][j] == 'E' || matrix[i][j] == 'W' || matrix[i][j] == 'S')
            {
                if ((i > 0 && matrix[i - 1][j] == '0') || 
                    (matrix[i + 1] != NULL && matrix[i + 1][j] == '0') || 
                    (j > 0 && matrix[i][j - 1] == '0') || 
                    (matrix[i][j + 1] == '0'))
                    return 0;
                else
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 1;
}

int check_map(char **matrix)
{
    int full_height;
    int closed;
    int player;
    int player_valid;

    if (!matrix || !matrix[0])
        return (1);
    if (!even_map(matrix))
    {
        printline_fd(2, "Error: the map is uneven. Fill with spaces to make it even\n");
        return (1);
    }
    full_height = get_full_height(matrix);
    closed = is_it_closed(matrix, full_height);
    player = does_player_exist(matrix);
    player_valid = is_player_free(matrix);
    if (closed == 0 && player == 0 && player_valid == 0)
        return (0);
    return (1);
}