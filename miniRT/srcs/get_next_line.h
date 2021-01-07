/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 12:23:33 by honlee            #+#    #+#             */
/*   Updated: 2020/12/31 13:40:43 by honlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int					get_next_line(int fd, char **line);
int					ft_len(char *src);
int					is_newline(char *str);
int					return_end(int fd, char **bus, char **line, int rb);
int					bu_split(char **line, char *bu);
char				*bu_append(char *bu, char *buff);
char				*ft_strdup(char *input);

#endif
