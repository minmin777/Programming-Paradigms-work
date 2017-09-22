# This is a Makefile. Make sure it has that name.

# The first rule in a Makefile is the default. So, by default,
# this Makefile builds both prime and count_xs. You can write
# `make prime` or `make count_xs` on the command line to make
# just one

# This line says that `prime` depends on `prime.o` and `main.o`,
# and then how to build the target (prime) from the dependencies
mat: check_mat.o main.o
	gcc -o mat check_mat.o main.o

# Other rules are similar.
main.o: main.c 
	gcc -c main.c

prime.o: prime.c prime.h
	gcc -c prime.c

count_xs: count_xs.c
	gcc -o count_xs count_xs.c