CFLAGS = -O3 -Wall

TARGETS = memscan memscan.exe memscan2 memscan2.exe

clean = $(TARGETS)

all: $(TARGETS)

memscan: memscan.c

memscan2: memscan2.c

memscan.exe: CC=/usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc
memscan.exe: memscan.c
	$(CC) -c $(CFLAGS) -o $@ $<

memscan2.exe: CC=/usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc
memscan2.exe: memscan.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(if $(wildcard $($@)),$(RM) $(wildcard $($@)))

.PHONY: all clean
.DELETE_ON_ERROR:
