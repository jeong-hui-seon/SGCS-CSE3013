CC = g++
target = a.out
objects = main.o str.o
srcs = main.cpp str.cpp
heds = str.h

$(target): $(objects)
	$(CC) -o $(target) $(objects)

%.o: %.cpp $(heds)
	$(CC) -c -o $@ $<

.PHONY : clean

clean :
	rm $(target) $(objects)