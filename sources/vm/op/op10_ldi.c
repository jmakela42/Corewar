/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/23 12:38:43 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_ldi(t_args *args, uint8_t *code, t_car *car)
{
	int	val[3];

	if (args->arg_types[0] == T_IND)
		val[0] = get_tind(args->arg[0], code);
	else if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_REG)
		val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	val[2] = args->arg[2];
	car->reg[val[2] - 1] = decode(code + (val[0] + val[1]) % IDX_MOD, REGSIZE);
}

void		op_ldi(t_vm *core, t_car *car)
{
	uint8_t	*code;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("ldi", car->args);
	code = core->arena + car->pc;
	if (read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		read_args(code + OP_BYTE + ARGTYPE_BYTE, car->args);
		do_ldi(car->args, code, car);
	}
	get_jump(car, car->args);
	printf("ldi\n");
}
