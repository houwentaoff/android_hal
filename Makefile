SUBDIRS=libhardware libgps test_unit

#ifndef TOP_DIR
TOP_DIR=$(shell pwd)/
export TOP_DIR
#endif

include env.mk

all:
	-@echo  "\033[32m Building 3ps module ... \033[0m"
	for d in $(SUBDIRS); do [ -d $$d ] && $(MAKE) -C $$d; done

clean:
	for d in $(SUBDIRS); do [ -d $$d ] && $(MAKE) -C $$d clean; done
	-@$(RM) -f *~

install:
	for d in $(SUBDIRS); do [ -d $$d ] && $(MAKE) -C $$d install; done

.PHONY:clean
