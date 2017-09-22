# Makefile for llist

all: check_dlist_node check_dlist

check_dlist_node: check_dlist_node.o dlist_node.o
	gcc -g -o $@ $^ -lcheck

check_dlist: check_dlist.o dlist.o dlist_node.o
	gcc -g -o $@ $^ -lcheck

%.o: %.c
	gcc -g -c $^

check_dlist_node.o dlist_node.o: dlist_node.h
check_dlist.o: dlist.h
dlist.o: dlist.h dlist_node.h

clean:
	rm -rf check_dlist_node check_dlist
	rm -rf *.o *.gch *.dSYM

.PHONY: all

# this next line prevents `make` from deleting the .o files
.SECONDARY: