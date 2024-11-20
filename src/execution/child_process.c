/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:00:02 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/20 14:13:31 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void wait_for_childs(int num_pid, pid_t *pids)
{
	int		i;

	i = 0;
	while (i < num_pid)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

/*try to store the read end  before  you fork*/
void	set_child(t_pars *pars, t_env *env, int fd_write_end, int	process_num, char ***env_array)
{
	if (pars->cmd == NULL)
		exit(EXIT_SUCCESS);
	*env_array = back_to_array(env);
	if (!env_array)
	{
		close(fd_write_end);
		perror("Environment array creation failed");
		exit(errno);
	}
	if (check_redirection_type(process_num, pars, fd_write_end) == 0)
	{
		close(fd_write_end);
		perror ("pipe redirection failed");
		exit(EXIT_FAILURE);
	}
	if (pars->redir != NULL)
		redirect_check(pars);
}

void	my_dear_child(int fd_write_end, int	process_num, t_pars *pars, t_env *env)
{
	char	**env_array;
	
	set_child(pars, env, fd_write_end, process_num, &env_array);
	if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
	{
		run_built_in(&env, pars->cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		path_hendler(env, &pars, pars->cmd[0]);
		execve(pars->path, pars->cmd, env_array);
		ft_putstr_fd(pars->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		double_array_free(pars->cmd);
		free(pars->	path);
		exit(127);
	}
}
//void	my_dear_child(int fd_write_end, int	process_num, t_pars *pars, t_env *env)
//{
//	char	**environment;

//	if (pars->cmd == NULL)
//		exit(EXIT_SUCCESS);
//	path_hendler(env, &pars, pars->cmd[0]);
//	environment = back_to_array(env);
//	if (!environment)
//	{
//		close(fd_write_end);
//		perror("Environment array creation failed");
//		exit(errno);
//	}
//	if (check_redirection_type(process_num, pars, fd_write_end) == 0)
//	{
//		close(fd_write_end);
//		perror ("pipe redirection failed");
//		exit(EXIT_FAILURE);
//	}
//	if (pars->redir != NULL)
//	{
//		redirect_check(pars);
//	}
//	if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
//	{
//		run_built_in(&env, pars->cmd);
//		exit(EXIT_SUCCESS);
//	}
//	else
//	{
//		execve(pars->path, pars->cmd, environment);
//		ft_putstr_fd(pars->cmd[0], 2);
//		ft_putendl_fd(": command not found", 2);
//		double_array_free(pars->cmd);
//		free(pars->	path);
//		exit(127);
//	}
//}