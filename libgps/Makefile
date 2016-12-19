default:all

ifneq ($(PC), 1)

ifneq (buildroot, $(findstring buildroot, $(CC)))
#all:tips_warning 
all:tips lib
else
all:tips lib 
endif

else
all:tips lib 
endif

tips:
	-@echo  "\033[32m Building gps ... \033[0m"
tips_warning:
	-@echo  "\033[5;41;32m You don't need to compile gps module  ... \033[0m"

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

lib:gps.o athr_gps.o
	$(AR) rucs libpgs.a $^ 

%.o:%.c
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	-@$(RM) *.o *.a
.PHONY:clean
