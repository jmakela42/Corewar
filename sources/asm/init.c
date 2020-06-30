/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:57:41 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/25 15:17:08 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm	*intialize_asm(char *filename)
{
	t_asm	*core;
	char	*target_file;

	core = (t_asm *)ft_memalloc(sizeof(t_asm));
	if (!core)
		ft_error_exit("Malloc at initialize_asm", NULL, NULL);
	target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!target_file)
		ft_error_exit("Given file is of incorrect type", (void *)core, clear_t_asm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Failed to open given source file", (void *)core, clear_t_asm);
	core->core_fd = open(target_file, O_RDWR | O_CREAT, 0600);
	if (core->core_fd < 0)
		ft_error_exit("Failed to open given target file", (void *)core, clear_t_asm);
	core->byte_size = 0;
	return (core);
}

/*
** Function to add a node to the linked list struct.
** Allocates memory and initializes all values to null.
*/

t_operation	*newnode(void)
{
	t_operation *new;

	new = (t_operation*)ft_memalloc(sizeof(t_operation));
	if (!new)
		ft_error_exit("Malloc at newnode", NULL, NULL);
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
** Goes through the list and calls for newnode to allocate and initialize the new node.
*/

int	list_append(t_operation **head)
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

int ft_chrpos(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i = i + 1;
	}
	return (-1);
}

int				is_hex(char *argum)
{
	int i;
	char hexmask[] = "0123456789abcdefABCDEF";

	i = 3;
	if (argum[1] == '0' && (argum[2] == 'x' || argum[2] == 'X'))
	{
		while (argum[i] != '\0')
		{
			if (ft_chrpos(hexmask, argum[i]) < 0)
				return (0);
			i = i + 1;
		}
		return (1);
	}
	return (0);
}

unsigned long			ft_pow(int number, int power)
{
	unsigned long total;

	total = number;
	if (!power)
		return (1);
	else if (power == 1)
		return (number);
	else
	{
		while (power > 1)
		{
			total = total * number;
			power = power - 1;
		}
	}
	return (total);
}

char			*x_to_deci(char *argum)
{
	unsigned long hex;
	int len;
	int val;
	int i;

	hex = 0;
	len = ft_strlen(argum);
	len = len - 4;
	val = 0;
	i = 3;
	while (argum[i] != '\0')
	{
		if (argum[i] >= '0' && argum[i] <= '9')
			val = argum[i] - 48;
		else if (argum[i] >= 'a' && argum[i] <= 'f')
			val = argum[i] - 97 + 10;
		else if (argum[i] >= 'A' && argum[i] <= 'F')
			val = argum[i] - 65 + 10;
		hex = hex + (val * ft_pow(16, len));
		len = len - 1;
		i = i + 1;
	}
	return(ft_ultoa(hex));
}
