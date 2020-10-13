###
### Makefile
###
###
### Licensed under GNU GPL v3
###
###

.PHONY: clean install uninstall

CC = g++                        # compiler to use

LINKERFLAG = -lcurses

SRCS := source/main.cpp

BIN := dvd

dvd:
		@echo "Building..."
		@${CC} ${SRCS} -o ${BIN} ${LINKERFLAG}
		@echo "Done!"

clean:
		@echo "Cleaning up..."
		@rm dvd
		@echo "Done!"

install: dvd
		@echo "Installing..."
		@sudo cp dvd /usr/bin/dvd
		@echo "Done!"

uninstall: 
		@echo "Uninstalling..."
		@rm /usr/bin/dvd
		@echo "Done!"
