CC = gcc
CFLAGS = -I include -Wall

src = $(wildcard src/*.c)
obj = $(patsubst src/%.c, build/%.o, $(src))
hdrs = $(wildcard include/*.h)

usip: $(obj)
	$(CC) $(obj) -o usip

build/%.o: src/%.c ${hdrs}
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm build/*.o usip
