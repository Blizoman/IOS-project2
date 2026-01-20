.PHONY: clean zip a
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

a:
	make clean
	make proj2
	touch proj2.out
proj2: $(OBJS)
	gcc -std=gnu99 -Wall -Wextra -Werror -pedantic -o $@ $^

clean:
	rm -f proj2 proj2.out *.o
zip:
	zip xblizna00.zip *.c *.h Makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $<