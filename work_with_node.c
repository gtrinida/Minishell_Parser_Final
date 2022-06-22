/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:20:13 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 03:51:51 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list_utils(t_node *tmp, t_rdir *rdir)
{
	if (tmp->need_to_free_arg == 1)
	{
		free(tmp->arg);
		tmp->need_to_free_arg = 0;
		tmp->need_to_free_str = 0;
	}
	while (rdir != NULL)
	{
		tmp->rdir = rdir->next;
		if (rdir->arg)
		{
			free(rdir->arg);
		}
		free(rdir);
		rdir = tmp->rdir;
	}
	free(tmp);
}

void	clear_list(t_node **list)
{
	t_node	*tmp;
	t_rdir	*rdir;
	int		i;

	i = 0;
	tmp = *list;
	while (tmp != NULL)
	{
		*list = tmp->next;
		free(tmp->cmd);
		while (i < tmp->n_arg)
		{
			free(tmp->arg[i]);
			i++;
		}
		if (tmp->n_arg == 0 && tmp->need_to_free_str == 1)
			free(tmp->arg[0]);
		i = 0;
		rdir = tmp->rdir;
		clear_list_utils(tmp, rdir);
		tmp = *list;
	}
}

void	print_rdir(t_rdir *rdir)
{
	while (rdir->next)
	{
		printf("rdir argument: %s\n", rdir->arg);
		printf("heredock quot: %d\n", rdir->heredock_quote);
		rdir = rdir->next;
	}
	printf("rdir argument: %s\n", rdir->arg);
	printf("heredock quot: %d\n", rdir->heredock_quote);
}

void	print_node(t_node *node)
{
	int		i;
	t_node	*tmp;

	tmp = node;
	i = 0;
	if (!node)
		return ;
	while (tmp->next)
	{
		i++;
		if (tmp->rdir)
			print_rdir(tmp->rdir);
		print_node2(tmp);
		tmp = tmp->next;
	}
	if (tmp->rdir)
		print_rdir(tmp->rdir);
	print_node2(tmp);
}

void	print_node2(t_node *node)
{
	int	i;

	i = 0;
	printf("command: %s\n", node->cmd);
	while (node->n_arg > i)
	{
		printf("argument: %s\n", node->arg[i]);
		i++;
	}
}
