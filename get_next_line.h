/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulmet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:23:04 by atoulmet          #+#    #+#             */
/*   Updated: 2016/12/30 18:43:46 by atoulmet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_struct
{
	char				*stock;
	int					fd;
	struct s_struct		*next;
}					t_struct;

int					get_next_line(const int fd, char **line);

# define BUFF_SIZE 10

#endif
