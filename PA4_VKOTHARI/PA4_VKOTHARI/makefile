CFLAGS=-g -Wall

# “make all” will make the executable(s)
all: example1

# Create the executable
example1: example1.o
	gcc $(CFLAGS) example1.o -o example1

# Create the .o file
example1.o: example1.c
	gcc $(CFLAGS) -c example1.c

#Remove the .o files and executable	
clean:
	rm –f *.o example1
	rm –f –r html latex

# Generate documentation
docs:
	doxygen