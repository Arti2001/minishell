/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:49:20 by amysiv            #+#    #+#             */
/*   Updated: 2024/10/24 16:04:18 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_fd(t_pars *pars)
{
	if (dup2(pars->orig_in, STDIN_FILENO) == -1)
	{
		perror("Failed to restore stdin");
		return ;
	}
	if (close(pars->orig_in) == -1)
	{
		perror("Failed to close stdin");
		return ;
	}
	if (dup2(pars->orig_out, STDOUT_FILENO) == -1)
	{
		perror("Failed to restore the stdout");
		return ;
	}
	if (close(pars->orig_out) == -1)
	{
		perror("Failed to close stdout");
		return ;
	}
}
void	redirect_in(t_redirect redirect)
{
	int	file_fd;

	file_fd = open(redirect.filename, O_RDONLY);
	if (file_fd == -1)
	{
		perror("can't open an infile");
		exit(EXIT_FAILURE);
	}
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
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
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

void	redirect_heredoc(t_redirect redir)
{
	int		fd[2];
	char	*eof;
	char	*line;
	
	eof = redir.filename;
	line = NULL;
	if (pipe(fd) == -1)
	{
		perror("pipe in herdoc error");
		return ;
	}
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf("Minishell: warning: here-document delimited by signal (wanted `%s')\n", eof);
			break;
		}
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	if (ft_strncmp(redir.filename, "c", 1) == 0)
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("redirect in heredoc error!");
			return ;
		}
	close(fd[0]);
}

void	redirect_check(t_pars *pars)
{
	int		i;
	
	i = 0;
	while (pars->redir[i].filename != NULL)
	{
		if (pars->redir[i].type == HEREDOC)
		{
			redirect_heredoc(pars->redir[i]);
		}
		else if(pars->redir[i].type == OUT || pars->redir[i].type == OUT_A)
		{
			redirect_out(pars->redir[i]);
		}
		else if (pars->redir[i].type == IN)
		{
			redirect_in(pars->redir[i]);
		}
		i++;
	}
	
}
