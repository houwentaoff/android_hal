default:all

all:tips lib

tips:
	-@echo  "\033[32m Building libhardware ... \033[0m"

ifneq ($(PC), 1)

ifndef TOP_DIR
TOP_DIR = $(shell pwd)/../
endif

include ../env.mk

endif

ifneq (buildroot, $(findstring buildroot, $(CC)))
INC+= 
else
INC+=
endif


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
