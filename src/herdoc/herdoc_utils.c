/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:11:55 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 19:37:08 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_or_write(t_redirect *redir, int fd, char *line, t_i_env *i_env)
{
	char	*expanded;

	expanded = expand_vars_str(line, DEFAULT, i_env);
	if (redir->is_expandable)
		shell_putendl_fd(expanded, fd);
	else
		shell_putendl_fd(line, fd);
	free(expanded);
	free(line);
}

int	is_herdoc(t_redirect *redirect)
{
	int	i;

	i = 0;
	if (redirect == NULL)
		return (0);
	while (redirect[i].filename != NULL)
	{
		if (redirect[i].type == HEREDOC_RE)
			return (1);
		else
			i++;
	}
	return (0);
}
