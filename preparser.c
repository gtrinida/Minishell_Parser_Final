/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:44 by gtrinida          #+#    #+#             */
/*   Updated: 2022/06/22 03:35:51 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredock_behind(char *line, int i)
{
	if (i == 0)
		return (0);
	i--;
	while (is_nothing(line[i]))
			i--;
	if (line[i] == '<')
	{
		if (i == 0)
			return (0);
		if (line[i - 1] == '<')
			return (1);
	}
	return (0);
}

void	data_init(t_params *data)
{
	data->list = NULL;
	data->key = 1;
}

int	cycle(char **env, t_params *data, int res)
{
	char	*line;

	while (1)
	{
		line = readline("minishell-3.2$ ");
		if (!line)
			return (1);
		if (!fast_quotes_check(line))
			printf("it was fast check >\n");
		else if (parser(line, env, data))
		{
			res = 1;
			if (line)
				free(line);
			print_node(data->list);
			clear_list(&(data->list));
		}
		if (!res)
			free(line);
		res = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_params	*data;
	int			res;

	res = 0;
	data = malloc(sizeof(t_params));
	if (!data)
		return (0);
	data_init(data);
	(void)argc;
	(void)argv;
	cycle(env, data, res);
	free(data);
	return (1);
}
