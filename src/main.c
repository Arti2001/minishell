/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 12:56:16 by amysiv        #+#    #+#                 */
/*   Updated: 2024/11/14 14:27:08 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	if (!ft_strncmp("cd", arg, ft_strlen(arg)))
		return (CD);
	if (!ft_strncmp("pwd", arg, ft_strlen(arg)))
		return (PWD);
	if (!ft_strncmp("env", arg, ft_strlen(arg)))
		return (ENV);
	if (!ft_strncmp("echo", arg, ft_strlen(arg)))
		return (ECHO);
	if (!ft_strncmp("exit", arg, ft_strlen(arg)))
		return (EXIT);
	if (!ft_strncmp("unset", arg, ft_strlen(arg)))
		return (UNSET);
	if (!ft_strncmp("export", arg, ft_strlen(arg)))
		return (EXPORT);
	return (NO_BUILTIN);
}

/*check_built_in() checks if it is a built in, if so ,  calls the coresponding built in function*/
int	run_built_in(t_env **env, char **arg)
{
	if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0])))
		return (ft_cd(*env, arg));
	if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0])))
		return (ft_pwd());
	if (!ft_strncmp("env", arg[0], ft_strlen(arg[0])))
		return (ft_env(*env));
	if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0])))
		return (ft_echo(arg));
	if (!ft_strncmp("exit", arg[0], ft_strlen(arg[0])))
		ft_exit(arg);
	if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0])))
		return (ft_unset(env, arg));
	if (!ft_strncmp("export", arg[0], ft_strlen(arg[0])))
		return (ft_export(*env, arg));
	return (NO_BUILTIN);
}

/*This is a temporary parsing. Below in the main() I read the input from the console, then  I split it with the ft_split function
and initialize the temporary struct init_temp_struct() which should contain the data for exexution (such as redirections, amount of pipes, heredoc) */



t_redirect	*init_redirect(void)
{
	int					i;
	int					count;
	t_redirect			*redirects;
	char				*names[] = { "a", NULL};
	t_redirect_type		type[] = {HEREDOC_RE, 0};

	count = 1;
	i = 0;
	redirects = (t_redirect *)malloc(sizeof(t_redirect) * (count + 1));
	if (redirects == NULL)
		return (NULL);
	while (count > i)
	{
		redirects[i] = (t_redirect){names[i], type[i]};
		i++;
	}
	redirects[i] = (t_redirect){names[i], type[i]};
	return (redirects);
}


t_pars	*ll_last_pars(t_pars *last)
{
	if (last == NULL)
		return (NULL);
	while (last->next_process != NULL)
		last = last->next_process;
	return (last);
}

void	node_add_back(t_pars	**head, t_pars *new_node)
{
	t_pars*	last;

	if (head == NULL)
		return ;
	last = ll_last_pars(*head);
	last->next_process = new_node;
}

t_pars	*parsing_node(char **cmd)
{
	t_pars *pars;

	pars = (t_pars *)malloc(sizeof(t_pars) * 1);
	pars->cmd = cmd;
	pars->fd_in = STDIN_FILENO;
	pars->fd_out = STDOUT_FILENO;
	pars->redir = init_redirect();
	pars->path = NULL;
	pars->next_process = NULL;
	return (pars);
}

void	append_pars_node(t_pars **head, char **cmd)
{
	t_pars	*new_pars_node;

	new_pars_node = parsing_node(cmd);
	if (cmd == NULL)
	{
		printf("cmd is NULL");
		return ;
	}
	if (*head == NULL)
		*head = new_pars_node;
	else
		node_add_back(head, new_pars_node);
}

t_pars *set_parsing_lst(char **cmds)
{
	int	i;
	t_pars 	*head_pars;
	char 	**cmd_arg;
	i = 0;
	head_pars  = NULL;
	while (cmds[i])
	{
		cmd_arg = ft_split(cmds[i], ' ');
		append_pars_node(&head_pars, cmd_arg);
		i++;
	}
	return (head_pars);
}

// void	init_pars_struct(char *input, t_pars *pars)
// {
// 	//pars =(t_pars *)ft_calloc(1, sizeof(t_pars));

// 	pars->orig_in = dup(STDIN_FILENO);
// 	pars->orig_out = dup(STDOUT_FILENO);
// 	pars->cmd = ft_split(input, ' ');
// 	pars->redir = init_redirect();
// 	pars->next_process = NULL;
// }



int main(int argc, char *argv[], char *envp[])
{
	char*	input;
	t_env*	env;
	t_pars	*pars;
	//t_data	data;

	if (argc == 1  && argv[0])
	{
		env = set_env(envp);
		if (env == NULL)
			return (1);
		input = NULL;
		while (1)
		{
			input = readline("Minishell>");
			if (input == NULL)
				return (1);
			if (!input[0])
				continue;
			add_history(input);
			//data.err_code = 0;
			pars = set_parsing_lst(ft_split(input, '|'));
			//init_pars_struct(input, &pars);
			/* lexer testing */
			init_pars(input, env);
			/* lexer testing*/
			free(input);
			if (pars->next_process == NULL)
			{
				if (is_builtin(pars->cmd[0]) == NO_BUILTIN)
					run_single_cmd(pars, env);
				else
					run_built_in(&env, pars->cmd);
			}
			else
			{
				//set_extern_cmd_path(pars, env);
				if (run_multi_cmd(pars, env) == 0)
					return(1);
			}
		}
		free_list(env);
	}
	return (0);
}
