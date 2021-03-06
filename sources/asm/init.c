/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:57:41 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/13 13:38:23 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm			*intialize_asm(char *filename)
{
	t_asm	*core;

	core = (t_asm *)ft_memalloc(sizeof(t_asm));
	if (!core)
		ft_error("Malloc at initialize_asm");
	core->target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!core->target_file)
		ft_error_exit("Incorrect file type", (void *)core, clear_t_asm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Open Error on source file", (void *)core, clear_t_asm);
	core->byte_size = 0;
	core->line_cnt = 0;
	core->champ_name = NULL;
	core->champ_comment = NULL;
	return (core);
}

/*
** Function to add a node to the linked list struct.
** Allocates memory and initializes all values to null.
*/

t_operation		*newnode(void)
{
	t_operation *new;

	new = (t_operation*)ft_memalloc(sizeof(t_operation));
	if (!new)
		ft_error("Malloc at newnode");
	new->label = NULL;
	new->op_name = NULL;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	new->argtypes[0] = 0;
	new->argtypes[1] = 0;
	new->argtypes[2] = 0;
	new->next = NULL;
	new->op_size = 0;
	new->t_dir_size = 0;
	new->op_code = 0;
	new->position = 0;
	new->label_pos[0] = 0;
	new->label_pos[1] = 0;
	new->label_pos[2] = 0;
	return (new);
}

/*
** Function to append a new link to the end of the list
** Goes through the list and calls for newnode to allocate
** and initialize the new node.
*/

int				list_append(t_operation **head)
{
	t_operation *last;

	last = *head;
	if (*head == NULL)
	{
		*head = newnode();
		return (1);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode();
	return (1);
}
