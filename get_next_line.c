/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulmet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:27:37 by atoulmet          #+#    #+#             */
/*   Updated: 2016/12/30 17:35:49 by atoulmet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_struct		*find_fd(int fd, t_struct **list)
{
	t_struct	*tmp;
	t_struct	*new;

	if (*list == NULL)
	{
		if ((*list = ft_memalloc(sizeof(t_struct))) == NULL)
			return (NULL);
		(*list)->fd = fd;
		return (*list);
	}
	tmp = *list;
	while (tmp->next != NULL && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	if ((new = ft_memalloc(sizeof(t_struct))) == NULL)
		return (NULL);
	new->fd = fd;
	tmp->next = new;
	return (new);
}

static char		*add_following_part(char **line, char *buff, t_struct *list)
{
	char	*output;
	int		i;
	int		j;
	int		stock;

	i = (*line == NULL ? 0 : ft_strlen(*line));
	j = 0;
	stock = 0;
	while (buff[j] && buff[j] != '\n')
		j++;
	if ((output = (char*)ft_memalloc(sizeof(char) * (i + j + 1))) == 0)
		return (NULL);
	if (*line != NULL)
	{
		ft_strcpy(output, *line);
		ft_strdel(line);
	}
	ft_strncpy(output + i, buff, j);
	if (buff[j] != '\0')
	{
		stock = ft_strlen(buff + j + 1);
		if ((list->stock = ft_strsub(buff, j + 1, stock)) == 0)
			return (NULL);
	}
	return (output);
}

static int		stock_checker(t_struct *list, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (list->stock == NULL)
		return (0);
	if (ft_strchr(list->stock, '\n') == NULL)
	{
		*line = ft_strdup(list->stock);
		ft_strdel(&(list->stock));
		return (0);
	}
	else
	{
		while (list->stock[i] != '\n')
			i++;
		if ((*line = ft_strsub(list->stock, 0, i)) == NULL)
			return (-1);
		tmp = list->stock;
		if ((list->stock = ft_strsub(list->stock, i + 1,
						ft_strlen(list->stock) - i)) == NULL)
			return (-1);
		ft_strdel(&tmp);
		return (1);
	}
}

static int		reader(int fd, char **line, t_struct *list)
{
	char	*buff;
	int		ret;

	if ((buff = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		buff[ret] = '\0';
		if (ret == -1)
			return (-1);
		if ((*line = add_following_part(line, buff, list)) == NULL)
			return (-1);
		if (ft_strchr(buff, '\n') != NULL)
		{
			ft_strdel(&buff);
			return (1);
		}
	}
	ft_strdel(&buff);
	if (*line == NULL || **line == '\0')
		return (0);
	else
		return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_struct	*begin_list = NULL;
	t_struct		*list;
	int				error_ctrl;

	error_ctrl = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	list = find_fd(fd, &begin_list);
	if ((error_ctrl = stock_checker(list, line)) == 1)
		return (1);
	if (error_ctrl == -1)
		return (-1);
	if ((error_ctrl = (reader(fd, line, list))) == 1)
		return (1);
	if (error_ctrl == -1)
		return (-1);
	else
		return (0);
}
