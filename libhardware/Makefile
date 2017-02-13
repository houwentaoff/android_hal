default:all

all:tips lib

tips:
	-@echo  "\033[32m Building libhardware ... \033[0m"

ifndef TOP_DIR
TOP_DIR = $(shell pwd)/../
endif

include ../env.mk

INC+=

LD:=

CFLAGS+=$(INC)
LDFLAGS+=$(LD)

lib:hardware.o
	$(AR) rucs libhardware.a $^ 

%.o:%.c
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	-@$(RM) *.o *.a
.PHONY:clean
