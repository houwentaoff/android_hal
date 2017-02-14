default:all

all:tips main

tips:
	-@echo  "\033[32m Building gps test app ... \033[0m"
tips_warning:
	-@echo  "\033[5;41;32m You don't need to compile app module  ... \033[0m"

ifndef TOP_DIR
TOP_DIR = $(shell pwd)/../
endif

include ../env.mk

INC+= -I$(TOP_DIR)/../libgpio/include/

#LD:= -L$(TOP_DIR)/libgps -lgps -L$(TOP_DIR)/libhardware -lhardware -ldl
LD:= -L$(TOP_DIR)/../libgpio/src/.libs -lgpio -L$(TOP_DIR)/libhardware -lhardware -ldl -lpthread

CFLAGS+=$(INC)

LDFLAGS+= $(LD)

main:main.o 
	$(CC) $^ -o $@ $(LD)

%.o:%.c
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	-@$(RM) *.o *.a main
.PHONY:clean
