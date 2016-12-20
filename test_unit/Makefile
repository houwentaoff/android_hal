default:all

ifneq ($(PC), 1)

ifneq (buildroot, $(findstring buildroot, $(CC)))
#all:tips_warning 
all:tips main
else
all:tips main 
endif

else
all:tips main 
endif

tips:
	-@echo  "\033[32m Building app ... \033[0m"
tips_warning:
	-@echo  "\033[5;41;32m You don't need to compile app module  ... \033[0m"

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

#LD:= -L$(TOP_DIR)/libgps -lgps -L$(TOP_DIR)/libhardware -lhardware -ldl
LD:= -L$(TOP_DIR)/libhardware -lhardware -ldl -lpthread

CFLAGS+=$(INC)

LDFLAGS+="aaa" $(LD)

main:main.o 
	$(CC) $^ -o $@ $(LD)

%.o:%.c
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	-@$(RM) *.o *.a
.PHONY:clean
