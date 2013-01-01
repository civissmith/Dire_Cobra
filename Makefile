################################################################################
# @Title: Makefile 
#
# @Author: Phil Smith 
#
# @Date: 29-Oct-2011	01:10 PM
#
# @Project: Controller
#
# @Purpose: 
#
# @Modification History: 
#
###############################################################################
CC=gcc
TARG=controld
SRC=controller.c iofunc.c setup.c
OBJ=controller.o iofunc.o setup.o
CFLAGS= -c 

all: $(TARG)

%.o: %.c *.h

controld: $(OBJ)
	$(CC) $(OBJ) -o $@


.PHONY: clean

clean: 
	$(RM) $(TARG) $(OBJ)	
