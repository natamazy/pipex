/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:31:26 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/08 16:18:52 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes_files(t_allvars *vars)
{
	int	j;

	j = 0;
	while (j < vars->cmd_count - 1)
	{
		close(vars->pipeing[j][0]);
		close(vars->pipeing[j][1]);
		j++;
	}
}

void	running_cmds(char *argv[], char *envp[], t_allvars *vars)
{
	int	i;
	int	id;

	i = 0;
	while (i < vars->cmd_count)
	{
		id = fork();
		if (id == -1)
			print_error(ERROR_FORK, 2);
		if (id == 0 && i == 0)
			first_cmd(argv, envp, vars, i);
		else if (id == 0 && i == vars->cmd_count - 1)
			middle_cmd(argv, envp, vars, i);
		else if (id == 0)
			last_cmd(argv, envp, vars, i);
		i++;
	}
}

void	init_vars(t_allvars *vars, char *envp[])
{
	vars->cmd_and_flags = NULL;
	vars->paths = find_paths(envp);
}

void	pipeing_pipes(t_allvars *vars)
{
	int	i;

	i = 0;
	while (i < vars->cmd_count - 1)
	{
		if (pipe(vars->pipeing[i]) == -1)
			print_error(ERROR_PIPE, 2);
		i++;
	}
}

void	waiting_for_childs(void)
{
	while (wait(NULL) != -1)
		;
}
