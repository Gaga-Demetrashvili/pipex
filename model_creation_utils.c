/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_creation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:55:18 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/29 22:06:58 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_cmds_arr(char **argv, int cmdc, char **cmds_arr,
		int is_heredoc)
{
	int	i;
	int	offset;

	i = 0;
	if (is_heredoc)
		offset = 3;
	else
		offset = 2;
	while (i < cmdc)
	{
		cmds_arr[i] = ft_strdup(argv[i + offset]);
		i++;
	}
	cmds_arr[i] = NULL;
}

static void	init_cmdv_arr(char ***cmdv_arr, char **cmds_arr, int cmdc)
{
	int	i;

	i = 0;
	while (i < cmdc)
	{
		cmdv_arr[i] = ft_split(cmds_arr[i], ' ');
		i++;
	}
	cmdv_arr[i] = NULL;
}

static void	model_init_logic_depending_on_heredoc(t_model *model,
		t_pr_args pr_args, char *heredoc_tmp_file_name)
{
	if (model->is_heredoc)
	{
		model->cmd_c = pr_args.argc - 4;
		model->infile_name = heredoc_tmp_file_name;
	}
	else
	{
		model->cmd_c = pr_args.argc - 3;
		model->infile_name = pr_args.argv[1];
	}
}

t_model	create_and_init_model(t_pr_args pr_args, int is_heredoc,
		char *heredoc_tmp_file_name)
{
	t_model	model;
	char	**cmds_arr;
	char	***cmdv_arr;

	model.is_heredoc = is_heredoc;
	model_init_logic_depending_on_heredoc(&model, pr_args,
		heredoc_tmp_file_name);
	cmds_arr = (char **)malloc(sizeof(char *) * (model.cmd_c + 1));
	if (cmds_arr)
		init_cmds_arr(pr_args.argv, model.cmd_c, cmds_arr, model.is_heredoc);
	cmdv_arr = (char ***)malloc(sizeof(char **) * (model.cmd_c + 1));
	if (cmdv_arr)
		init_cmdv_arr(cmdv_arr, cmds_arr, model.cmd_c);
	model.cmds_arr = cmds_arr;
	model.cmdv_arr = cmdv_arr;
	model.outfile_name = pr_args.argv[pr_args.argc - 1];
	model.envp = pr_args.envp;
	return (model);
}
