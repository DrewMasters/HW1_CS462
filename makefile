all: dining_philosophers.c
	gcc -pthread -o dining_philosophers dining_philosophers.c
clean:
	$(RM) dining_philosophers
