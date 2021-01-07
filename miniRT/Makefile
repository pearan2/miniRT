# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/03 21:49:15 by honlee            #+#    #+#              #
#    Updated: 2021/01/06 18:01:45 by honlee           ###   ########seoul.kr   #
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
					shade_util1.c
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
					lldb ${NAME}

test		:		fclean
					${CC} ${TCF} -o ${NAME}
					./${NAME}