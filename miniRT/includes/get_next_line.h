/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 12:23:33 by honlee            #+#    #+#             */
/*   Updated: 2021/01/06 19:43:51 by honlee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 100
# define OPEN_MAX 1
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
