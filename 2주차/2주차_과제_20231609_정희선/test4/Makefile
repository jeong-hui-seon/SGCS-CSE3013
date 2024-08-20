CC = gcc
target = quiz
objects = main.o count.o test.o
srcs = main.c count.c test.c
heds = test.h count.h

$(target): $(objects)
	$(CC) -o $(target) $(objects)

%.o: %.c $(heds)
	$(CC) -c -o $@ $<

.PHONY : clean

clean :
	rm $(target) $(objects)
