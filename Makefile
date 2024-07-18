# to use:
# export Theia_DIR=/path/to/libtheia-dummy/
# and add -DWITH_LIBTHEIA=1 to your gvmd cmake command

CFLAGS = -g

all: libtheia.o

libtheia.a: libtheia.o
	ar rcs libtheia.a libtheia.o

libtheia.o: client.c
	$(CC) $(CFLAGS) -c -o libtheia.o client.c

clean:
	echo cleaning
	rm libtheia.a libtheia.o
