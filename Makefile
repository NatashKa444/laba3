.PHONY: all clean run
PROGRAM = lab_stack 
FILES = main.c stack.c sorting.c  
all:
 	gcc $(FILES) -o $(PROGRAM)
clean:
	rm -f $(PROGRAM)
run:
	./$(PROGRAM)