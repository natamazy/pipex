/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:53:25 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/08 14:52:21 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char *array[])
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

void	first_cmd(char *argv[], char *envp[], t_allvars *vars, int i)
{
	int	g;

	g = 2;
	if (vars->file1 == -1)
	{
		if (dup2(vars->here_doc_pipe[0][0], 0) == -1)
			print_error(ERROR_DUP, 2);
		g += 1;
	}
	else if (dup2(vars->file1, 0) == -1)
		print_error(ERROR_DUP, 2);
	if (dup2(vars->pipeing[i][1], 1) == -1)
		print_error(ERROR_DUP, 2);
	close_pipes_files(vars);
	vars->cmd_and_flags = ft_split(argv[i + g], ' ');
	if (vars->cmd_and_flags == NULL)
		print_error(ERROR_MALLOC, 2);
	vars->cmd = cmd_exist(vars->paths, vars->cmd_and_flags[0]);
	if (vars->cmd == NULL)
	{
		free_split(vars->cmd_and_flags);
		print_error(ERROR_CMD, 2);
	}
	execve(vars->cmd, vars->cmd_and_flags, envp);
}

void	middle_cmd(char *argv[], char *envp[], t_allvars *vars, int i)
{
	int	g;

	g = 2;
	if (vars->file1 == -1)
		g += 1;
	if (dup2(vars->pipeing[i - 1][0], 0) == -1)
		print_error(ERROR_DUP, 2);
	if (dup2(vars->file2, 1) == -1)
		print_error(ERROR_DUP, 2);
	close_pipes_files(vars);
	vars->cmd_and_flags = ft_split(argv[i + g], ' ');
	if (vars->cmd_and_flags == NULL)
		print_error(ERROR_MALLOC, 2);
	vars->cmd = cmd_exist(vars->paths, vars->cmd_and_flags[0]);
	if (vars->cmd == NULL)
	{
		free_split(vars->cmd_and_flags);
		print_error(ERROR_CMD, 2);
	}
	execve(vars->cmd, vars->cmd_and_flags, envp);
}

void	last_cmd(char *argv[], char *envp[], t_allvars *vars, int i)
{
	int	g;

	g = 2;
	if (vars->file1 == -1)
		g += 1;
	if (dup2(vars->pipeing[i - 1][0], 0) == -1)
		print_error(ERROR_DUP, 2);
	if (dup2(vars->pipeing[i][1], 1) == -1)
		print_error(ERROR_DUP, 2);
	close_pipes_files(vars);
	vars->cmd_and_flags = ft_split(argv[i + g], ' ');
	if (vars->cmd_and_flags == NULL)
		print_error(ERROR_MALLOC, 2);
	vars->cmd = cmd_exist(vars->paths, vars->cmd_and_flags[0]);
	if (vars->cmd == NULL)
	{
		free_split(vars->cmd_and_flags);
		print_error(ERROR_CMD, 2);
	}
	execve(vars->cmd, vars->cmd_and_flags, envp);
}
