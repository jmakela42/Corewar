/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 16:28:30 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_st(t_args *args, t_car *car, t_vm *core)
{
	int	val[2];
	int	temp;

	val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_IND)
	{
		val[1] = args->arg[1];
		write_bytes(car->pc + val[1] % IDX_MOD, val[0], car, core);
	}
	else if (args->arg_types[1] == T_REG)
	{
		val[1] = args->arg[1];
		car->reg[val[1] - 1] = val[0];
	}
	vm_log(F_LOG, "r%d %d", args->arg[0], val[1]);
}

void		op_st(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_st(car->args, car, core);
	}
	get_step(car, car->args);
}
