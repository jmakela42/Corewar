/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:16 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 15:16:39 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vs	*init_visual_settings(char *title)
{
	t_vs	*settings;

	settings = (t_vs *)ft_memalloc(sizeof(t_vs));
	if (!settings)
		ft_error_exit("Malloc at init_visual_settings", NULL, NULL);
	settings->height = 66;
	settings->width = 64 * 2 + 2;
	initscr();
	cbreak();
	mvprintw(0,20, title);
	settings->win = newwin(settings->height, settings->width, 1, 0);
	refresh();
	box(settings->win, 0, 0);
	return (settings);
}

void	show_arena(t_vm *core)
{
	int	y;
	int	x;
	size_t	i;

	core->vfx = init_visual_settings(core->champ->header->prog_name);
	vfx_colors();
	y = 1;
	x = 1;
	i = 0;
	while (i < MEM_SIZE)
	{
		wattron(core->vfx->win, COLOR_PAIR((int)(core->byte_owner[i])));
		mvwprintw(core->vfx->win, y, x, "%02x", core->arena[i]);
		wattroff(core->vfx->win, COLOR_PAIR((int)(core->byte_owner[i])));
		wrefresh(core->vfx->win);
		i++;
		x += 2;
		if (x >= core->vfx->width - 1)
		{
			x = 1;
			y++;
		}
	}
	getch();
	endwin();
}