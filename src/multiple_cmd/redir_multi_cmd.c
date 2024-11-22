/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_multi_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:57:42 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/18 21:06:26 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redir_first_proc(int fd_write_end)
{
	if (dup2(fd_write_end, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect the write end");
		return (0);
	}
	if (close(fd_write_end) == -1)
	{
		perror("Failed to close the write end");
		return (0);
	}
	return (1);
}

int redir_mid_proc(t_pars *pars, int fd_write_end)
{
	if (dup2(pars->fd_in, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect the read end");
		return (0);
	}
	if (close(pars->fd_in) == -1)
	{
		perror("Failed to close the read end");
		return (0);
	}
	if (dup2(fd_write_end, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect the write end");
		return (0);
	}
	if (close(fd_write_end) == -1)
	{
		perror("Failed to close the write end");
		return (0);
	}
	return (1);
}
int redir_last_proc(t_pars	*pars)
{
	if (dup2(pars->fd_in, STDIN_FILENO) == -1)
		{
			perror("Failed to redirect the read end");
			return (0);
		}
		if (close(pars->fd_in) == -1)
		{
			perror("Failed to close the read end");
			return (0);

		}
	return (1);
}
int	check_redirection_type(int	process_num, t_pars *pars, int fd_write_end)
{
	if (process_num == 0 && pars->next_process != NULL)
	{
		return(redir_first_proc(fd_write_end));
	}
	else if (process_num != 0 && pars->next_process != NULL)
	{
		return(redir_mid_proc(pars, fd_write_end));
	}
	else if (process_num != 0 && pars->next_process == NULL)
	{
		return(redir_last_proc(pars));
	}
	return (0);
}

