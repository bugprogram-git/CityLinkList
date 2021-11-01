OBJS:=citylinklist.o main.o
CC:=clang
main:$(OBJS)
	$(CC) $(OBJS) -o main -lm
citylinklist.o:
main.o:
.PHONY:
	clean
clean:
	rm *.o
