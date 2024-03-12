/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:08:07 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/08 16:21:06 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	freeing(t_allvars *vars)
{
	free(vars->pipeing);
	close(vars->file1);
	close(vars->file2);
	free_split(vars->paths);
	free(vars->paths);
	vars->paths = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_allvars	vars;

	init_vars(&vars, envp);
	args_files_validation(argc, argv, &vars);
	pipeing_pipes(&vars);
	if (vars.file1 == -1)
		get_from_here_doc(&vars);
	running_cmds(argv, envp, &vars);
	if (vars.is_here_doc == 1)
		free(vars.here_doc_pipe);
	close_pipes_files(&vars);
	freeing(&vars);
	waiting_for_childs();
	return (0);
}
