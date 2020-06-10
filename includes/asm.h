/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/10 12:11:31 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "libft.h"
# include "ft_error.h"

# define SRC_TYPE ".s"
# define TRGT_TYPE ".cor"

typedef struct	s_asm
{
	int		source_fd;
	int		core_fd;
	char	*champ_name;
	char	*champ_comment;
	int		flag;
}				t_asm;


/*
** ASM struct utilities
*/

void	clear_t_asm(void *object);
char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type);
t_asm	*intialize_asm(char *filename);
void	print_asmcore(t_asm *core);
int		analysis(t_asm *core, char *line);

/*
** ASM File reading
*/
void	read_file(t_asm *core, int source_fd);

#endif