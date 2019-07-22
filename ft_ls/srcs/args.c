/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fremoor <fremoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 09:08:19 by fremoor           #+#    #+#             */
/*   Updated: 2019/07/22 15:37:04 by fremoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				islink(const char *path)
{
	struct stat	s;

	lstat(path, &s);
	return (S_ISLNK(s.st_mode));
}

int				isdir(const char *path)
{
	struct stat	s;

	stat(path, &s);
	return (S_ISDIR(s.st_mode));
}

void			sort_args(char **args)
{
	int			i;
	char		*temp;

	i = 0;
	while ((args[i] != NULL) && (args[i + 1] != NULL))
	{
		if (ft_strcmp(args[i], args[i + 1]) <= 0)
			i++;
		else
		{
			temp = args[i];
			args[i] = args[i + 1];
			args[i + 1] = temp;
		}
	}
}

int				check_arg(int ac, int flags, char **args)
{
	int			i;
	int			check;
	int			tru;

	i = -1;
	check = 0;
	tru = 0;
	while (args[++i] != NULL)
		if (!(isdir(args[i])))
		{
			ft_ls(args[i], flags);
			tru = 1;
		}
	if (tru == 1)
		ft_putchar('\n');
	i = -1;
	while (args[++i] != NULL)
	{
		if (isdir(args[i]))
		{
			if (ac > 1)
				ft_printf("%s:\n", args[i]);
			ft_ls(args[i], flags);
			if (i + 1 < ac)
				ft_putchar('\n');
		}
		check = 1;
	}
	return (check);
}

int				add_args(char **args, int ac, char **av)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		if ((av[i][0] == '-') && (ft_strlen(av[i]) > 1) && (av[i][1] != '-'))
			i++;
		else if (av[i][0] == '-' && av[i][1] == '-')
		{
			i++;
			break ;
		}
		else
			break;
	}
	while (i < ac)
		args[j++] = av[i++];
	args[j] = NULL;
	sort_args(args);
	return (j);
}
