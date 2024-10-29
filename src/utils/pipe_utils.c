/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:47:42 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/29 15:08:51 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int		child_process(int pipes_fd, )
{
	
}
int		create_multiple_processes(t_pars *pars)
{
	int		fd[2];
	pid_t	pid;
	
	while (pars->next_process != NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("can't create a pipe");
			return (0);
		}
		
		
		pipecount--;
	}
	
}