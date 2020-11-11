CFLAGS = -O3 -Wall

TARGETS = memscan memscan.exe memscan2 memscan2.exe memscan3 memscan3.exe

clean = $(TARGETS)

all: $(TARGETS)

memscan%: memscan%.c

%.exe: CC=/usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc
%.exe: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(if $(wildcard $($@)),$(RM) $(wildcard $($@)))

.PHONY: all clean
.DELETE_ON_ERROR:
