/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:01:20 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/27 16:32:12 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t g_signal;

int	go_all_herdoc(t_pars *pars, t_i_env *i_env)
{
	t_pars	*tmp;

	tmp = pars;
	while (tmp != NULL)
	{
		if (is_herdoc(tmp->redir))
		{
			if (run_herdoc(tmp->redir, i_env) == SIGINT)
				return (g_signal);
		}
		tmp = tmp->next_process;
	}
	return (1);
}

int	free_line(char *delim, int orig_stdin, char *line, int file_fd)
{
	if (g_signal == SIGINT)
	{
		if (dup2(orig_stdin, STDIN_FILENO) == -1)
		{
			perror("Failed to restore stdin");
			exit(EXIT_FAILURE);
		}
		if (close(orig_stdin) == -1)
		{
			perror("Failed to close stdin");
			exit(EXIT_FAILURE);
		}
		free(line);
		return (g_signal);
	}
	ft_putstr_fd("Warning: Here-document is not properly closed.\
	Expected delimiter: `", 2);
	ft_putstr_fd(delim, 2);
	ft_putendl_fd("'", 2);
	free(line);
	close(file_fd);
	return (1);
}

void	expand_or_write(t_redirect *redir, int fd, char *line, t_i_env *i_env)
{
	char	*expanded;

	expanded = expand_vars_str(line, DEFAULT, i_env);
	if (redir->is_expandable)
		ft_putendl_fd(expanded, fd);
	else
		ft_putendl_fd(line, fd);
	free(expanded);
	free(line);
}

int	write_into_herdoc(int fd, t_redirect *redir, t_i_env *i_env)
{
	char	*line;
	int		orig_in;

	orig_in = dup(STDIN_FILENO);
	line = NULL;
	init_siagtion(HERDOC_SIG);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			if (free_line(redir->filename, orig_in, line, fd) == g_signal)
				return (g_signal);
		}
		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename) + 1) == 0)
		{
			free(line);
			close(fd);
			break ;
		}
		expand_or_write(redir, fd, line, i_env);
	}
	dup2(orig_in, STDIN_FILENO);
	return (g_signal);
}

int	open_herdoc(t_redirect *redirect, t_i_env *i_env)
{
	int	fd;

	fd = open("/tmp/herdoc.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		perror("Faild to open the heredoc.txt");
		i_env->err_code = 1;
		return (0);
	}
	return (write_into_herdoc(fd, redirect, i_env));
}

int	run_herdoc(t_redirect *redirects, t_i_env *i_env)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (redirects[i].filename)
	{
		if (redirects[i].type == HEREDOC_RE)
		{
			ret = open_herdoc(&redirects[i], i_env);
			if (!ret)
			{
				return (0);
			}
		}
		i++;
	}
	return (ret);
}
