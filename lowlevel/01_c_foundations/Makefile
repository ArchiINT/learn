objects = memory_01.o

memory_01 : $(objects)
	gcc -Wall -o memory_01 $(objects)

memory_01.o : memory_01.c

.PHONY: clean

clean :
	rm memory_01 $(objects)
