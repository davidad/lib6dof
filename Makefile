PREFIX ?= /usr/local
LIBS =
DYLIB =

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
HIDC = hidapi/mac/hid.c
DYLIB = -dynamiclib
LIBS += -framework IOKit -framework CoreFoundation
OUTPUT = lib6dof.dylib
endif
ifeq ($(UNAME), Linux)
HIDC = hidapi/linux/hid.c
DYLIB = -shared
OUTPUT = lib6dof.so
endif

default:
	git submodule update
	make $(OUTPUT)

example: example.c lib6dof.h
	gcc $(CFLAGS) $(LIBS) -o example example.c -l6dof -lcurses

CFLAGS += -I.

$(OUTPUT): lib6dof.c lib6dof.h $(HIDC)
	gcc $(CFLAGS) $(LIBS) -o $(OUTPUT) lib6dof.c $(HIDC) $(DYLIB)

clean: .PHONY
	rm $(OUTPUT)

install: $(OUTPUT)
	install -d $(PREFIX)/lib
	install -c -m 644 $(OUTPUT) $(PREFIX)/lib/$(OUTPUT)
