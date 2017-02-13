default:all

all:tips lib  

tips:
	-@echo  "\033[32m Building libgps ... \033[0m"
tips_warning:
	-@echo  "\033[5;41;32m You don't need to compile libgps   ... \033[0m"

ifndef TOP_DIR
TOP_DIR = $(shell pwd)/../
endif

include ../env.mk

INC+= 

LD:= 

CFLAGS+=$(INC)

LDFLAGS+=$(LD)

lib:gps.o athr_gps.o
	$(AR) rucs libgps.a $^ 
	$(CC) -shared -fPIC -o libgps.so $^ -lm -lpthread

%.o:%.c
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	-@$(RM) *.o *.a *.so
.PHONY:clean
