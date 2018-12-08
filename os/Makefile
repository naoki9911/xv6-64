CC = gcc
LD = ld
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m64 -Werror -fno-omit-frame-pointer -fno-stack-protector
LDFLAGS = -m elf_x86_64
FONT_NAME = font.pf2

OBJS = \
       font.o\
       graphic.o\


kernel:main.o $(OBJS) font_bin.h
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel main.o $(OBJS)

font_builder: font_builder.c
	$(CC) -o font_builder font_builder.c

font_bin.h: font_builder
	./font_builder $(FONT_NAME) > font_bin.h

clean:
	rm -rf *.o *.d kernel font_bin.h font_builder

.c.o:
	$(CC) $(CFLAGS) -fno-pic -O -nostdinc -I. -c $<
