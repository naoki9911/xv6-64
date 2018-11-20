CFLAGS = "-c"
FONT_NAME = font.pf2

OBJS = \
       font_builder.o\
       font.o\

font_builder: font_builder.c
	gcc -o font_builder font_builder.c

font_bin.h: font_builder
	./font_builder $(FONT_NAME) > font_bin.h

clean:
	rm -rf *.o font_bin.h font_builder

.c.o:
	gcc $(CFLAGS) $<
