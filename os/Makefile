CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m64 -Werror -fno-omit-frame-pointer
FONT_NAME = font.pf2

OBJS = \
       font_builder.o\
       font.o\

kernel:main.o
	mv main.o kernel

font_builder: font_builder.c
	gcc -o font_builder font_builder.c

font_bin.h: font_builder
	./font_builder $(FONT_NAME) > font_bin.h

clean:
	rm -rf *.o *.d kernel font_bin.h font_builder

.c.o:
	gcc $(CFLAGS) -fno-pic -O -nostdinc -I. -c $<
