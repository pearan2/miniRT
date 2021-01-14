# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/03 21:49:15 by honlee            #+#    #+#              #
#    Updated: 2021/01/14 01:16:23 by honlee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

SRCDIR		=		./srcs/
SRCNAME		=		\
					main.c\
					vec_util1.c\
					vec_util2.c\
					mlx_util1.c\
					color_util1.c\
					color_util2.c\
					sphere_util1.c\
					ray_util1.c\
					shade_util1.c\
					get_next_line.c\
					get_next_line_utils.c\
					split_util1.c\
					split_util2.c\
					convert_util1.c\
					error_util1.c\
					parse_util1.c\
					parse_util2.c\
					parse_util3.c\
					parse_util4.c\
					parse_util5.c\
					rotate_util1.c\
					plane_util1.c\
					event_util1.c\
					square_util1.c\
					disk_util1.c\
					cylinder_util1.c\
					cylinder_util2.c\
					tri_util1.c\
					bmp_util1.c
SRCS		=		${addprefix ${SRCDIR}, ${SRCNAME}}
INCDIR		=		./includes/
CC			=		clang
CF			=		-Wall -Wextra -Werror -I ${INCDIR} ${SRCS} -lbsd -lmlx -lXext -lX11 -lm
DCF			=		-g -I ${INCDIR} ${SRCS} -lbsd -lmlx -lXext -lX11 -lm
TCF			=		-I ${INCDIR} ${SRCS} -lbsd -lmlx -lXext -lX11 -lm
NAME		=		miniRT

${NAME}		:		
					${CC} ${CF} -o ${NAME}

fclean		:
					rm -f ${NAME}

all			:		${NAME}

re			:		fclean all

dbg			:		fclean
					${CC} ${DCF} -o ${NAME}
					lldb ${NAME} -- test/1.rt

test		:		fclean
					${CC} ${TCF} -o ${NAME}
					./${NAME} test/1.rt