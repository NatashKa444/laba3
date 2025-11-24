CC = gcc
PROGRAM = lab_stack
FILES = main.c stack.c 
all:
	$(CC) $(FILES) -o $(PROGRAM)
clean:
	rm -f $(PROGRAM)
run:
	./$(PROGRAM)