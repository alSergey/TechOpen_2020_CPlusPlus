all: containers.a

%.o: %.c
	gcc -g -c $^

containers.a: vector.o list.o tree.o hash.o
	ar r $@ $^

clean:
	rm -f *.o *.a

test: test.o containers.a
	gcc -g -o $@ $^ 

check: test
	./test

.PHONY: all check clean
