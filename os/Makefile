CC = gcc
LD = ld
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m64 -Werror -fno-omit-frame-pointer -fno-stack-protector
LDFLAGS = -m elf_x86_64

OBJS = \
       font.o\
       graphic.o\
       console.o\
       debug.o\


kernel:main.o $(OBJS)
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel main.o $(OBJS)

clean:
	rm -rf *.o *.d kernel

.c.o:
	$(CC) $(CFLAGS) -fno-pic -O -nostdinc -I. -c $<
