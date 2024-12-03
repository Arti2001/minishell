/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:49:20 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 15:28:43 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int in, int out)
{
	if (close(in) == -1)
	{
		perror("Failed to close in stdin");
		exit(EXIT_FAILURE);
	}
	if (close(out) == -1)
	{
		perror("Failed to close in stdout");
		exit(EXIT_FAILURE);
	}
}

void	restore_fd(int	orig_in, int orig_out)
{
	if (dup2(orig_in, STDIN_FILENO) == -1)
	{
		perror("error: can not restore the original fd in");
		return ;
	}
	if (close(orig_in) == -1)
	{
		perror("error: closing  fd in");
		return ;
	}
	if (dup2(orig_out, STDOUT_FILENO) == -1)
	{
		perror("error: can not restore the original fd out");
		return ;
	}
	if (close(orig_out) == -1)
	{
		perror("error: closing  fd out");
		return ;
	}
}

int	redirect_in(t_redirect redirect)
{
	int	file_fd;

	if (redirect.type == HEREDOC_RE)
		file_fd = open("/tmp/herdoc.txt", O_RDONLY);
	else
		file_fd = open(redirect.filename, O_RDONLY);
	if (file_fd == -1)
	{
		perror(redirect.filename);
		exit(EXIT_FAILURE);
	}
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		perror("can't redirect stdin");
		exit(EXIT_FAILURE);
	}
	if (close(file_fd) == -1)
	{
		perror("can't close infile");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	redirect_out(t_redirect redirect)
{
	int	file_fd;

	if (redirect.type == OUT)
		file_fd = open(redirect.filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		file_fd = open(redirect.filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (file_fd == -1)
	{
		perror("can't open an outfile");
		exit(EXIT_FAILURE);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		perror("cant't redirect stdout");
		exit(EXIT_FAILURE);
	}
	if (close(file_fd) == -1)
	{
		perror("can't close outfile");
		exit(EXIT_FAILURE);
	}
}

int	redirect_check(t_pars *pars)
{
	int		i;

	i = 0;
	while (pars->redir[i].filename)
	{
		if (pars->redir[i].type == HEREDOC_RE || pars->redir[i].type == IN)
		{
			redirect_in(pars->redir[i]);
		}
		else if (pars->redir[i].type == OUT || pars->redir[i].type == OUT_A)
		{
			redirect_out(pars->redir[i]);
		}
		i++;
	}
	return (0);
}
