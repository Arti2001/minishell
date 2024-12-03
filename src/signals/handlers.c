/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:15:25 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 21:13:57 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	handler_int(int num)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = num;
}

void	handler_non_int(int num)
{
	write(1, "\n", 2);
	g_signal = num;
}

void	handler_sigq(int num)
{
	write(1, "Quit (core dumped)", 19);
	write(1, "\n", 2);
	g_signal = num;
}

void	handler_heredoc(int num)
{
	write(1, "\n", 2);
	close(STDIN_FILENO);
	g_signal = num;
}
