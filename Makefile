OBJS:=citylinklist.o main.o
CC:=clang
main:$(OBJS)
	$(CC) -c $(OBJS) -o main -lm
citylinklist.o:
	$(CC) -c citylinklist.c
main.o:
	$(CC) citylinklist.o main.o -c -o main 
.PHONY:
	clean
clean:
	rm *.o main
