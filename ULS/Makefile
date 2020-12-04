# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#    By: pmarchenko <pmarchenko@student.ucode.world>                   		   #
#                                                                              #
#    Created: 2017/11/13 14:20:39 by pmarchenko                            	   #
#    Updated: 2018/01/15 14:29:46 by pmarchenko                                #
#                                                                              #
# **************************************************************************** #

NAME	=	uls

CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic)

SRCD	=	src
INCD	=	inc
OBJD	=	obj

LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/inc

INC		=	uls.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC	= 		main.c mx_bzero.c mx_arrlen.c mx_arr_free.c mx_nbrlen.c


SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(LMXA) $(NAME)

$(NAME): $(OBJS)
	@clang $(CFLG) $(OBJS) -L$(LMXD) -lmx -o $@

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c -g $< -o $@ -I$(INCD) -I$(LMXI)


$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LMXA):
	@make -sC $(LMXD)
clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)

uninstall: clean
	@make -sC $(LMXD) $@
	@rm -rf $(NAME)

reinstall: uninstall install