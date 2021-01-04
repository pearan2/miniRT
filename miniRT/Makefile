# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honlee <honlee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/03 21:49:15 by honlee            #+#    #+#              #
#    Updated: 2021/01/04 02:43:14 by honlee           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

SRCDIR		=		./srcs/
SRCNAME		=		\
					main.c\
					vec_util1.c\
					vec_util2.c\
					mlx_util1.c\
					color_uilt1.c\
					color_uilt2.c
SRCS		=		${addprefix ${SRCDIR}, ${SRCNAME}}
INCDIR		=		./includes/
CC			=		clang
CF			=		-Wall -Wextra -Werror -I ${INCDIR} ${SRCS} -lbsd -lmlx -lXext -lX11 -lm
NAME		=		miniRT

${NAME}		:		
					${CC} ${CF} -o ${NAME}

fclean		:
					rm -f ${NAME}

all			:		${NAME}

re			:		fclean all

test		:		re
					./${NAME}