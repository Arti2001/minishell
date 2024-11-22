/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:09:25 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/22 14:31:12 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t g_signal;

static void	handler_int(int num)
{
	//write(1, "I'm in interactive", 19);
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = num;
}

static void	handler_non_int(int num)
{
	write(1, "\n", 2);
	signal(SIGINT, SIG_IGN);
	g_signal = num;
}

static void	handler_herdoc(int num)
{
	printf("Herdoc signal\n");
	
	g_signal = num;
}

void	init_siagtion(int param)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (param == INTERACTIVE)
	{
		sa.sa_handler = &handler_int;
		if (sigaction(SIGINT, &sa, NULL) == -1)
		{
			perror("Failed to call sigaction().");
			exit(0);
		}
		signal(SIGQUIT, SIG_IGN);
	}
	else if (param == NON_INTERACTIVE)
	{
		sa.sa_handler = &handler_non_int;
		if (sigaction(SIGINT, &sa, NULL) == -1)
		{
			perror("Failed to call sigaction().");
			exit(0);
		}
		signal(SIGQUIT, SIG_IGN);
	}
	else if (param == HERDOC_SIG)
	{
		sa.sa_handler = &handler_herdoc;
		if (sigaction(SIGINT, &sa, NULL) == -1)
		{
			perror("Failed to call sigaction().");
			exit(0);
		}
		signal(SIGQUIT, SIG_IGN);
	}
}


